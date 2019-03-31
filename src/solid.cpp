#include <servoce/solid.h>

#include <gp_Pln.hxx>

#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>
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
#include <BRepFilletAPI_MakeFillet.hxx>
#include <TopExp_Explorer.hxx>

#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepOffsetAPI_MakeThickSolid.hxx>

#include <BRepLib_MakeFace.hxx>
#include <BRepPrimAPI_MakeHalfSpace.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>

#include <ShapeUpgrade_UnifySameDomain.hxx>

#include <Geom_Surface.hxx>
#include <Geom_Plane.hxx>

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
	printf("shape servoce::cylinder(double r, double h, double angle, bool center) is deprecated");

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

shape servoce::cylinder(double r, double h, double a1, double a2, bool center)
{
	assert(a2 > a1);
	double diff = a2 - a1;

	assert(diff > M_PI * 2);

	if (!center)
	{
		gp_Ax2 ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(cos(a1), sin(a1), 0));
		return BRepPrimAPI_MakeCylinder(ax2, r, h, diff).Solid();
	}
	else
	{
		gp_Ax2 ax2(gp_Pnt(0, 0, -h / 2), gp_Dir(0, 0, 1), gp_Dir(cos(a1), sin(a1), 0));
		return BRepPrimAPI_MakeCylinder(ax2, r, h, diff).Solid();
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

shape servoce::cone(double r1, double r2, double h, double angle, bool center)
{
	printf("shape servoce::cone(double r1, double r2, double h, double angle, bool center) is deprecated");

	if (!center)
	{
		return BRepPrimAPI_MakeCone(r1, r2, h, angle).Solid();
	}
	else
	{
		gp_Ax2 ax2(gp_Pnt(0, 0, -h / 2), gp_Vec(0, 0, 1));
		return BRepPrimAPI_MakeCone(ax2, r1, r2, h, angle).Solid();
	}
}

shape servoce::cone(double r1, double r2, double h, double a1, double a2, bool center)
{
	assert(a2 > a1);
	double diff = a2 - a1;

	assert(diff > M_PI * 2);

	if (!center)
	{
		gp_Ax2 ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(cos(a1), sin(a1), 0));
		return BRepPrimAPI_MakeCone(ax2, r1, r2, h, diff).Solid();
	}
	else
	{
		gp_Ax2 ax2(gp_Pnt(0, 0, -h / 2), gp_Dir(0, 0, 1), gp_Dir(cos(a1), sin(a1), 0));
		return BRepPrimAPI_MakeCone(ax2, r1, r2, h, diff).Solid();
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

		//trans::translate trs(-vec/2);
		//auto sld = make_linear_extrude(base, vec);
		//return trs(sld);

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

/*shape shape::fillet(double r, const std::vector<int>& nums) {
	std::set<int>snums(nums.begin(), nums.end());
	BRepFilletAPI_MakeFillet mk(*m_shp);//
	int idx = 0;
	for (TopExp_Explorer ex(*m_shp,TopAbs_EDGE); ex.More(); ex.Next()) {
		TopoDS_Edge Edge =TopoDS::Edge(ex.Current());
		if (snums.count(idx)) mk.Add(r, Edge);
		++idx;
	}

	return mk.Shape();
}*/

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



/*TopoDS_Shape TopoShape::makePipeShell(const TopTools_ListOfShape& profiles,
									  const Standard_Boolean make_solid,
									  const Standard_Boolean isFrenet,
									  int transition) const
{
	if (this->_Shape.IsNull())
		Standard_Failure::Raise("Cannot sweep along empty spine");
	if (this->_Shape.ShapeType() != TopAbs_WIRE)
		Standard_Failure::Raise("Spine shape is not a wire");

	BRepOffsetAPI_MakePipeShell mkPipeShell(TopoDS::Wire(this->_Shape));
	BRepBuilderAPI_TransitionMode transMode;
	switch (transition) {
		case 1: transMode = BRepBuilderAPI_RightCorner;
			break;
		case 2: transMode = BRepBuilderAPI_RoundCorner;
			break;
		default: transMode = BRepBuilderAPI_Transformed;
			break;
	}
	mkPipeShell.SetMode(isFrenet);
	mkPipeShell.SetTransitionMode(transMode);
	TopTools_ListIteratorOfListOfShape it;
	for (it.Initialize(profiles); it.More(); it.Next()) {
		mkPipeShell.Add(TopoDS_Shape(it.Value()));
	}

	if (!mkPipeShell.IsReady()) Standard_Failure::Raise("shape is not ready to build");
	else mkPipeShell.Build();

	if (make_solid) mkPipeShell.MakeSolid();

	return mkPipeShell.Shape();
}*/

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

		/*BRepBuilderAPI_TransitionMode transMode;
		switch () {
			case 1: transMode = BRepBuilderAPI_RightCorner;
				break;
			case 2: transMode = BRepBuilderAPI_RoundCorner;
				break;
			default: transMode = BRepBuilderAPI_Transformed;
				break;
		}*/
		mkPipeShell.SetMode(isFrenet);
		//mkPipeShell.SetTransitionMode(transMode);

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

	/*if (path.Shape().IsNull())
		Standard_Failure::Raise("Cannot sweep along empty spine");
	if (profile.Shape().IsNull())
		Standard_Failure::Raise("Cannot sweep empty profile");
	return BRepOffsetAPI_MakePipe(path.Wire(), profile.Shape());*/
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
	//builder.SetSmoothing(smooth);

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
		facesToRemove.Append(near_face(proto,p).Face());
	
	auto algo = BRepOffsetAPI_MakeThickSolid();
	algo.MakeThickSolidByJoin(proto.Shape(), facesToRemove, thickness, 1.e-3);
	return algo.Shape();
}

shape servoce::unify(const shape& proto)
{
	ShapeUpgrade_UnifySameDomain USD(proto.Shape(), true, true, true); // UnifyFaces mode on, UnifyEdges mode on, ConcatBSplines mode on.
	USD.Build();
	return USD.Shape();
}
