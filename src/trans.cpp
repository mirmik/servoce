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

#include <gxx/print.h>
#include <gp_Trsf.hxx>
#include <BRepBuilderAPI_Transform.hxx>

//gp_Trsf OCC_Trans(const servoce::trans::transformation& trsf) { 
//	gp_Trsf ret; trsf.init_native(&ret); return ret; 
//}

//servoce::solid servoce::trans::create_transformed(const servoce::solid& shp, const servoce::trans::transformation& trans) {
//	return BRepBuilderAPI_Transform(shp.Shape(), OCC_Trans(trans), true).Shape();
//}
//
//servoce::face servoce::trans::create_transformed(const servoce::face& shp, const servoce::trans::transformation& trans) {
//	return BRepBuilderAPI_Transform(shp.Shape(), OCC_Trans(trans), true).Shape();
//}
//
//servoce::wire servoce::trans::create_transformed(const servoce::wire& shp, const servoce::trans::transformation& trans) {
//	return BRepBuilderAPI_Transform(shp.Shape(), OCC_Trans(trans), true).Shape();
//}
//
//servoce::shape servoce::trans::create_transformed(const servoce::shape& shp, const servoce::trans::transformation& trans) {
//	return BRepBuilderAPI_Transform(shp.Shape(), OCC_Trans(trans), true).Shape();
//}
//
//servoce::point3 servoce::trans::create_transformed(const servoce::point3& pnt, const servoce::trans::transformation& trans) {
//	auto p = pnt.Pnt();
//	p.Transform(OCC_Trans(trans));
//	return servoce::point3(p.X(), p.Y(), p.Z());
//}
//
//servoce::vector3 servoce::trans::create_transformed(const servoce::vector3& pnt, const servoce::trans::transformation& trans) {
//	auto v = pnt.Vec();
//	v.Transform(OCC_Trans(trans));
//	return servoce::vector3(v.X(), v.Y(), v.Z());
//}

//void servoce::trans::translate::init_native(gp_Trsf* trsf) const {
//	trsf->SetTranslation(gp_Vec(x,y,z));
//}
//
//void servoce::trans::axrotation::init_native(gp_Trsf* trsf) const {
//	trsf->SetRotation(gp_Ax1(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)), angle);
//}
//
//void servoce::trans::axis_mirror::init_native(gp_Trsf* trsf) const {
//	trsf->SetMirror(gp_Ax1(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)));
//}
//
//void servoce::trans::plane_mirror::init_native(gp_Trsf* trsf) const {
//	trsf->SetMirror(gp_Ax2(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)));
//}

servoce::trans::transformation::transformation(const transformation& oth) : trsf(new gp_Trsf(*oth.trsf)) {}

servoce::trans::transformation servoce::trans::rotateX(double a) {
	return servoce::trans::axrotation(1,0,0,a);
}

servoce::trans::transformation servoce::trans::rotateY(double a) {
	return servoce::trans::axrotation(0,1,0,a);
}

servoce::trans::transformation servoce::trans::rotateZ(double a) {
	return servoce::trans::axrotation(0,0,1,a);
}

servoce::trans::transformation servoce::trans::mirrorX() {
	return servoce::trans::axis_mirror(1,0,0);
}

servoce::trans::transformation servoce::trans::mirrorY() {
	return servoce::trans::axis_mirror(0,1,0);
}

servoce::trans::transformation servoce::trans::mirrorZ() {
	return servoce::trans::axis_mirror(0,0,1);
}

servoce::trans::transformation servoce::trans::mirrorXY() {
	return servoce::trans::plane_mirror(0,0,1);
}

servoce::trans::transformation servoce::trans::mirrorYZ() {
	return servoce::trans::plane_mirror(1,0,0);
}

servoce::trans::transformation servoce::trans::mirrorXZ() {
	return servoce::trans::plane_mirror(0,1,0);
}

servoce::solid servoce::trans::transformation::operator()(const servoce::solid& shp) const {
	return BRepBuilderAPI_Transform(shp.Shape(), *trsf, true).Shape();
}

servoce::face servoce::trans::transformation::operator()(const servoce::face& shp) const {
	return BRepBuilderAPI_Transform(shp.Shape(), *trsf, true).Shape();
}

servoce::wire servoce::trans::transformation::operator()(const servoce::wire& shp) const {
	return BRepBuilderAPI_Transform(shp.Shape(), *trsf, true).Shape();
}

servoce::shape servoce::trans::transformation::operator()(const servoce::shape& shp) const {
	return BRepBuilderAPI_Transform(shp.Shape(), *trsf, true).Shape();
}

servoce::point3 servoce::trans::transformation::operator()(const servoce::point3& pnt) const {
	gp_Pnt ret = pnt.Pnt();
	ret.Transform(*trsf); 
	return ret; 
}

