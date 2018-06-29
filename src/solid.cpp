#include <servoce/solid.h>

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
//#include <BRepPrimAPI_MakeWedge.hxx>
//#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <TopExp_Explorer.hxx>

#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>

#include <gxx/panic.h>

#include <gxx/print.h>

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
	//delete m_first;
	//delete m_last;
}

servoce::sweep_solid::sweep_solid(BRepPrimAPI_MakeSweep&& builder) : solid(builder.Shape()) {
	m_first = new TopoDS_Shape(builder.FirstShape());
	m_last = new TopoDS_Shape(builder.LastShape());
}

servoce::solid servoce::sweep3d::make_linear_extrude(const servoce::shape& base, const servoce::vector3& vec, bool center) {
	if (center) {
        auto trs = servoce::trans::translate(-vec/2);
        return make_linear_extrude(trs(base),vec);

        //trans::translate trs(-vec/2);
        //auto sld = make_linear_extrude(base, vec);
        //return trs(sld);

    }
    return BRepPrimAPI_MakePrism(base.Shape(), vec.Vec()).Shape();
}

servoce::solid servoce::solid::fillet(double r, const std::vector<int>& nums) {
    std::set<int>snums(nums.begin(), nums.end());
    BRepFilletAPI_MakeFillet mk(*m_shp);//
    int idx = 0;
    for (TopExp_Explorer ex(*m_shp,TopAbs_EDGE); ex.More(); ex.Next()) {
        TopoDS_Edge Edge =TopoDS::Edge(ex.Current());
        if (snums.count(idx)) mk.Add(r, Edge);
        ++idx;
    }

    return mk.Shape();
}

servoce::solid servoce::sweep3d::make_linear_extrude(const servoce::shape& base, double z, bool center) {
    return servoce::sweep3d::make_linear_extrude(base, servoce::vector3(0,0,z), center);
}

servoce::solid servoce::sweep3d::make_pipe(const servoce::shape& profile, const servoce::wire& path) {
    if (path.Shape().IsNull())
        Standard_Failure::Raise("Cannot sweep along empty spine");
    if (profile.Shape().IsNull())
        Standard_Failure::Raise("Cannot sweep empty profile");
    return BRepOffsetAPI_MakePipe(path.Wire(), profile.Shape()).Shape();
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

servoce::solid servoce::sweep3d::make_pipe_shell(
    const servoce::shape& profile, 
    const servoce::wire& path, 
    bool isFrenet
) {
    try{
        BRepOffsetAPI_MakePipeShell mkPipeShell(path.Wire());
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
    } catch (...) {
        gxx::println("ERROR");
    }


    /*if (path.Shape().IsNull())
        Standard_Failure::Raise("Cannot sweep along empty spine");
    if (profile.Shape().IsNull())
        Standard_Failure::Raise("Cannot sweep empty profile");
    return BRepOffsetAPI_MakePipe(path.Wire(), profile.Shape());*/
}