/**
	Python bind for servoce::face_shape
*/

#include <pybind11/pybind11.h>
#include <local/pywrap_util.h>

#include <servoce/util.h>
#include <servoce/util/b64.h>

#include <servoce/face.h>
#include <servoce/shell.h>
#include <servoce/solid.h>
#include <servoce/wire.h>
#include <servoce/edge.h>

#include <pywrap/transformable.h>

namespace py = pybind11;
using namespace servoce;

void registry_face_shape(py::module & m)
{
	auto cls = py::class_<face_shape, shape>(m, "Face")
	.def(py::pickle(
	[](const face_shape & self) { return b64::base64_encode(string_dump(self)); },
	[](const std::string & in) { return restore_string_dump<face_shape>(b64::base64_decode(in)); }), ungil())
	.def("normal", &face_shape::normal, py::arg("u")=0, py::arg("v")=0, ungil())
	.def("surface", &face_shape::surface)
	//.def("vrange", &face_shape::vrange)
	//.def("urange", &face_shape::urange)
	;
	pywrap_transformable<servoce::face_shape>(cls);

	m.def("ngon_wire", 		ngon_wire, ungil(), py::arg("r"), py::arg("n"));
	m.def("square_wire", 	square_wire, ungil(), py::arg("a"), py::arg("center") = false);
	m.def("rectangle_wire", 	rectangle_wire, ungil(), py::arg("a"), py::arg("b"), py::arg("center") = false);

	m.def("ngon", 		ngon, ungil(), py::arg("r"), py::arg("n"));
	m.def("square", 	square, ungil(), py::arg("a"), py::arg("center") = false);
	m.def("rectangle", 	rectangle, ungil(), py::arg("a"), py::arg("b"), py::arg("center") = false);

	m.def("circle_edge", 	(edge_shape(*)(double)) &circle_edge, ungil(), py::arg("r"));
	m.def("circle_edge", 	(edge_shape(*)(double, double)) &circle_edge, ungil(), py::arg("r"), py::arg("angle"));
	m.def("circle_edge", 	(edge_shape(*)(double, double, double)) &circle_edge, ungil(), py::arg("r"), py::arg("a1"), py::arg("a2"));
	m.def("ellipse_edge", 	(edge_shape(*)(double, double)) &ellipse_edge, ungil(), py::arg("r1"), py::arg("r2"));
	m.def("ellipse_edge", 	(edge_shape(*)(double, double, double, double)) &ellipse_edge, ungil(), py::arg("r1"), py::arg("r2"), py::arg("a1"), py::arg("a2"));
	
	m.def("circle", 	(face_shape(*)(double)) &circle, ungil(), py::arg("r"));
	m.def("circle", 	(face_shape(*)(double, double)) &circle, ungil(), py::arg("r"), py::arg("angle"));
	m.def("circle", 	(face_shape(*)(double, double, double)) &circle, ungil(), py::arg("r"), py::arg("a1"), py::arg("a2"));
	m.def("ellipse", 	(face_shape(*)(double, double)) &ellipse, ungil(), py::arg("r1"), py::arg("r2"));
	m.def("ellipse", 	(face_shape(*)(double, double, double, double)) &ellipse, ungil(), py::arg("r1"), py::arg("r2"), py::arg("a1"), py::arg("a2"));
	
	m.def("polygon", 	(face_shape(*)(const std::vector<point3>&))&polygon, ungil(), py::arg("pnts"));
	m.def("textshape", 	textshape, ungil(), py::arg("text"), py::arg("fontpath"), py::arg("size"));

	m.def("infplane", 	infplane, ungil());

	m.def("ruled_face", &ruled_face, ungil());
	m.def("trivial_tube", (face_shape (*)(const shape& spine, double r))&trivial_tube, ungil());
	//m.def("tube", (shape(*)(const servoce::edge_shape&,double,double,int,int,int))&make_tube, py::arg("shp"), py::arg("r"), py::arg("tol"), py::arg("cont"), py::arg("maxdegree"), py::arg("maxsegm"), ungil());



	m.def("make_face", (face_shape(*)(const std::vector<const servoce::shape*>& vec))&make_face, ungil());
}