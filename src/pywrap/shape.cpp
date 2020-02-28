/**
	Python bind for servoce::shape
*/

#include <pybind11/pybind11.h>
#include <local/pywrap_util.h>

#include <servoce/util.h>
#include <servoce/util/b64.h>
#include <servoce/shape.h>
#include <servoce/solid.h>
#include <servoce/face.h>
#include <servoce/edge.h>
#include <servoce/trans.h>

namespace py = pybind11;
using namespace servoce;

void registry_shape(py::module & m)
{
	py::class_<shape>(m, "Shape")
	
	.def("transform", (shape(shape::*)(const transformation& trans)) &shape::transform, ungil())
	.def("transform", (shape(shape::*)(const general_transformation& trans)) &shape::transform, ungil())
	
	.def("translate", (shape(shape::*)(double,double,double))&shape::translate, py::arg("x")=0, py::arg("y")=0, py::arg("z")=0, ungil())
	.def("translate", (shape(shape::*)(vector3))&shape::translate, py::arg("v"), ungil())
	
	.def("move", (shape(shape::*)(double,double,double))&shape::move, py::arg("x")=0, py::arg("y")=0, py::arg("z")=0, ungil())
	.def("move", (shape(shape::*)(vector3))&shape::move, py::arg("v"), ungil())
	.def("moveX", &shape::moveX, ungil())
	.def("moveY", &shape::moveY, ungil())
	.def("moveZ", &shape::moveZ, ungil())

	.def("mov", (shape(shape::*)(double,double,double))&shape::move, py::arg("x")=0, py::arg("y")=0, py::arg("z")=0, ungil())
	.def("mov", (shape(shape::*)(vector3))&shape::move, py::arg("v"), ungil())
	.def("movX", &shape::moveX, ungil())
	.def("movY", &shape::moveY, ungil())
	.def("movZ", &shape::moveZ, ungil())
	
	.def("up", &shape::up, ungil())
	.def("down", &shape::down, ungil())	
	.def("right", &shape::right, ungil())
	.def("left", &shape::left, ungil())
	.def("forw", &shape::forw, ungil())
	.def("back", &shape::back, ungil())
	
	.def("rotate", (shape(shape::*)(double,double,double))&shape::rotate, py::arg("x")=0, py::arg("y")=0, py::arg("z")=0, ungil())	
	.def("rotate", (shape(shape::*)(double,vector3))&shape::rotate, py::arg("a"), py::arg("v"), ungil())	
	.def("rotateX", &shape::rotateX, ungil())
	.def("rotateY", &shape::rotateY, ungil())
	.def("rotateZ", &shape::rotateZ, ungil())
	
	.def("rot", (shape(shape::*)(double,double,double))&shape::rotate, py::arg("x")=0, py::arg("y")=0, py::arg("z")=0, ungil())	
	.def("rot", (shape(shape::*)(double,vector3))&shape::rotate, py::arg("a"), py::arg("v"), ungil())	
	.def("rotX", &shape::rotateX, ungil())
	.def("rotY", &shape::rotateY, ungil())
	.def("rotZ", &shape::rotateZ, ungil())
	
	.def("mirrorX", &shape::mirrorX, ungil())
	.def("mirrorY", &shape::mirrorY, ungil())
	.def("mirrorZ", &shape::mirrorZ, ungil())
	.def("mirrorXY", &shape::mirrorXY, ungil())
	.def("mirrorYZ", &shape::mirrorYZ, ungil())
	.def("mirrorXZ", &shape::mirrorXZ, ungil())
	
	.def("scale", 	 &shape::scale,    ungil(), py::arg("factor"), py::arg("center") = point3())
	.def("scaleX",   &shape::scaleX,   ungil(), py::arg("factor"))
	.def("scaleY",   &shape::scaleY,   ungil(), py::arg("factor"))
	.def("scaleZ",   &shape::scaleZ,   ungil(), py::arg("factor"))
	.def("scaleXY",  &shape::scaleXY,  ungil(), py::arg("x"), py::arg("y"))
	.def("scaleYZ",  &shape::scaleYZ,  ungil(), py::arg("y"), py::arg("z"))
	.def("scaleXZ",  &shape::scaleXZ,  ungil(), py::arg("x"), py::arg("z"))
	.def("scaleXYZ", &shape::scaleXYZ, ungil(), py::arg("x"), py::arg("y"), py::arg("z")) 

	.def("__add__", (shape(shape::*)(const shape&))&shape::operator+, ungil())
	.def("__sub__", &shape::operator-, ungil())
	.def("__xor__", &shape::operator^, ungil())
	.def(py::pickle(
	[](const shape & self) { return b64::base64_encode(string_dump(self)); },
	[](const std::string & in) { return restore_string_dump<shape>(b64::base64_decode(in)); }), ungil())
	.def("fill", &shape::fill)
	.def("center", &shape::center, ungil())
	.def("extrude", (shape(shape::*)(const vector3&, bool)) &shape::extrude, ungil(), py::arg("vec"), py::arg("center") = false)
	.def("extrude", (shape(shape::*)(double, double, double, bool)) &shape::extrude, ungil(), py::arg("x"), py::arg("y"), py::arg("z"), py::arg("center") = false)
	.def("extrude", (shape(shape::*)(double, bool)) &shape::extrude, ungil(), py::arg("z"), py::arg("center") = false)
	.def("is_closed", &shape::is_closed, ungil())
	.def("sfvertex", &shape::sfvertex, ungil())
	.def("endpoints", &shape::sfvertex, ungil())

	.def("vertices", &shape::vertices, ungil())
	.def("solids", &shape::solids, ungil())
	.def("faces", &shape::faces, ungil())
	.def("edges", &shape::edges, ungil())
	.def("wires", &shape::wires, ungil())
	.def("shells", &shape::shells, ungil())
	.def("compounds", &shape::compounds, ungil())
	.def("compsolids", &shape::compsolids, ungil())

	.def("shapetype", &shape::shapetype_as_string, ungil())
	.def("print_topo_dump", &shape::print_topo_dump, ungil())

	.def("fillet", (shape(shape::*)(double, const std::vector<point3>&))&shape::fillet, ungil(), py::arg("r"), py::arg("refs"))
	.def("fillet", (shape(shape::*)(double))&shape::fillet, ungil(), py::arg("r"))
	.def("chamfer", (shape(shape::*)(double, const std::vector<point3>&))&shape::chamfer, ungil(), py::arg("r"), py::arg("refs"))
	.def("chamfer", (shape(shape::*)(double))&shape::chamfer, ungil(), py::arg("r"))

	.def("fillet2d", (shape(shape::*)(double, const std::vector<point3>&))&shape::fillet2d, ungil(), py::arg("r"), py::arg("refs"))
	.def("fillet2d", (shape(shape::*)(double))&shape::fillet2d, ungil(), py::arg("r"))
	.def("chamfer2d", (shape(shape::*)(double, const std::vector<point3>&))&shape::chamfer2d, ungil(), py::arg("r"), py::arg("refs"))
	.def("chamfer2d", (shape(shape::*)(double))&shape::chamfer2d, ungil(), py::arg("r"))

	.def("fillet", [](const shape & shp, double r, const py::list & arr) { return fillet(shp, r, points(arr)); }, ungil(), py::arg("r"), py::arg("refs"))
	.def("chamfer", [](const shape & shp, double r, const py::list & arr) { return fillet(shp, r, points(arr)); }, ungil(), py::arg("r"), py::arg("refs"))
	.def("chamfer2d", [](const shape & shp, double r, const py::list & arr) { return fillet(shp, r, points(arr)); }, ungil(), py::arg("r"), py::arg("refs"))
	.def("fillet2d", [](const shape & shp, double r, const py::list & arr) { return fillet(shp, r, points(arr)); }, ungil(), py::arg("r"), py::arg("refs"))

	.def("cmradius", &shape::cmradius, ungil())
	.def("mass", &shape::mass, ungil())
	.def("matrix_of_inertia", &shape::matrix_of_inertia, ungil())
	.def("static_moments", &shape::static_moments, ungil())

	.def("bbox", &servoce::shape::bounding_box, ungil())
	//.def("moment_of_inertia", &shape::moment_of_inertia, ungil()) //TODO
	//.def("radius_of_gyration", &shape::radius_of_gyration, ungil()) //TODO
	;
}