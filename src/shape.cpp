#include <servoce/shape.h>
#include <servoce/face.h>
#include <servoce/edge.h>
#include <servoce/solid.h>
#include <servoce/wire.h>
#include <servoce/shell.h>
#include <servoce/compsolid.h>
#include <servoce/compound.h>
#include <servoce/geomprops.h>
#include <servoce/boundbox.h>

#include <TopoDS_Shape.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_CompSolid.hxx>
#include <TopoDS.hxx>
#include <gp_Pln.hxx>

#include <BinTools_ShapeSet.hxx>
#include <BinTools.hxx>

#include <BRepTools_WireExplorer.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepFilletAPI_MakeFillet2d.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepExtrema_DistShapeShape.hxx>
#include <Geom_Plane.hxx>

#include <BRepBndLib.hxx>

#include <TopTools_HSequenceOfShape.hxx>
#include <TopOpeBRepBuild_Tools.hxx>
#include <ShapeExtend_Explorer.hxx>

#include <TopAbs_ShapeEnum.hxx>
#include <TopExp_Explorer.hxx>
#include <GProp_GProps.hxx>
#include <BRepGProp.hxx>

#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_GTransform.hxx>
#include <TopExp.hxx>

#include <algorithm>
#include <cassert>
#include <iostream>

#include <servoce/edge.h>
#include <servoce/face.h>

servoce::shape::shape(const TopoDS_Shape& shp) : m_shp(new TopoDS_Shape(shp))
{
	if (m_shp->IsNull())
	{
		printf("warn: null shape contruct\n");
	}
}

servoce::shape::shape(const shape& oth) : m_shp(new TopoDS_Shape(*oth.m_shp))
{}

servoce::shape::shape(shape&& oth) : m_shp(oth.m_shp)
{
	oth.m_shp = nullptr;
}

servoce::shape::~shape() { delete m_shp; }

bool servoce::shape::is_nullshape() 
{
	return m_shp->IsNull() || vertices().size() == 0;
}

servoce::shape& servoce::shape::operator= (const shape& oth)
{
	if (m_shp != oth.m_shp)
	{
		delete m_shp;
		m_shp = new TopoDS_Shape(*oth.m_shp);
	}

	return *this;
}

servoce::shape& servoce::shape::operator= (shape&& oth)
{
	delete m_shp;
	m_shp = oth.m_shp;
	oth.m_shp = nullptr;
	return *this;
}

servoce::shape& servoce::shape::operator= (const TopoDS_Shape& shp)
{
	delete m_shp;
	m_shp = new TopoDS_Shape(shp);
	return *this;
}

TopoDS_Shape& servoce::shape::Shape() { return *m_shp; }
const TopoDS_Shape& servoce::shape::Shape() const { return *m_shp; }

TopoDS_Edge& servoce::shape::Edge() { return TopoDS::Edge(*m_shp); }
const TopoDS_Edge& servoce::shape::Edge() const { return TopoDS::Edge(*m_shp); }

TopoDS_Vertex& servoce::shape::Vertex() { return TopoDS::Vertex(*m_shp); }
const TopoDS_Vertex& servoce::shape::Vertex() const { return TopoDS::Vertex(*m_shp); }

TopoDS_Wire& servoce::shape::Wire() { return TopoDS::Wire(*m_shp); }
const TopoDS_Wire& servoce::shape::Wire() const { return TopoDS::Wire(*m_shp); }

TopoDS_Face& servoce::shape::Face() { return TopoDS::Face(*m_shp); }
const TopoDS_Face& servoce::shape::Face() const { return TopoDS::Face(*m_shp); }

TopoDS_Shell& servoce::shape::Shell() { return TopoDS::Shell(*m_shp); }
const TopoDS_Shell& servoce::shape::Shell() const { return TopoDS::Shell(*m_shp); }

TopoDS_Solid& servoce::shape::Solid() { return TopoDS::Solid(*m_shp); }
const TopoDS_Solid& servoce::shape::Solid() const { return TopoDS::Solid(*m_shp); }

