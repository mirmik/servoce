/**
	Python bind for servoce::face_shape
*/

#include <pybind11/pybind11.h>
#include <local/pywrap_util.h>

#include <servoce/util.h>
#include <servoce/util/b64.h>

#include <servoce/face.h>
#include <servoce/solid.h>
#include <servoce/edge.h>

namespace py = pybind11;
using namespace servoce;

void registry_face_shape(py::module & m)
{
	py::class_<face_shape, shape>(m, "Face")
	.def(py::pickle(
	[](const face_shape & self) { return b64::base64_encode(string_dump(self)); },
	[](const std::string & in) { return restore_string_dump<face_shape>(b64::base64_decode(in)); }), ungil())
	.def("normal", &face_shape::normal, py::arg("u")=0, py::arg("v")=0, ungil())
	.def("surface", &face_shape::surface)
	//.def("vrange", &face_shape::vrange)
	//.def("urange", &face_shape::urange)
	;

	m.def("square", 	square, ungil(), py::arg("a"), py::arg("center") = false, py::arg("wire")=false);
	m.def("rectangle", 	rectangle, ungil(), py::arg("a"), py::arg("b"), py::arg("center") = false, py::arg("wire")=false);
	
	m.def("circle", 	(shape(*)(double, bool)) &circle, ungil(), py::arg("r"), py::arg("wire")=false);
	m.def("circle", 	(shape(*)(double, double, bool)) &circle, ungil(), py::arg("r"), py::arg("angle"), py::arg("wire")=false);
	m.def("circle", 	(shape(*)(double, double, double, bool)) &circle, ungil(), py::arg("r"), py::arg("a1"), py::arg("a2"), py::arg("wire")=false);
	
	m.def("ellipse", 	(shape(*)(double, double, bool)) &ellipse, ungil(), py::arg("r1"), py::arg("r2"), py::arg("wire")=false);
	m.def("ellipse", 	(shape(*)(double, double, double, double, bool)) &ellipse, ungil(), py::arg("r1"), py::arg("r2"), py::arg("a1"), py::arg("a2"), py::arg("wire")=false);
	
	m.def("ngon", 		ngon, ungil(), py::arg("r"), py::arg("n"), py::arg("wire")=false);
	m.def("polygon", 	(face_shape(*)(const std::vector<point3>&))&polygon, ungil(), py::arg("pnts"));
	m.def("textshape", 	textshape, ungil(), py::arg("text"), py::arg("fontpath"), py::arg("size"));

	m.def("infplane", 	infplane, ungil());

	m.def("ruled_face", &ruled_face, ungil());
	m.def("trivial_tube", (face_shape (*)(const shape& spine, double r))&trivial_tube, ungil());
	m.def("tube", (shape(*)(const servoce::edge_shape&,double,double,int,int,int))&make_tube, py::arg("shp"), py::arg("r"), py::arg("tol"), py::arg("cont"), py::arg("maxdegree"), py::arg("maxsegm"), ungil());
}