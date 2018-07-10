#include <servoce/topo.h>
#include <servoce/trans.h>
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

//gp_Trsf OCC_Trans(const servoce::transformation& trsf) { 
//	gp_Trsf ret; trsf.init_native(&ret); return ret; 
//}

//servoce::solid servoce::create_transformed(const servoce::solid& shp, const servoce::transformation& trans) {
//	return BRepBuilderAPI_Transform(shp.Shape(), OCC_Trans(trans), true).Shape();
//}
//
//servoce::face servoce::create_transformed(const servoce::face& shp, const servoce::transformation& trans) {
//	return BRepBuilderAPI_Transform(shp.Shape(), OCC_Trans(trans), true).Shape();
//}
//
//servoce::wire servoce::create_transformed(const servoce::wire& shp, const servoce::transformation& trans) {
//	return BRepBuilderAPI_Transform(shp.Shape(), OCC_Trans(trans), true).Shape();
//}
//
//servoce::shape servoce::create_transformed(const servoce::shape& shp, const servoce::transformation& trans) {
//	return BRepBuilderAPI_Transform(shp.Shape(), OCC_Trans(trans), true).Shape();
//}
//
//servoce::point3 servoce::create_transformed(const servoce::point3& pnt, const servoce::transformation& trans) {
//	auto p = pnt.Pnt();
//	p.Transform(OCC_Trans(trans));
//	return servoce::point3(p.X(), p.Y(), p.Z());
//}
//
//servoce::vector3 servoce::create_transformed(const servoce::vector3& pnt, const servoce::transformation& trans) {
//	auto v = pnt.Vec();
//	v.Transform(OCC_Trans(trans));
//	return servoce::vector3(v.X(), v.Y(), v.Z());
//}

//void servoce::translate::init_native(gp_Trsf* trsf) const {
//	trsf->SetTranslation(gp_Vec(x,y,z));
//}
//
//void servoce::axrotation::init_native(gp_Trsf* trsf) const {
//	trsf->SetRotation(gp_Ax1(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)), angle);
//}
//
//void servoce::axis_mirror::init_native(gp_Trsf* trsf) const {
//	trsf->SetMirror(gp_Ax1(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)));
//}
//
//void servoce::plane_mirror::init_native(gp_Trsf* trsf) const {
//	trsf->SetMirror(gp_Ax2(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)));
//}
/*
servoce::transformation::transformation(const transformation& oth) : trsf(new gp_Trsf(*oth.trsf)) {}
*/
servoce::transformation servoce::rotateX(double a) {
	return servoce::axrotation(1,0,0,a);
}

servoce::transformation servoce::rotateY(double a) {
	return servoce::axrotation(0,1,0,a);
}

servoce::transformation servoce::rotateZ(double a) {
	return servoce::axrotation(0,0,1,a);
}

servoce::transformation servoce::mirrorX() {
	return servoce::axis_mirror(1,0,0);
}

servoce::transformation servoce::mirrorY() {
	return servoce::axis_mirror(0,1,0);
}

servoce::transformation servoce::mirrorZ() {
	return servoce::axis_mirror(0,0,1);
}

servoce::transformation servoce::mirrorXY() {
	return servoce::plane_mirror(0,0,1);
}

servoce::transformation servoce::mirrorYZ() {
	return servoce::plane_mirror(1,0,0);
}

servoce::transformation servoce::mirrorXZ() {
	return servoce::plane_mirror(0,1,0);
}

/*servoce::solid servoce::transformation::operator()(const servoce::solid& shp) const {
	return BRepBuilderAPI_Transform(shp.Shape(), *trsf, true).Shape();
}

servoce::face servoce::transformation::operator()(const servoce::face& shp) const {
	return BRepBuilderAPI_Transform(shp.Shape(), *trsf, true).Shape();
}

servoce::wire servoce::transformation::operator()(const servoce::wire& shp) const {
	return BRepBuilderAPI_Transform(shp.Shape(), *trsf, true).Shape();
}*/

