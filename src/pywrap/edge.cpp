/**
	Python bind for servoce::edge_shape
*/

#include <pybind11/pybind11.h>
#include <local/pywrap_util.h>

#include <servoce/util.h>
#include <servoce/util/b64.h>

#include <servoce/edge.h>
#include <servoce/face.h>

namespace py = pybind11;
using namespace servoce;

void registry_edge_shape(py::module & m)
{
	py::class_<edge_shape, shape>(m, "Edge")
	.def(py::pickle(
	[](const edge_shape & self) { return b64::base64_encode(string_dump(self)); },
	[](const std::string & in) { return restore_string_dump<edge_shape>(b64::base64_decode(in)); }), ungil())
	.def("range", &edge_shape::range, ungil())
	.def("length", &edge_shape::length, ungil())
	.def("d0", &edge_shape::d0, ungil())
	.def("d1", &edge_shape::d1, ungil())
	.def("linoff", (double(edge_shape::*)(double, double)const)&edge_shape::linoff, ungil())
	//.def("linoff", (double(edge_shape::*)(double)const)&edge_shape::linoff, ungil())
	.def("linoff_point", (point3(edge_shape::*)(double, double)const)&edge_shape::linoff_point, ungil())
	//.def("linoff_point", (point3(edge_shape::*)(double)const)&edge_shape::linoff_point, ungil())
	.def("uniform_points", (std::vector<servoce::point3>(edge_shape::crvalgo::*)(int, double, double)const)&edge_shape::uniform_points, ungil(), py::arg("npnts"), py::arg("strt"), py::arg("fini"))
	.def("uniform_points", (std::vector<servoce::point3>(edge_shape::crvalgo::*)(int)const)&edge_shape::uniform_points, ungil(), py::arg("npnts"))
	.def("uniform", (std::vector<double>(edge_shape::crvalgo::*)(int, double, double)const)&edge_shape::uniform, ungil(), py::arg("npnts"), py::arg("strt"), py::arg("fini"))
	.def("uniform", (std::vector<double>(edge_shape::crvalgo::*)(int)const)&edge_shape::uniform, ungil(), py::arg("npnts"))
	.def("fill", &edge_shape::fill, ungil())
	;
	
	m.def("interpolate", (edge_shape(*)(const std::vector<point3>&, const std::vector<vector3>&, bool))
	      &make_interpolate, ungil(),
	      py::arg("pnts"),
	      py::arg("tang"),
	      py::arg("closed") = false
	     );

	m.def("interpolate", (edge_shape(*)(const std::vector<point3>&, const bool))
	      &make_interpolate, ungil(),
	      py::arg("pnts"),
	      py::arg("closed") = false
	     );

	m.def("bezier", (edge_shape(*)(const std::vector<point3>&, const std::vector<double>&))
	      &bezier, ungil(),
	      py::arg("pnts"),
	      py::arg("weights")
	     );

	m.def("bezier", (edge_shape(*)(const std::vector<point3>&))
	      &bezier, ungil(),
	      py::arg("pnts")
	     );

	m.def("bspline", (edge_shape(*)(
	                      const std::vector<point3>& poles, const std::vector<double>& knots, const std::vector<int>& multiplicities,
	                      int degree, bool periodic))
	      &bspline, ungil(),
	      py::arg("pnts"),
	      py::arg("knots"),
	      py::arg("multiplicities"),
	      py::arg("degree"),
	      py::arg("periodic") = false
	     );

	m.def("bspline", (edge_shape(*)(
	                      const std::vector<point3>& poles, const std::vector<double>& weights, const std::vector<double>& knots, const std::vector<int>& multiplicities,
	                      int degree, bool periodic, bool check_rational))
	      &bspline, ungil(),
	      py::arg("pnts"),
	      py::arg("knots"),
	      py::arg("weights"),
	      py::arg("multiplicities"),
	      py::arg("degree"),
	      py::arg("periodic") = false,
	      py::arg("check_rational") = true
	     );
}