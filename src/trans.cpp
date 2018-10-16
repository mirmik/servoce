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
#include <gp_Trsf.hxx>

#include <BRepBuilderAPI_Transform.hxx>

servoce::transformation::transformation(const transformation& oth) : trsf(new gp_Trsf(*oth.trsf)) {}

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

servoce::shape servoce::transformation::operator()(const servoce::shape& shp) const {
	return BRepBuilderAPI_Transform(shp.Shape(), *trsf, true).Shape();
}

servoce::transformation servoce::transformation::operator()(const servoce::transformation& oth) const {
	return *this * oth;
}

servoce::transformation  servoce::transformation::operator*(const servoce::transformation& oth) const {
	return servoce::transformation(new gp_Trsf(this->trsf->Multiplied(*oth.trsf)));
}

servoce::transformation::~transformation() { delete trsf; }

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