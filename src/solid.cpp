#include <servoce/solid.h>

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
//#include <BRepPrimAPI_MakeWedge.hxx>
//#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>

#include <gxx/panic.h>

servoce::solid servoce::prim3d::make_box(double x, double y, double z, bool center) {
	if (!center) {
		return BRepPrimAPI_MakeBox(x, y, z).Solid(); 
	} else {
		gp_Ax2 ax2(gp_Pnt(-x/2,-y/2,-z/2), gp_Vec(0,0,1));
		return BRepPrimAPI_MakeBox(ax2, x, y, z).Solid(); 			
	}
}
servoce::solid servoce::prim3d::make_cylinder(double r, double h, bool center) { 
	if (!center) {
		return BRepPrimAPI_MakeCylinder(r, h).Solid(); 
	} else {
		gp_Ax2 ax2(gp_Pnt(0,0,-h/2), gp_Vec(0,0,1));
		return BRepPrimAPI_MakeCylinder(ax2, r, h).Solid(); 		
	}
}

servoce::solid servoce::prim3d::make_cone(double r1, double r2, double h, bool center) { 
	if (!center) {
		return BRepPrimAPI_MakeCone(r1, r2, h).Solid(); 
	} else {
		gp_Ax2 ax2(gp_Pnt(0,0,-h/2), gp_Vec(0,0,1));
		return BRepPrimAPI_MakeCone(ax2, r1, r2, h).Solid(); 		
	}
}

servoce::solid servoce::prim3d::make_sphere(double r) { 
	return BRepPrimAPI_MakeSphere(r).Solid(); 
}

servoce::solid servoce::prim3d::make_torus(double r1, double r2) { 
	return BRepPrimAPI_MakeTorus(r1,r2).Solid(); 
}

servoce::sweep_solid::~sweep_solid() {
	delete m_first;
	delete m_last;
}

servoce::sweep_solid::sweep_solid(BRepPrimAPI_MakeSweep&& builder) : solid(builder.Shape()) {
	m_first = new TopoDS_Shape(builder.FirstShape());
	m_last = new TopoDS_Shape(builder.LastShape());
}

servoce::sweep_solid servoce::sweep3d::make_linear_extrude(const servoce::shape& base, const servoce::vector3& vec) {
	return BRepPrimAPI_MakePrism(base.Shape(), vec.Vec());
}

servoce::sweep_solid servoce::sweep3d::make_pipe(const servoce::shape& profile, const servoce::wire& path) {
    if (path.Shape().IsNull())
        Standard_Failure::Raise("Cannot sweep along empty spine");
    if (profile.Shape().IsNull())
        Standard_Failure::Raise("Cannot sweep empty profile");
    return BRepOffsetAPI_MakePipe(path.Wire(), profile.Shape());
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

    if (make_solid)	mkPipeShell.MakeSolid();

    return mkPipeShell.Shape();
}*/