servoce::vector3 servoce::trans::transformation::operator()(const servoce::vector3& pnt) const {
	//gp_Vec ret = pnt.Vec();
	//ret.Transform(*trsf); 
	//return ret; 

	return pnt.Vec().Transformed(*trsf);
}

servoce::trans::transformation servoce::trans::transformation::operator()(const servoce::trans::transformation& oth) const {
	return *this * oth;
}

servoce::trans::transformation  servoce::trans::transformation::operator*(const servoce::trans::transformation& oth) const {
	return servoce::trans::transformation(new gp_Trsf(this->trsf->Multiplied(*oth.trsf)));
}

/*servoce::trans::complex_transformation::complex_transformation(gp_Trsf* left, gp_Trsf* right) {
	trsf = new gp_Trsf(left->Multiplied(*right));
}*/

servoce::trans::transformation::~transformation() {
	delete trsf;
}

/*servoce::trans::translate::translate(double x, double y, double z) : x(x), y(y), z(z) {
	trsf = new gp_Trsf();
	trsf->SetTranslation(gp_Vec(x,y,z));
} */


servoce::trans::transformation servoce::trans::translate(double x, double y) {
	return servoce::trans::translate(x, y, 0);
}

servoce::trans::transformation servoce::trans::translate(double x, double y, double z) {
	auto trsf = new gp_Trsf();
	trsf->SetTranslation(gp_Vec(x,y,z));
	return servoce::trans::transformation(trsf);
}

servoce::trans::transformation servoce::trans::translate(const vector3& vec) {
	return servoce::trans::translate(vec.x, vec.y, vec.z);
}

servoce::trans::transformation servoce::trans::axrotation(double ax, double ay, double az, double angle) {
	auto trsf = new gp_Trsf();
	trsf->SetRotation(gp_Ax1(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)), angle);
	return servoce::trans::transformation(trsf);
}

servoce::trans::transformation servoce::trans::axis_mirror(double ax, double ay, double az) {
	auto trsf = new gp_Trsf();
	trsf->SetMirror(gp_Ax1(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)));
	return servoce::trans::transformation(trsf);
}

servoce::trans::transformation servoce::trans::plane_mirror(double ax, double ay, double az) {
	auto trsf = new gp_Trsf();
	trsf->SetMirror(gp_Ax2(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)));
	return servoce::trans::transformation(trsf);
}

/*servoce::trans::translate::translate(double x, double y) : translate(x,y,0) {} 
servoce::trans::translate::translate(const vector3& vec) : translate(vec.x,vec.y,vec.z) {} 

servoce::trans::axrotation::axrotation(double ax, double ay, double az, double angle) : ax(ax), ay(ay), az(az), angle(angle) {
	trsf = new gp_Trsf();
	trsf->SetRotation(gp_Ax1(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)), angle);	
}

servoce::trans::axis_mirror::axis_mirror(double ax, double ay, double az) : ax(ax), ay(ay), az(az) {
	trsf = new gp_Trsf();
	trsf->SetMirror(gp_Ax1(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)));
}

servoce::trans::plane_mirror::plane_mirror(double ax, double ay, double az) : ax(ax), ay(ay), az(az) {
	trsf = new gp_Trsf();
	trsf->SetMirror(gp_Ax2(gp_Pnt(0,0,0), gp_Vec(ax,ay,az)));
}*/

servoce::trans::transformation servoce::trans::up(double z){
	return servoce::trans::translate(0,0,z);
}

servoce::trans::transformation servoce::trans::down(double z){
	return servoce::trans::translate(0,0,-z);
}

servoce::trans::transformation servoce::trans::forw(double y){
	return servoce::trans::translate(0,y,0);
}

servoce::trans::transformation servoce::trans::back(double y){
	return servoce::trans::translate(0,-y,0);
}

servoce::trans::transformation servoce::trans::left(double x){
	return servoce::trans::translate(-x,0,0);
}

servoce::trans::transformation servoce::trans::right(double x){
	return servoce::trans::translate(x,0,0);
}


void servoce::trans::transformation::dump(std::ostream& out) const {
	out.write((char*)trsf, sizeof(gp_Trsf));
}

void servoce::trans::transformation::load(std::istream& in) {
	in.read((char*)trsf, sizeof(gp_Trsf));
}

std::string servoce::trans::transformation::string_dump() const {
	std::stringstream sstrm;
	dump(sstrm);
	return sstrm.str();

}

servoce::trans::transformation servoce::trans::transformation::restore_string_dump(const std::string& in) {
	std::stringstream sstrm(in);
	servoce::trans::transformation tr;
	tr.trsf = new gp_Trsf;
	tr.load(sstrm);
	return tr;
}