TopoDS_Compound& servoce::shape::Compound() { return TopoDS::Compound(*m_shp); }
const TopoDS_Compound& servoce::shape::Compound() const { return TopoDS::Compound(*m_shp); }

TopoDS_CompSolid& servoce::shape::CompSolid() { return TopoDS::CompSolid(*m_shp); }
const TopoDS_CompSolid& servoce::shape::CompSolid() const { return TopoDS::CompSolid(*m_shp); }

TopoDS_Wire servoce::shape::Wire_orEdgeToWire() const
{
	if (Shape().ShapeType() == TopAbs_WIRE)
		return Wire();
	else
		return BRepBuilderAPI_MakeWire(Edge()).Wire();
}


servoce::point3 servoce::shape::as_vertex() const { return Vertex(); }
servoce::edge_shape servoce::shape::as_edge() const { return Edge(); }
servoce::wire_shape servoce::shape::as_wire() const { return Wire_orEdgeToWire(); }
servoce::face_shape servoce::shape::as_face() const { return Face(); }
servoce::shell_shape servoce::shape::as_shell() const { return Shell(); } 
servoce::solid_shape servoce::shape::as_solid() const { return Solid(); } 
servoce::compsolid_shape servoce::shape::as_compsolid() const { return CompSolid(); } 
servoce::compound_shape servoce::shape::as_compound() const { return Compound(); } 

void servoce::shape::dump(std::ostream& out) const
{
	BinTools_ShapeSet theShapeSet;

	if (m_shp->IsNull())
	{
		theShapeSet.Add(*m_shp);
		theShapeSet.Write(out);
		BinTools::PutInteger(out, -1);
		BinTools::PutInteger(out, -1);
		BinTools::PutInteger(out, -1);
	}
	else
	{
		Standard_Integer shapeId = theShapeSet.Add(*m_shp);
		Standard_Integer locId = theShapeSet.Locations().Index(m_shp->Location());
		Standard_Integer orient = static_cast<int>(m_shp->Orientation());

		theShapeSet.Write(out);
		BinTools::PutInteger(out, shapeId);
		BinTools::PutInteger(out, locId);
		BinTools::PutInteger(out, orient);
	}
}

void servoce::shape::load(std::istream& in)
{
	BinTools_ShapeSet theShapeSet;
	theShapeSet.Read(in);
	Standard_Integer shapeId = 0, locId = 0, orient = 0;
	BinTools::GetInteger(in, shapeId);

	if (shapeId <= 0 || shapeId > theShapeSet.NbShapes())
		return;

	BinTools::GetInteger(in, locId);
	BinTools::GetInteger(in, orient);
	TopAbs_Orientation anOrient = static_cast<TopAbs_Orientation>(orient);

	m_shp = new TopoDS_Shape();
	*m_shp = theShapeSet.Shape(shapeId);
	m_shp->Location(theShapeSet.Locations().Location (locId));
	m_shp->Orientation (anOrient);
}

servoce::point3 servoce::shape::center() const
{
	GProp_GProps props;
	BRepGProp::VolumeProperties(Shape(), props);
	gp_Pnt centerMass = props.CentreOfMass();
	return point3(centerMass);
}

servoce::shape servoce::shape::fill()
{
	if (Shape().ShapeType() == TopAbs_EDGE)
	{
		return	BRepBuilderAPI_MakeFace(BRepBuilderAPI_MakeWire(Edge()).Wire()).Shape();
	}

	if (Shape().ShapeType() == TopAbs_WIRE)
	{
		return BRepBuilderAPI_MakeFace(Wire()).Shape();
	}

	throw "unsuported type";
}

servoce::shape servoce::fill(const servoce::shape& shp)
{
	if (shp.Shape().ShapeType() == TopAbs_EDGE)
	{
		return	BRepBuilderAPI_MakeFace(BRepBuilderAPI_MakeWire(shp.Edge()).Wire()).Shape();
	}

	if (shp.Shape().ShapeType() == TopAbs_WIRE)
	{
		return BRepBuilderAPI_MakeFace(shp.Wire()).Shape();
	}

	throw "unsuported type";
}

