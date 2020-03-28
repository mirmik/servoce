/**
	Python bind for servoce::wire_shape
*/

#include <pybind11/pybind11.h>
#include <local/pywrap_util.h>

#include <servoce/util.h>
#include <servoce/util/b64.h>

#include <servoce/edge.h>
#include <servoce/wire.h>
#include <servoce/face.h>

#include <pywrap/transformable.h>
#include <servoce/transformable_shape_impl.h>

namespace py = pybind11;
using namespace servoce;

void registry_wire_shape(py::module & m)
{
	auto cls = py::class_<wire_shape, shape>(m, "Wire")
	.def(py::pickle(
	[](const wire_shape & self) { return b64::base64_encode(string_dump(self)); },
	[](const std::string & in) { return restore_string_dump<wire_shape>(b64::base64_decode(in)); }), ungil())
	.def("fill", &wire_shape::fill, ungil())
	;
	pywrap_transformable<servoce::wire_shape>(cls);


	m.def("segment",
	      make_segment, ungil()
	     );

	m.def("polysegment", (wire_shape(*)(const std::vector<point3>&, const bool))
	      &make_polysegment, ungil(),
	      py::arg("pnts"),
	      py::arg("closed") = false
	     );


	m.def("helix",
	      make_helix, ungil(),
	      py::arg("step"),
	      py::arg("height"),
	      py::arg("radius"),
	      py::arg("angle") = 0,
	      py::arg("leftHanded") = false,
	      py::arg("newStyle") = true
	     );

	m.def("long_helix",
	      make_long_helix, ungil(),
	      py::arg("step"),
	      py::arg("height"),
	      py::arg("radius"),
	      py::arg("angle") = 0,
	      py::arg("leftHanded") = false
	     );

	m.def("circle_arc",
	      &circle_arc, ungil()
	     );

	m.def("sew",
	      &sew, ungil()
	     );

	m.def("extract_curve", &extract_curve, ungil());
	m.def("make_wire", (wire_shape(*)(const std::vector<const servoce::shape*>& vec))&make_wire, ungil());
	
}