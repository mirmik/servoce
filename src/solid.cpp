#include <servoce/solid.h>

#include <gp_Pln.hxx>

#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS.hxx>

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepExtrema_DistShapeShape.hxx>
//#include <BRepPrimAPI_MakeWedge.hxx>
//#include <BRepOffsetAPI_ThruSections.hxx>
#include <TopExp_Explorer.hxx>

#include <BRepBuilderAPI_MakeSolid.hxx>

#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepFilletAPI_MakeFillet2d.hxx>
#include <BRepTools_WireExplorer.hxx>

#include <BRepBuilderAPI_MakeShell.hxx>
#include <BRepOffsetAPI_Sewing.hxx>

#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepOffsetAPI_MakeThickSolid.hxx>

#include <BRepLib_MakeFace.hxx>
#include <BRepPrimAPI_MakeHalfSpace.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>

#include <ShapeUpgrade_UnifySameDomain.hxx>

#include <Geom_Surface.hxx>
#include <Geom_Plane.hxx>

#include <map>
#include <limits>

#include <exception>
#include <assert.h>

using namespace servoce;

shape servoce::box(double x, double y, double z, bool center)
{
	if (!center)
	{
		return BRepPrimAPI_MakeBox(x, y, z).Solid();
	}
	else
	{
		gp_Ax2 ax2(gp_Pnt(-x / 2, -y / 2, -z / 2), gp_Vec(0, 0, 1));
		return BRepPrimAPI_MakeBox(ax2, x, y, z).Solid();
	}
}

shape servoce::cylinder(double r, double h, bool center)
{
	if (!center)
	{
		return BRepPrimAPI_MakeCylinder(r, h).Solid();
	}
	else
	{
		gp_Ax2 ax2(gp_Pnt(0, 0, -h / 2), gp_Vec(0, 0, 1));
		return BRepPrimAPI_MakeCylinder(ax2, r, h).Solid();
	}
}

shape servoce::cylinder(double r, double h, double angle, bool center)
{
	if (!center)
	{
		return BRepPrimAPI_MakeCylinder(r, h, angle).Solid();
	}
	else
	{
		gp_Ax2 ax2(gp_Pnt(0, 0, -h / 2), gp_Vec(0, 0, 1));
		return BRepPrimAPI_MakeCylinder(ax2, r, h, angle).Solid();
	}
}

shape servoce::cone(double r1, double r2, double h, bool center)
{
	if (!center)
	{
		return BRepPrimAPI_MakeCone(r1, r2, h).Solid();
	}
	else
	{
		gp_Ax2 ax2(gp_Pnt(0, 0, -h / 2), gp_Vec(0, 0, 1));
		return BRepPrimAPI_MakeCone(ax2, r1, r2, h).Solid();
	}
}

shape servoce::cone(double r1, double r2, double h, double yaw, bool center)
{
	if (!center)
	{
		return BRepPrimAPI_MakeCone(r1, r2, h, yaw).Solid();
	}
	else
	{
		gp_Ax2 ax2(gp_Pnt(0, 0, -h / 2), gp_Vec(0, 0, 1));
		return BRepPrimAPI_MakeCone(ax2, r1, r2, h, yaw).Solid();
	}
}

shape servoce::sphere(double r) { return BRepPrimAPI_MakeSphere(r).Solid(); }
shape servoce::sphere(double r, double an1) { return BRepPrimAPI_MakeSphere(r, an1).Solid(); }
shape servoce::sphere(double r, double an1, double an2) { return BRepPrimAPI_MakeSphere(r, an1, an2).Solid(); }
shape servoce::sphere(double r, double an1, double an2, double an3) { return BRepPrimAPI_MakeSphere(r, an1, an2, an3).Solid(); }

shape servoce::torus(double r1, double r2)
{
	return BRepPrimAPI_MakeTorus(r1, r2).Solid();
}

shape servoce::torus(double r1, double r2, double ua)
{
	return BRepPrimAPI_MakeTorus(r1, r2, ua).Solid();
}

shape servoce::torus(double r1, double r2, double va1, double va2)
{
	return BRepPrimAPI_MakeTorus(r1, r2, va1, va2).Solid();
}

shape servoce::torus(double r1, double r2, double va1, double va2, double ua)
{
	return BRepPrimAPI_MakeTorus(r1, r2, va1, va2, ua).Solid();
}