std::vector<servoce::point3> servoce::shape::vertices() const
{
	std::vector<servoce::point3> pnts;

	for (TopExp_Explorer expVertex(Shape(), TopAbs_VERTEX); expVertex.More(); expVertex.Next())
	{
		const TopoDS_Vertex& vtx = TopoDS::Vertex(expVertex.Current());
		servoce::point3 pnt(vtx);
		bool needadd = true;

		for (auto& p : pnts)
		{
			if (point3::early(pnt, p))
			{
				needadd = false;
				break;
			}

		}

		if (needadd)
			pnts.push_back(pnt);
	}

	std::sort(pnts.begin(), pnts.end(), [](const servoce::point3 & a, const servoce::point3 & b)
	{
		return servoce::point3::lexless_xyz(a, b);
	});

	return pnts;
}

servoce::topoenum servoce::shape::type()
{
	throw "TODO";
}

std::vector<servoce::solid_shape> servoce::shape::solids() const
{
	std::vector<servoce::solid_shape> ret;

	for (TopExp_Explorer ex(Shape(), TopAbs_SOLID); ex.More(); ex.Next())
	{
		TopoDS_Solid obj = TopoDS::Solid(ex.Current());
		ret.emplace_back(obj);
	}

	return ret;
}

std::vector<servoce::face_shape> servoce::shape::faces() const
{
	std::vector<servoce::face_shape> ret;

	for (TopExp_Explorer ex(Shape(), TopAbs_FACE); ex.More(); ex.Next())
	{
		TopoDS_Face obj = TopoDS::Face(ex.Current());
		ret.emplace_back(obj);
	}

	return ret;
}

std::vector<servoce::wire_shape> servoce::shape::wires() const
{
	std::vector<servoce::wire_shape> ret;

	for (TopExp_Explorer ex(Shape(), TopAbs_WIRE); ex.More(); ex.Next())
	{
		TopoDS_Wire obj = TopoDS::Wire(ex.Current());
		ret.emplace_back(obj);
	}

	return ret;
}

std::vector<TopoDS_Edge> servoce::shape::Edges() const
{
	std::vector<TopoDS_Edge> ret;

	for (TopExp_Explorer ex(Shape(), TopAbs_EDGE); ex.More(); ex.Next())
	{
		TopoDS_Edge obj = TopoDS::Edge(ex.Current());
		ret.emplace_back(obj);
	}

	return ret;
}

std::vector<servoce::edge_shape> servoce::shape::edges() const
{
	std::vector<servoce::edge_shape> ret;

	for (TopExp_Explorer ex(Shape(), TopAbs_EDGE); ex.More(); ex.Next())
	{
		TopoDS_Edge obj = TopoDS::Edge(ex.Current());
		ret.emplace_back(obj);
	}

	return ret;
}


std::vector<servoce::shell_shape> servoce::shape::shells() const
{
	std::vector<servoce::shell_shape> ret;

	for (TopExp_Explorer ex(Shape(), TopAbs_SHELL); ex.More(); ex.Next())
	{
		TopoDS_Shell obj = TopoDS::Shell(ex.Current());
		ret.emplace_back(obj);
	}

	return ret;
}

std::vector<servoce::compound_shape> servoce::shape::compounds() const
{

	std::vector<servoce::compound_shape> ret;

	for (TopExp_Explorer ex(Shape(), TopAbs_COMPOUND); ex.More(); ex.Next())
	{
		TopoDS_Compound obj = TopoDS::Compound(ex.Current());
		ret.emplace_back(obj);
	}

	return ret;
}

std::vector<servoce::compsolid_shape> servoce::shape::compsolids() const
{

	std::vector<servoce::compsolid_shape> ret;

	for (TopExp_Explorer ex(Shape(), TopAbs_COMPSOLID); ex.More(); ex.Next())
	{
		TopoDS_CompSolid obj = TopoDS::CompSolid(ex.Current());
		ret.emplace_back(obj);
	}

	return ret;
}

