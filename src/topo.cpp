#include <servoce/topo.h>
#include <servoce/face.h>
#include <servoce/solid.h>

#include <TopoDS_Shape.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>
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

#include <TopOpeBRepBuild_Tools.hxx>

#include <TopAbs_ShapeEnum.hxx>
#include <TopExp_Explorer.hxx>
#include <GProp_GProps.hxx>
#include <BRepGProp.hxx>

#include <TopExp.hxx>

#include <algorithm>
#include <cassert>

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

TopoDS_Wire servoce::shape::Wire_orEdgeToWire() const
{
	if (Shape().ShapeType() == TopAbs_WIRE)
		return Wire();
	else
		return BRepBuilderAPI_MakeWire(Edge()).Wire();
}

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



servoce::point3 servoce::shape::center()
{
	GProp_GProps props;
	BRepGProp::LinearProperties(Shape(), props);
	gp_Pnt centerMass = props.CentreOfMass();
	return point3(centerMass);
}

//servoce::shape servoce::make_section(const servoce::shape& shp)
//{
//	TopoDS_Face face = BRepBuilderAPI_MakeFace(gp_Pln(gp_Pnt(0, 0, 0), gp_Vec(0, 0, 1)));
//	return BRepAlgoAPI_Common(shp.Shape(), face).Shape();
//}

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

std::vector<servoce::shape> servoce::shape::solids() const
{
	std::vector<servoce::shape> ret;

	for (TopExp_Explorer ex(Shape(), TopAbs_SOLID); ex.More(); ex.Next())
	{
		TopoDS_Solid obj = TopoDS::Solid(ex.Current());
		ret.emplace_back(obj);
	}

	return ret;
}

std::vector<servoce::shape> servoce::shape::faces() const
{
	std::vector<servoce::shape> ret;

	for (TopExp_Explorer ex(Shape(), TopAbs_FACE); ex.More(); ex.Next())
	{
		TopoDS_Face obj = TopoDS::Face(ex.Current());
		ret.emplace_back(obj);
	}

	return ret;
}

std::vector<servoce::shape> servoce::shape::wires() const
{
	std::vector<servoce::shape> ret;

	for (TopExp_Explorer ex(Shape(), TopAbs_WIRE); ex.More(); ex.Next())
	{
		TopoDS_Wire obj = TopoDS::Wire(ex.Current());
		ret.emplace_back(obj);
	}

	return ret;
}

std::vector<servoce::shape> servoce::shape::edges() const
{
	std::vector<servoce::shape> ret;

	for (TopExp_Explorer ex(Shape(), TopAbs_EDGE); ex.More(); ex.Next())
	{
		TopoDS_Edge obj = TopoDS::Edge(ex.Current());
		ret.emplace_back(obj);
	}

	return ret;
}

servoce::shape servoce::near_face(const servoce::shape& shp, const servoce::point3& pnt)
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

servoce::shape servoce::near_edge(const servoce::shape& shp, const servoce::point3& pnt)
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


//servoce::shape	servoce::near_face(const servoce::shape& shp, const servoce::point3& pnt) {
//
//}
//
//servoce::shape	servoce::near_edge(const servoce::shape& shp, const servoce::point3& pnt)
//{
//	return near_edge_native(shp, pnt);
//}
//
//servoce::shape 	servoce::near_vertex(const servoce::shape& shp, const servoce::point3& pnt) {
//
//}


/*servoce::shape operator+(const servoce::point3& pnt, const servoce::shape& th)
{
	return servoce::make_union(th, pnt.Vtx());
}

servoce::shape operator+(const servoce::shape& th, const servoce::point3& pnt)
{
	return servoce::make_union(th, pnt.Vtx());
}*/

std::string servoce::shape::shapetype_as_string()
{
	switch (Shape().ShapeType())
	{
		case TopAbs_WIRE: return "wire";

		case TopAbs_EDGE: return "edge";

		case TopAbs_COMPOUND: return "compound";

		case TopAbs_FACE: return "face";

		case TopAbs_SOLID: return "solid";
	}
}

servoce::BoundBox::BoundBox(const servoce::shape& shp)
{
	Bnd_Box B;
	BRepBndLib::Add(shp.Shape(), B);
	B.Get(xmin, ymin, zmin, xmax, ymax, zmax);
	xdim = xmax - xmin;
	ydim = ymax - ymin;
	zdim = zmax - zmin;
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