shape servoce::make_linear_extrude(const shape& base, const vector3& vec, bool center)
{
	if (center)
	{
		auto trs = translate(-vec / 2);
		return make_linear_extrude(trs(base), vec);
	}

	//Этот хак необходим из-за тенденции некоторых алгоритмов opencascade создавать SOLID тогда,
	//Когда можно было бы ожидать FACE
	if (base.Shape().ShapeType() == TopAbs_SOLID)
	{
		auto fcs = base.faces();

		if (fcs.size() == 1)
		{
			return BRepPrimAPI_MakePrism(fcs[0].Face(), vec.Vec()).Shape();
		}
		else
		{
			throw std::logic_error("linear_extrude doesn't work with solids");
		}
	}

	return BRepPrimAPI_MakePrism(base.Shape(), vec.Vec()).Shape();
}

shape servoce::make_linear_extrude(const shape& base, double z, bool center)
{
	return make_linear_extrude(base, vector3(0, 0, z), center);
}

servoce::shape servoce::shape::extrude(double z, bool center)
{
	return make_linear_extrude(*this, z, center);
}

servoce::shape servoce::shape::extrude(double x, double y, double z, bool center)
{
	return make_linear_extrude(*this, vector3(x, y, z), center);
}

servoce::shape servoce::shape::extrude(const vector3& vec, bool center)
{
	return make_linear_extrude(*this, vec, center);
}

shape servoce::make_pipe(const shape& profile, const shape& path)
{
	if (path.Shape().IsNull())
		Standard_Failure::Raise("Cannot sweep along empty spine");

	if (profile.Shape().IsNull())
		Standard_Failure::Raise("Cannot sweep empty profile");

	return BRepOffsetAPI_MakePipe(path.Wire_orEdgeToWire(), profile.Shape()).Shape();
}

shape servoce::make_pipe_shell(
    const shape& profile,
    const shape& path,
    bool isFrenet
)
{
	try
	{
		BRepOffsetAPI_MakePipeShell mkPipeShell(path.Wire_orEdgeToWire());
		mkPipeShell.SetMode(isFrenet);

		mkPipeShell.SetMode(isFrenet);
		mkPipeShell.Add(profile.Shape());

		if (!mkPipeShell.IsReady()) std::logic_error("shape is not ready to build");

		mkPipeShell.Build();
		mkPipeShell.MakeSolid();

		return mkPipeShell.Shape();
	}
	catch (...)
	{
		Standard_Failure::Raise("ERROR");
	}

	return shape();
}

shape servoce::halfspace()
{
	gp_Pln P;
	TopoDS_Face F = BRepLib_MakeFace(P);
	BRepPrimAPI_MakeHalfSpace MHS(F, gp_Pnt(0, 0, -1));
	return MHS.Solid();
}

shape servoce::loft(const std::vector<shape>& vec, bool smooth)
{
	BRepOffsetAPI_ThruSections builder(Standard_True, !smooth);

	for (auto v : vec)
		if (v.Shape().ShapeType() == TopAbs_FACE)
			Standard_Failure::Raise("Loft argument must be array of WIRES");

	for (auto& r : vec)
	{
		builder.AddWire(r.Wire_orEdgeToWire());
	}

	return builder.Shape();
}

shape servoce::revol(const shape& proto, double angle)
{
	auto ax = gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));

	if (angle == 0)
		return BRepPrimAPI_MakeRevol(proto.Shape(), ax).Shape();
	else
		return BRepPrimAPI_MakeRevol(proto.Shape(), ax, angle).Shape();
}

shape servoce::thicksolid(const shape& proto, const std::vector<point3>& pnts, double thickness)
{
	TopTools_ListOfShape facesToRemove;

	for (auto p : pnts)
		facesToRemove.Append(near_face(proto, p).Face());

	auto algo = BRepOffsetAPI_MakeThickSolid();
	algo.MakeThickSolidByJoin(proto.Shape(), facesToRemove, thickness, 1.e-3);
	return algo.Shape();
}

servoce::shape servoce::fillet(const servoce::shape& shp, double r, const std::vector<servoce::point3>& refs)
{
	auto type = shp.Shape().ShapeType();

	if (TopAbs_SOLID == type || TopAbs_COMPSOLID == type || type == TopAbs_COMPOUND)
	{
		BRepFilletAPI_MakeFillet mk(shp.Shape());

		for (auto& p : refs)
		{
			mk.Add(r, near_edge(shp, p).Edge());
		}

		return mk.Shape();
	}
	else if (TopAbs_FACE == type)
	{
		std::cout << "This method deprecated for 2d faces. Use fillet2d." << std::endl;
		BRepFilletAPI_MakeFillet2d mk(shp.Face());

		for (auto& p : refs)
		{
			mk.AddFillet(near_vertex(shp, p).Vertex(), r);
		}

		return mk.Shape();
	}
	else
	{
		throw std::runtime_error("Fillet argument has unsuported type.");
	}
}