servoce::face_shape servoce::near_face(const servoce::shape& shp, const servoce::point3& pnt)
{
	double min = std::numeric_limits<double>::max();
	TopoDS_Face ret;

	TopoDS_Vertex vtx = pnt.Vtx();

	for (TopExp_Explorer ex(shp.Shape(), TopAbs_FACE); ex.More(); ex.Next())
	{
		TopoDS_Face obj = TopoDS::Face(ex.Current());
		BRepExtrema_DistShapeShape extrema(obj, vtx);

		if (min > extrema.Value()) { ret = obj; min = extrema.Value(); }
	}

	return ret;
}

servoce::edge_shape servoce::near_edge(const servoce::shape& shp, const servoce::point3& pnt)
{
	double min = std::numeric_limits<double>::max();
	TopoDS_Edge ret;

	TopoDS_Vertex vtx = pnt.Vtx();

	for (TopExp_Explorer ex(shp.Shape(), TopAbs_EDGE); ex.More(); ex.Next())
	{
		TopoDS_Edge obj = TopoDS::Edge(ex.Current());
		BRepExtrema_DistShapeShape extrema(obj, vtx);

		if (min > extrema.Value()) { ret = obj; min = extrema.Value(); }
	}

	return ret;
}

servoce::shape servoce::near_vertex(const servoce::shape& shp, const servoce::point3& pnt)
{
	double min = std::numeric_limits<double>::max();
	TopoDS_Vertex ret;

	TopoDS_Vertex vtx = pnt.Vtx();

	for (TopExp_Explorer ex(shp.Shape(), TopAbs_VERTEX); ex.More(); ex.Next())
	{
		TopoDS_Vertex obj = TopoDS::Vertex(ex.Current());
		BRepExtrema_DistShapeShape extrema(obj, vtx);

		if (min > extrema.Value()) { ret = obj; min = extrema.Value(); }
	}

	return ret;
}

std::string servoce::shape::shapetype_as_string() const
{
	switch (Shape().ShapeType())
	{
		case TopAbs_WIRE: return "wire";

		case TopAbs_EDGE: return "edge";

		case TopAbs_COMPOUND: return "compound";

		case TopAbs_COMPSOLID: return "compsolid";

		case TopAbs_FACE: return "face";

		case TopAbs_SOLID: return "solid";

		case TopAbs_SHELL: return "shell";

		case TopAbs_VERTEX: return "shell";

		case TopAbs_SHAPE: return "shape";
	}

	return "undefined";
}

servoce::shape servoce::shape::fillet(double r, const std::vector<servoce::point3>& refs)
{
	return servoce::fillet(*this, r, refs);
}

servoce::shape servoce::shape::fillet(double r)
{
	return servoce::fillet(*this, r);
}

servoce::shape servoce::shape::chamfer(double r, const std::vector<servoce::point3>& refs)
{
	return servoce::chamfer(*this, r, refs);
}

servoce::shape servoce::shape::chamfer(double r)
{
	return servoce::chamfer(*this, r);
}

servoce::shape servoce::shape::fillet2d(double r, const std::vector<servoce::point3>& refs)
{
	return servoce::fillet2d(*this, r, refs);
}

servoce::shape servoce::shape::fillet2d(double r)
{
	return servoce::fillet2d(*this, r);
}

servoce::shape servoce::shape::chamfer2d(double r, const std::vector<servoce::point3>& refs)
{
	return servoce::chamfer2d(*this, r, refs);
}

servoce::shape servoce::shape::chamfer2d(double r)
{
	return servoce::chamfer2d(*this, r);
}

