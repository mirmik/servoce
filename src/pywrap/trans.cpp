/**
	Python bind for servoce::transform
	Python bind for servoce::general_transform
*/

#include <pybind11/pybind11.h>
#include <local/pywrap_util.h>

#include <servoce/util.h>
#include <servoce/util/b64.h>
#include <servoce/trans.h>
#include <servoce/shape.h>

namespace py = pybind11;
using namespace servoce;

void registry_trans(py::module & m)
{
	py::class_<transformation>(m, "transformation")
	.def(py::init<const point3&, const vector3&, const vector3&>(), py::arg("pnt"), py::arg("dir0"), py::arg("dir1"))
	.def("__call__", (shape(transformation::*)(const shape&)const)&transformation::operator(), ungil())
	.def("__call__", (point3(transformation::*)(const point3&)const)&transformation::operator(), ungil())
	.def("__call__", (vector3(transformation::*)(const vector3&)const)&transformation::operator(), ungil())
	.def("__call__", (transformation(transformation::*)(const transformation&)const)&transformation::operator(), ungil())
	.def("__mul__", &transformation::operator*, ungil())
	.def("invert", &transformation::invert)
	.def("inverse", &transformation::invert)
	.def(py::pickle(
	[](const transformation & self) { return b64::base64_encode(self.string_dump()); },
	[](const std::string & in) { return transformation::restore_string_dump(b64::base64_decode(in)); }), ungil())
	.def("translation_part", &transformation::translation_part)
	.def("rotation_part", &transformation::rotation_part)
	.def("translation", &transformation::translation)
	.def("rotation", &transformation::rotation)
	.def("__repr__", [](const transformation & trsf)
	{
		char buf[128];
		auto rot = trsf.rotation();
		auto mov = trsf.translation();
		sprintf(buf, "trans((%f,%f,%f,%f),(%f,%f,%f))", rot.x, rot.y, rot.z, rot.w, mov.x, mov.y, mov.z);
		return std::string(buf);
	})
	;


	py::class_<general_transformation>(m, "general_transformation")
	.def("__call__", (shape(general_transformation::*)(const shape&)const)&general_transformation::operator(), ungil())
	.def("__call__", (general_transformation(general_transformation::*)(const general_transformation&)const)&general_transformation::operator(), ungil())
	.def(py::pickle(
	[](const general_transformation & self) { return b64::base64_encode(self.string_dump()); },
	[](const std::string & in) { return general_transformation::restore_string_dump(b64::base64_decode(in)); }), ungil())
	;


	m.def("translate", (transformation(*)(double, double, double)) &translate, py::arg("x") = 0, py::arg("y") = 0, py::arg("z") = 0, ungil());
	m.def("translate", (transformation(*)(const vector3&)) &translate, py::arg("v"), ungil());
	
	m.def("move", (transformation(*)(double, double, double)) &move, py::arg("x") = 0, py::arg("y") = 0, py::arg("z") = 0, ungil());
	m.def("move", (transformation(*)(const vector3&)) &move, py::arg("v"), ungil());
	m.def("move", (transformation(*)(const point3&)) &move, py::arg("p"), ungil());
	m.def("moveX", &moveX, ungil());
	m.def("moveY", &moveY, ungil());
	m.def("moveZ", &moveZ, ungil());
	
	m.def("up", up, ungil());
	m.def("down", down, ungil());
	m.def("left", left, ungil());
	m.def("right", right, ungil());
	m.def("forw", forw, ungil());
	m.def("back", back, ungil());

	m.def("axrotation", axrotation, ungil());
	m.def("rotate", (transformation(*)(double,double,double))&rotate, py::arg("x") = 0, py::arg("y") = 0, py::arg("z") = 0, ungil());
	m.def("rotate", (transformation(*)(double,const vector3&))&rotate, py::arg("a"), py::arg("v"), ungil());
	m.def("rotate", (transformation(*)(const quaternion&))&rotate, py::arg("q"), ungil());
	m.def("rotateX", rotateX, ungil());
	m.def("rotateY", rotateY, ungil());
	m.def("rotateZ", rotateZ, ungil());
	m.def("short_rotate", &short_rotate, py::arg("f"), py::arg("t"), ungil());

	m.def("mirrorO", (transformation(*)(double,double,double))&mirrorO, ungil());
	m.def("mirrorO", (transformation(*)(const point3&))&mirrorO, ungil());
	m.def("mirrorO", (transformation(*)())&mirrorO, ungil());

	m.def("mirror_axis", (transformation(*)(double,double,double))&mirror_axis, ungil());
	m.def("mirror_axis", (transformation(*)(vector3))&mirror_axis, ungil());
	m.def("mirrorX", mirrorX, ungil());
	m.def("mirrorY", mirrorY, ungil());
	m.def("mirrorZ", mirrorZ, ungil());

	m.def("mirror_plane", (transformation(*)(double,double,double))&mirror_plane, ungil());
	m.def("mirror_plane", (transformation(*)(vector3))&mirror_plane, ungil());
	m.def("mirrorXY", mirrorXY, ungil());
	m.def("mirrorXZ", mirrorXZ, ungil());
	m.def("mirrorYZ", mirrorYZ, ungil());

	m.def("scale", (transformation(*)(double,point3))&scale, ungil(), py::arg("factor"), py::arg("center"));
	m.def("scale", (transformation(*)(double))&scale, ungil(), py::arg("factor"));
	m.def("scaleX", scaleX, ungil(), py::arg("factor"));
	m.def("scaleY", scaleY, ungil(), py::arg("factor"));
	m.def("scaleZ", scaleZ, ungil(), py::arg("factor"));
	m.def("scaleXY", scaleXY, ungil(), py::arg("x"), py::arg("y"));
	m.def("scaleYZ", scaleYZ, ungil(), py::arg("y"), py::arg("z"));
	m.def("scaleXZ", scaleXZ, ungil(), py::arg("x"), py::arg("z"));
	m.def("scaleXYZ", &scaleXYZ, ungil(), py::arg("x"), py::arg("y"), py::arg("z"));
	m.def("nulltrans", nulltrans, ungil());
}