servoce::shape servoce::fillet(const servoce::shape& shp, double r)
{
	auto type = shp.Shape().ShapeType();

	if (TopAbs_SOLID == type || TopAbs_COMPSOLID == type || type == TopAbs_COMPOUND)
	{
		BRepFilletAPI_MakeFillet mk(shp.Shape());

		for (TopExp_Explorer ex(shp.Shape(), TopAbs_EDGE); ex.More(); ex.Next())
		{
			mk.Add(r, TopoDS::Edge(ex.Current()));
		}

		return mk.Shape();
	}
	else if (TopAbs_FACE == type)
	{
		std::cout << "This method deprecated for 2d faces. Use fillet2d." << std::endl;

		BRepFilletAPI_MakeFillet2d mk(shp.Face());

		for (TopExp_Explorer expWire(shp.Shape(), TopAbs_WIRE); expWire.More(); expWire.Next())
		{
			BRepTools_WireExplorer explorer(TopoDS::Wire(expWire.Current()));

			while (explorer.More())
			{
				const TopoDS_Vertex& vtx = explorer.CurrentVertex();
				mk.AddFillet(vtx, r);

				explorer.Next();
			}
		}

		return mk.Shape();
	}
	else
	{
		throw std::runtime_error("Fillet argument has unsuported type.");
	}
}

servoce::shape servoce::chamfer(const servoce::shape& shp, double r, const std::vector<servoce::point3>& refs)
{
	auto type = shp.Shape().ShapeType();

	if (TopAbs_SOLID == type || TopAbs_COMPSOLID == type || type == TopAbs_COMPOUND)
	{
		try
		{
			BRepFilletAPI_MakeChamfer mk(shp.Shape());


			TopTools_IndexedDataMapOfShapeListOfShape edgeFaceMap;
			TopExp::MapShapesAndAncestors(shp.Shape(), TopAbs_EDGE, TopAbs_FACE, edgeFaceMap);

			for (auto& p : refs)
			{
				double min = std::numeric_limits<double>::max();
				TopoDS_Edge ret;
				TopoDS_Vertex vtx = p.Vtx();

				for (TopExp_Explorer ex(shp.Shape(), TopAbs_EDGE); ex.More(); ex.Next())
				{
					TopoDS_Edge obj = TopoDS::Edge(ex.Current());
					BRepExtrema_DistShapeShape extrema(obj, vtx);

					if (min > extrema.Value()) { ret = obj; min = extrema.Value(); }
				}

				TopTools_ListOfShape list = edgeFaceMap.FindFromKey(ret);
				mk.Add(r, ret, TopoDS::Face(list.First()));
			}

			return mk.Shape();
		}
		catch (std::exception ex)
		{
			std::cout << ex.what() << std::endl;
			throw ex;
		}
	}
	else if (TopAbs_FACE == type)
	{
		throw std::runtime_error("Face chamfer. TODO.");
	}
	else
	{
		throw std::runtime_error("Fillet argument has unsuported type.");
	}
}


servoce::shape servoce::chamfer(const servoce::shape& shp, double r)
{
	auto type = shp.Shape().ShapeType();

	if (TopAbs_SOLID == type || TopAbs_COMPSOLID == type || type == TopAbs_COMPOUND)
	{
		BRepFilletAPI_MakeChamfer mk(shp.Shape());

		TopTools_IndexedDataMapOfShapeListOfShape edgeFaceMap;
		TopExp::MapShapesAndAncestors(shp.Shape(), TopAbs_EDGE, TopAbs_FACE, edgeFaceMap);

		for (TopExp_Explorer ex(shp.Shape(), TopAbs_EDGE); ex.More(); ex.Next())
		{
			TopTools_ListOfShape list = edgeFaceMap.FindFromKey(ex.Current());

			// Find adjacent face
			mk.Add(r, TopoDS::Edge(ex.Current()), TopoDS::Face(list.First()));
		}

		return mk.Shape();
	}
	else if (TopAbs_FACE == type)
	{
		throw std::runtime_error("Face chamfer. TODO.");
	}
	else
	{
		throw std::runtime_error("Fillet argument has unsuported type.");
	}
}

shape _unify_face(const servoce::shape& proto)
{
	ShapeUpgrade_UnifySameDomain USD(proto.Shape(), true, true, true); // UnifyFaces mode on, UnifyEdges mode on, ConcatBSplines mode on.
	USD.Build();
	return USD.Shape();
}

#include <BOPTools_AlgoTools.hxx>
#include <GeomAPI_IntSS.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <servoce/boolops.h>