void servoce::shape::print_topo_dump()
{
	if (!Shape().IsNull())
	{
		std::cout << "____shape type: " << Shape().ShapeType() << "____" << std::endl;

		Handle(TopTools_HSequenceOfShape) seqShape = new TopTools_HSequenceOfShape;
		Handle(TopTools_HSequenceOfShape) compounds, compsolids, solids, shells, faces, wires, edges, vertices;

		ShapeExtend_Explorer anExp;

		anExp.SeqFromCompound(Shape(), false);
		anExp.DispatchList(seqShape, vertices, edges, wires, faces, shells, solids, compsolids, compounds);
		std::cout << "____Nb compounds: " << compounds->Length() << "____" << std::endl;
		std::cout << "____Nb compsolids: " << compsolids->Length() << "____" << std::endl;
		std::cout << "____Nb solids: " << solids->Length() << "____" << std::endl;
		std::cout << "____Nb shells: " << shells->Length() << "____" << std::endl;
		std::cout << "____Nb faces: " << faces->Length() << "____" << std::endl;
		std::cout << "____Nb wires: " << wires->Length() << "____" << std::endl;
		std::cout << "____Nb edges: " << edges->Length() << "____" << std::endl;
		std::cout << "____Nb vertices: " << vertices->Length() << "____" << std::endl;
	}
}

TopoDS_Edge servoce::shape::Edge_OrOneEdgedWireToEdge() const
{
	if (Shape().ShapeType() == TopAbs_EDGE)
	{
		return Edge();
	}

	else if (Shape().ShapeType() == TopAbs_WIRE)
	{
		auto edgs = Edges();

		if (edgs.size() > 1)
		{
			throw std::runtime_error(
			    "Attempt to extract edge from multiedged wire");
		}

		return edgs[0];
	}

	else
		throw std::runtime_error(
		    "Attempt to extract edge from uncompatible type of shape");
}


servoce::geomprops gprops(const servoce::shape& shp)
{
	switch (shp.Shape().ShapeType())
	{
		case TopAbs_VERTEX:
		case TopAbs_WIRE:
		case TopAbs_EDGE:
			return servoce::geomprops::linear_properties(shp, 1);

		case TopAbs_FACE:
		case TopAbs_SHELL:
			return servoce::geomprops::surface_properties(shp, 1);

		case TopAbs_SOLID:
		case TopAbs_COMPSOLID:
		case TopAbs_COMPOUND:
		case TopAbs_SHAPE:
			return servoce::geomprops::volume_properties(shp, 1);

		default:
			throw std::runtime_error("undefined shape");
	}
}

servoce::vector3 servoce::shape::cmradius() const
{
	return gprops(*this).cmradius();
}

double servoce::shape::mass() const
{
	return gprops(*this).mass();
}

servoce::matrix33 servoce::shape::matrix_of_inertia() const
{
	return gprops(*this).matrix_of_inertia();
}

std::tuple<double, double, double> servoce::shape::static_moments () const
{
	return gprops(*this).static_moments();
}

double servoce::shape::moment_of_inertia(const servoce::vector3& axis) const
{
	return gprops(*this).moment_of_inertia(axis);
}

double servoce::shape::radius_of_gyration(const servoce::vector3& axis) const
{
	return geomprops::volume_properties(*this, 1).radius_of_gyration(axis);
}

std::tuple<servoce::vector3, servoce::vector3, servoce::vector3> servoce::shape::principal_inertia_axes() const 
{
	return gprops(*this).principal_inertia_axes();
}

std::tuple<double, double, double> servoce::shape::principal_inertia_moments() const 
{
	return gprops(*this).principal_inertia_moments();
}

servoce::transformation servoce::shape::inertia_frame() const 
{
	return gprops(*this).inertia_frame();
}

servoce::boundbox servoce::shape::bounding_box()
{
	Bnd_Box box;
	BRepBndLib::Add(Shape(), box);
	return {box};
}


servoce::shape servoce::shape::transform(const servoce::transformation& trans) const
{
	return BRepBuilderAPI_Transform(Shape(), *trans.trsf, true).Shape();
}

servoce::shape servoce::shape::transform(const servoce::general_transformation& trans) const
{
	return BRepBuilderAPI_GTransform(Shape(), *trans.gtrsf, true).Shape();
}

servoce::geomprops servoce::shape::props1() 
{
	return geomprops::linear_properties(*this);
}

servoce::geomprops servoce::shape::props2() 
{
	return geomprops::surface_properties(*this);
}

servoce::geomprops servoce::shape::props3() 
{
	return geomprops::volume_properties(*this);
}
