#include <pybind11/pybind11.h>
#include <local/pywrap_util.h>

#include <servoce/util.h>
#include <servoce/util/b64.h>

#include <servoce/surface.h>
#include <servoce/face.h>

namespace py = pybind11;
using namespace servoce;

void registry_surface_shape(py::module & m)
{
	py::class_<surface>(m, "surface")
	.def("map", &surface::map, ungil())
	.def("urange", &surface::urange)
	.def("vrange", &surface::vrange)
	.def(py::pickle(
	[](const surface & self) { return b64::base64_encode(string_dump(self)); },
	[](const std::string & in) { return restore_string_dump<surface>(b64::base64_decode(in)); }), ungil())
	;

	m.def("tube_surface", tube_surface, ungil());
	m.def("cylinder_surface", cylinder_surface, ungil());
}