std::vector<servoce::shape> _unify_faces_array(const std::vector<servoce::shape>& input)
{
	std::vector<servoce::shape> ret;
	ret.reserve(input.size());
	std::map<Handle(Geom_Plane), std::vector<const servoce::shape*>> fset;

	for (const servoce::shape& i : input)
	{
		Handle(Geom_Surface) surface = BRep_Tool::Surface(i.Face());

		BRepAdaptor_Surface adaptor_surface(i.Face());
		GeomAbs_SurfaceType surface_type = adaptor_surface.GetType();

		if (surface_type == GeomAbs_Plane)
		{
			Handle(Geom_Plane) pln = Handle(Geom_Plane)::DownCast(surface);
			gp_Pln pln0 = pln->Pln();

			bool found = false;

			for (auto& pr : fset)
			{
				Handle(Geom_Plane) key = pr.first;
				std::vector<const servoce::shape*>& arr = pr.second;

				gp_Pnt pnt;
				key->D0(0, 0, pnt);
				gp_Pln pln1 = key->Pln();

				auto dir0 = pln0.Axis().Direction();
				auto dir1 = pln1.Axis().Direction();

				//PRINT(dir0.IsEqual(dir1, 0.00001));
				//PRINT(pln0.Distance(pln1.Axis().Location()));
				//PRINT(pln1.Distance(pln0.Axis().Location()));

				if (
				    dir0.IsEqual(dir1, 0.00001) &&
				    abs(pln0.Distance(pln1.Axis().Location())) < 0.0000001 &&
				    abs(pln1.Distance(pln0.Axis().Location())) < 0.0000001)
				{
					found = true;
					arr.emplace_back(&i);
					break;
				}
			}

			if (found == false)
				fset.emplace(std::make_pair(pln, std::vector<const servoce::shape*> {&i}));
		}

		else
		{
			ret.emplace_back(i);
			continue;
		}
	}

	for (auto pr : fset)
	{
		auto farr = servoce::make_union(pr.second);
		ret.emplace_back(_unify_face(farr));
	}

	return ret;
}

shape _unify_shell(const servoce::shape& proto)
{
	std::vector<servoce::shape> faces;

	BRepOffsetAPI_Sewing mkShell;

	auto newfaces = _unify_faces_array(proto.faces());
	//PRINT(newfaces.size());

	for (servoce::shape& n : newfaces)
		mkShell.Add(n.Shape());

	mkShell.Perform();
	return mkShell.SewedShape();
}

shape _unify_solid(const servoce::shape& proto)
{
	BRepBuilderAPI_MakeSolid mkSolid;
	TopExp_Explorer explorer;

	for (explorer.Init(proto.Shape(), TopAbs_SHELL); explorer.More(); explorer.Next())
	{
		mkSolid.Add(_unify_shell(explorer.Current()).Shell());
	}

	mkSolid.Build();
	return mkSolid.Shape();
}

shape _unify_compound(const servoce::shape& proto)
{
	BRep_Builder builder;
	TopoDS_Compound comp;
	builder.MakeCompound(comp);

	TopExp_Explorer explorer;

	for (explorer.Init(proto.Shape(), TopAbs_SOLID); explorer.More(); explorer.Next())
	{
		builder.Add(comp, _unify_solid(explorer.Current()).Solid());
	}

	for (explorer.Init(proto.Shape(), TopAbs_SHELL, TopAbs_SOLID); explorer.More(); explorer.Next())
	{
		builder.Add(comp, _unify_shell(explorer.Current()).Shell());
	}

	std::vector<servoce::shape> faces;

	for (explorer.Init(proto.Shape(), TopAbs_FACE, TopAbs_SHELL); explorer.More(); explorer.Next())
	{
		faces.emplace_back(explorer.Current());
	}

	auto faces_new = _unify_faces_array(faces);

	for (auto& f : faces_new)
	{
		builder.Add(comp, f.Shape());
	}


	return comp;
}

shape servoce::unify(const shape& proto)
{
	const TopoDS_Shape& _Shape = proto.Shape();

	if (_Shape.IsNull()) Standard_Failure::Raise("Cannot remove splitter from empty shape");
	else if (_Shape.ShapeType() == TopAbs_SOLID) return _unify_solid(proto);
	//else if (_Shape.ShapeType() == TopAbs_SHELL) return _unify_shell(proto);
	//else if (_Shape.ShapeType() == TopAbs_FACE)	return _unify_face(proto);
	else if (_Shape.ShapeType() == TopAbs_COMPOUND) return _unify_compound(proto);
	else Standard_Failure::Raise("TODO");

	return shape();
}
