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
#include <gp_Quaternion.hxx>
#include <gp_GTrsf.hxx>

#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_GTransform.hxx>

servoce::transformation::transformation(const transformation& oth)
	: trsf(new gp_Trsf(*oth.trsf)) {}

servoce::general_transformation::general_transformation(const general_transformation& oth)
	: gtrsf(new gp_GTrsf(*oth.gtrsf)) {}

servoce::transformation servoce::rotate(const servoce::vector3& vec, double a)
{
	return servoce::axrotation(vec.x, vec.y, vec.z, a);
}

servoce::transformation servoce::rotateX(double a)
{
	return servoce::axrotation(1, 0, 0, a);
}

servoce::transformation servoce::rotateY(double a)
{
	return servoce::axrotation(0, 1, 0, a);
}

servoce::transformation servoce::rotateZ(double a)
{
	return servoce::axrotation(0, 0, 1, a);
}

servoce::transformation servoce::mirrorX()
{
	return servoce::axis_mirror(1, 0, 0);
}

servoce::transformation servoce::mirrorY()
{
	return servoce::axis_mirror(0, 1, 0);
}

servoce::transformation servoce::mirrorZ()
{
	return servoce::axis_mirror(0, 0, 1);
}

servoce::transformation servoce::mirrorXY()
{
	return servoce::plane_mirror(0, 0, 1);
}

servoce::transformation servoce::mirrorYZ()
{
	return servoce::plane_mirror(1, 0, 0);
}

servoce::transformation servoce::mirrorXZ()
{
	return servoce::plane_mirror(0, 1, 0);
}

servoce::transformation servoce::transformation::invert()
{
	gp_Trsf pr = trsf->Inverted();
	return transformation(new gp_Trsf(pr));
}

servoce::shape servoce::transformation::operator()(const servoce::shape& shp) const
{
	return BRepBuilderAPI_Transform(shp.Shape(), *trsf, true).Shape();
}

servoce::vector3 servoce::transformation::operator()(const servoce::vector3& vec) const
{
	return vec.Vec().Transformed(*trsf);
}

servoce::point3 servoce::transformation::operator()(const servoce::point3& pnt) const
{
	return pnt.Pnt().Transformed(*trsf);
}

servoce::shape servoce::general_transformation::operator()(const servoce::shape& shp) const
{
	return BRepBuilderAPI_GTransform(shp.Shape(), *gtrsf, true).Shape();
}

servoce::transformation servoce::transformation::operator()(const servoce::transformation& oth) const
{
	return *this * oth;
}

servoce::transformation  servoce::transformation::operator*(const servoce::transformation& oth) const
{
	return servoce::transformation(new gp_Trsf(this->trsf->Multiplied(*oth.trsf)));
}

servoce::transformation::~transformation()
{
	delete trsf;
}
servoce::general_transformation::~general_transformation()
{
	delete gtrsf;
}

servoce::transformation servoce::translate(double x, double y)
{
	return servoce::translate(x, y, 0);
}

servoce::transformation servoce::translate(double x, double y, double z)
{
	auto trsf = new gp_Trsf();
	trsf->SetTranslation(gp_Vec(x, y, z));
	return servoce::transformation(trsf);
}

servoce::transformation servoce::scale(double s, point3 center)
{
	auto trsf = new gp_Trsf();
	trsf->SetScale(center.Pnt(), s);
	return servoce::transformation(trsf);
}

servoce::general_transformation servoce::scaleX(double s)
{
	auto gtrsf = new gp_GTrsf();
	gtrsf->SetVectorialPart(gp_Mat(s, 0, 0, 0, 1, 0, 0, 0, 1));
	return servoce::general_transformation(gtrsf);
}

servoce::general_transformation servoce::scaleY(double s)
{
	auto gtrsf = new gp_GTrsf();
	gtrsf->SetVectorialPart(gp_Mat(1, 0, 0, 0, s, 0, 0, 0, 1));
	return servoce::general_transformation(gtrsf);
}

servoce::general_transformation servoce::scaleZ(double s)
{
	auto gtrsf = new gp_GTrsf();
	gtrsf->SetVectorialPart(gp_Mat(1, 0, 0, 0, 1, 0, 0, 0, s));
	return servoce::general_transformation(gtrsf);
}

servoce::general_transformation servoce::scaleXY(double x, double y)
{
	auto gtrsf = new gp_GTrsf();
	gtrsf->SetVectorialPart(gp_Mat(x, 0, 0, 0, y, 0, 0, 0, 1));
	return servoce::general_transformation(gtrsf);
}