servoce::shape servoce::transformation::operator()(const servoce::shape& shp) const {
	return BRepBuilderAPI_Transform(shp.Shape(), *trsf, true).Shape();
}
/*
servoce::point3 servoce::transformation::operator()(const servoce::point3& pnt) const {
	gp_Pnt ret = pnt.Pnt();
	ret.Transform(*trsf); 
	return ret; 
}

servoce::vector3 servoce::transformation::operator()(const servoce::vector3& pnt) const {
	//gp_Vec ret = pnt.Vec();
	//ret.Transform(*trsf); 
	//return ret; 

	return pnt.Vec().Transformed(*trsf);
}

servoce::transformation servoce::transformation::operator()(const servoce::transformation& oth) const {
	return *this * oth;
}
*/
servoce::transformation  servoce::transformation::operator*(const servoce::transformation& oth) const {
	return servoce::transformation(new gp_Trsf(this->trsf->Multiplied(*oth.trsf)));
}
/*
/*servoce::complex_transformation::complex_transformation(gp_Trsf* left, gp_Trsf* right) {
	trsf = new gp_Trsf(left->Multiplied(*right));
}*/

servoce::transformation::~transformation() { delete trsf; }

/*servoce::translate::translate(double x, double y, double z) : x(x), y(y), z(z) {
	trsf = new gp_Trsf();
	trsf->SetTranslation(gp_Vec(x,y,z));
} */


servoce::transformation servoce::translate(double x, double y) {
	return servoce::translate(x, y, 0);
}

servoce::transformation servoce::translate(double x, double y, double z) {
	auto trsf = new gp_Trsf();
	trsf->SetTranslation(gp_Vec(x,y,z));
	return servoce::transformation(trsf);
}

servoce::transformation servoce::translate(const vector3& vec) {
	return servoce::translate(vec.x, vec.y, vec.z);
}

servoce::transformation servoce::axrotation(double ax, double ay, double az, double angle) {
	auto trsf = new gp_Trsf();
	trsf->SetRotation(gp_Ax1(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)), angle);
	return servoce::transformation(trsf);
}

servoce::transformation servoce::axis_mirror(double ax, double ay, double az) {
	auto trsf = new gp_Trsf();
	trsf->SetMirror(gp_Ax1(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)));
	return servoce::transformation(trsf);
}

servoce::transformation servoce::plane_mirror(double ax, double ay, double az) {
	auto trsf = new gp_Trsf();
	trsf->SetMirror(gp_Ax2(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)));
	return servoce::transformation(trsf);
}

/*servoce::translate::translate(double x, double y) : translate(x,y,0) {} 
servoce::translate::translate(const vector3& vec) : translate(vec.x,vec.y,vec.z) {} 

servoce::axrotation::axrotation(double ax, double ay, double az, double angle) : ax(ax), ay(ay), az(az), angle(angle) {
	trsf = new gp_Trsf();
	trsf->SetRotation(gp_Ax1(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)), angle);	
}

servoce::axis_mirror::axis_mirror(double ax, double ay, double az) : ax(ax), ay(ay), az(az) {
	trsf = new gp_Trsf();
	trsf->SetMirror(gp_Ax1(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)));
}

servoce::plane_mirror::plane_mirror(double ax, double ay, double az) : ax(ax), ay(ay), az(az) {
	trsf = new gp_Trsf();
	trsf->SetMirror(gp_Ax2(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)));
}*/

servoce::transformation servoce::up(double z){
	return servoce::translate(0,0,z);
}

servoce::transformation servoce::down(double z){
	return servoce::translate(0,0,-z);
}

servoce::transformation servoce::forw(double y){
	return servoce::translate(0,y,0);
}

servoce::transformation servoce::back(double y){
	return servoce::translate(0,-y,0);
}

servoce::transformation servoce::left(double x){
	return servoce::translate(-x,0,0);
}

servoce::transformation servoce::right(double x){
	return servoce::translate(x,0,0);
}


void servoce::transformation::dump(std::ostream& out) const {
	out.write((char*)trsf, sizeof(gp_Trsf));
}

void servoce::transformation::load(std::istream& in) {
	in.read((char*)trsf, sizeof(gp_Trsf));
}

std::string servoce::transformation::string_dump() const {
	std::stringstream sstrm;
	dump(sstrm);
	return sstrm.str();

}

servoce::transformation servoce::transformation::restore_string_dump(const std::string& in) {
	std::stringstream sstrm(in);
	servoce::transformation tr;
	tr.trsf = new gp_Trsf;
	tr.load(sstrm);
	return tr;
}