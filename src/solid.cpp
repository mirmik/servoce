#include <servoce/solid.h>

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
//#include <BRepPrimAPI_MakePrism.hxx>
//#include <BRepPrimAPI_MakeWedge.hxx>
//#include <BRepOffsetAPI_ThruSections.hxx>
//#include <BRepOffsetAPI_MakePipe.hxx>

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
