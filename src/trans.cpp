#include <servoce/topo.h>
#include <local/util.h>

#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>

#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>

/*void ZenTranslate::doit() {
	trsf.SetTranslation(gp_Vec(x,y,z));
}

void ZenRotate::doit() {
	trsf.SetRotation(gp_Ax1(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)), angle);
}

void ZenAxisMirror::doit() {
	trsf.SetMirror(gp_Ax1(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)));
}

void ZenPlaneMirror::doit() {
	trsf.SetMirror(gp_Ax2(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)));
}*/

#include <gp_Trsf.hxx>
#include <BRepBuilderAPI_Transform.hxx>

gp_Trsf OCC_Trans(const servoce::trans::transformation& trsf) { 
	gp_Trsf ret; trsf.init_native(&ret); return ret; 
}

servoce::solid servoce::trans::create_transformed(const servoce::solid& shp, const servoce::trans::transformation& trans) {
	return TopoDS::Solid(BRepBuilderAPI_Transform(OCC_Shape(shp), OCC_Trans(trans), true));
}

servoce::face servoce::trans::create_transformed(const servoce::face& shp, const servoce::trans::transformation& trans) {
	return TopoDS::Face(BRepBuilderAPI_Transform(OCC_Shape(shp), OCC_Trans(trans), true));
}

servoce::wire servoce::trans::create_transformed(const servoce::wire& shp, const servoce::trans::transformation& trans) {
	return TopoDS::Wire(BRepBuilderAPI_Transform(OCC_Shape(shp), OCC_Trans(trans), true));
}

void servoce::trans::translate::init_native(gp_Trsf* trsf) const {
	trsf->SetTranslation(gp_Vec(x,y,z));
}

void servoce::trans::axrotation::init_native(gp_Trsf* trsf) const {
	trsf->SetRotation(gp_Ax1(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)), angle);
}

void servoce::trans::axis_mirror::init_native(gp_Trsf* trsf) const {
	trsf->SetMirror(gp_Ax1(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)));
}

void servoce::trans::plane_mirror::init_native(gp_Trsf* trsf) const {
	trsf->SetMirror(gp_Ax2(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)));
}

servoce::trans::axrotation servoce::trans::rotateX(double a) {
	return servoce::trans::axrotation(1,0,0,a);
}

servoce::trans::axrotation servoce::trans::rotateY(double a) {
	return servoce::trans::axrotation(0,1,0,a);
}

servoce::trans::axrotation servoce::trans::rotateZ(double a) {
	return servoce::trans::axrotation(0,0,1,a);
}

servoce::trans::axis_mirror servoce::trans::mirrorX() {
	return servoce::trans::axis_mirror(1,0,0);
}

servoce::trans::axis_mirror servoce::trans::mirrorY() {
	return servoce::trans::axis_mirror(0,1,0);
}

servoce::trans::axis_mirror servoce::trans::mirrorZ() {
	return servoce::trans::axis_mirror(0,0,1);
}

servoce::trans::plane_mirror servoce::trans::mirrorXY() {
	return servoce::trans::plane_mirror(0,0,1);
}

servoce::trans::plane_mirror servoce::trans::mirrorYZ() {
	return servoce::trans::plane_mirror(1,0,0);
}

servoce::trans::plane_mirror servoce::trans::mirrorXZ() {
	return servoce::trans::plane_mirror(0,1,0);
}