servoce::general_transformation servoce::scaleYZ(double y, double z)
{
	auto gtrsf = new gp_GTrsf();
	gtrsf->SetVectorialPart(gp_Mat(1, 0, 0, 0, y, 0, 0, 0, z));
	return servoce::general_transformation(gtrsf);
}

servoce::general_transformation servoce::scaleXZ(double x, double z)
{
	auto gtrsf = new gp_GTrsf();
	gtrsf->SetVectorialPart(gp_Mat(x, 0, 0, 0, 1, 0, 0, 0, z));
	return servoce::general_transformation(gtrsf);
}

servoce::general_transformation servoce::scaleXYZ(double x, double y, double z)
{
	auto gtrsf = new gp_GTrsf();
	gtrsf->SetVectorialPart(gp_Mat(x, 0, 0, 0, y, 0, 0, 0, z));
	return servoce::general_transformation(gtrsf);
}

servoce::transformation servoce::translate(const vector3& vec)
{
	return servoce::translate(vec.x, vec.y, vec.z);
}

servoce::transformation servoce::axrotation(double ax, double ay, double az, double angle)
{
	auto trsf = new gp_Trsf();
	trsf->SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Vec(ax, ay, az)), angle);
	return servoce::transformation(trsf);
}

servoce::transformation servoce::axis_mirror(double ax, double ay, double az)
{
	auto trsf = new gp_Trsf();
	trsf->SetMirror(gp_Ax1(gp_Pnt(0, 0, 0), gp_Vec(ax, ay, az)));
	return servoce::transformation(trsf);
}

servoce::transformation servoce::plane_mirror(double ax, double ay, double az)
{
	auto trsf = new gp_Trsf();
	trsf->SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Vec(ax, ay, az)));
	return servoce::transformation(trsf);
}

servoce::transformation servoce::up(double z)
{
	return servoce::translate(0, 0, z);
}

servoce::transformation servoce::down(double z)
{
	return servoce::translate(0, 0, -z);
}

servoce::transformation servoce::forw(double y)
{
	return servoce::translate(0, y, 0);
}

servoce::transformation servoce::back(double y)
{
	return servoce::translate(0, -y, 0);
}

servoce::transformation servoce::left(double x)
{
	return servoce::translate(-x, 0, 0);
}

servoce::transformation servoce::right(double x)
{
	return servoce::translate(x, 0, 0);
}


void servoce::transformation::dump(std::ostream& out) const
{
	out.write((char*)trsf, sizeof(gp_Trsf));
}

void servoce::general_transformation::dump(std::ostream& out) const
{
	out.write((char*)gtrsf, sizeof(gp_GTrsf));
}

void servoce::transformation::load(std::istream& in)
{
	in.read((char*)trsf, sizeof(gp_Trsf));
}

void servoce::general_transformation::load(std::istream& in)
{
	in.read((char*)gtrsf, sizeof(gp_GTrsf));
}

std::string servoce::transformation::string_dump() const
{
	std::stringstream sstrm;
	dump(sstrm);
	return sstrm.str();

}

servoce::transformation servoce::transformation::restore_string_dump(const std::string& in)
{
	std::stringstream sstrm(in);
	servoce::transformation tr;
	tr.trsf = new gp_Trsf;
	tr.load(sstrm);
	return tr;
}

std::string servoce::general_transformation::string_dump() const
{
	std::stringstream sstrm;
	dump(sstrm);
	return sstrm.str();
}

servoce::general_transformation servoce::general_transformation::restore_string_dump(const std::string& in)
{
	std::stringstream sstrm(in);
	servoce::general_transformation tr;
	tr.gtrsf = new gp_GTrsf;
	tr.load(sstrm);
	return tr;
}

servoce::transformation servoce::nulltrans()
{
	return servoce::transformation(new gp_Trsf());
}

std::vector<double>  servoce::transformation::translation_part() const
{
	auto tr = trsf->TranslationPart();
	return {tr.X(), tr.Y(), tr.Z()};
}

std::vector<double> servoce::transformation::rotation_part() const
{
	auto tr = trsf->GetRotation();
	return {tr.X(), tr.Y(), tr.Z(), tr.W()};
}

servoce::vector3 servoce::transformation::translation() const
{
	auto tr = trsf->TranslationPart();
	return gp_Vec(tr);
}

servoce::quaternion servoce::transformation::rotation() const
{
	auto tr = trsf->GetRotation();
	return tr;
}

servoce::transformation servoce::short_rotate(const vector3& from, const vector3& to)
{
	auto f = from.normalize();
	auto t = to.normalize();

	auto rot = f.cross(t);
	auto mul = linalg::uangle(f, t);

	return axrotation(rot.x, rot.y, rot.z, mul);
}