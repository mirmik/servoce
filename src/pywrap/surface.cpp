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
	py::class_<surface::surface>(m, "surface")
	.def("map", &surface::surface::map, ungil())
	.def("urange", &surface::surface::urange)
	.def("vrange", &surface::surface::vrange)
	.def(py::pickle(
	[](const surface::surface & self) { return b64::base64_encode(string_dump(self)); },
	[](const std::string & in) { return restore_string_dump<surface::surface>(b64::base64_decode(in)); }), ungil())
	;

	m.def("surface_tube", surface::tube, ungil());
	m.def("surface_cylinder", surface::cylinder, ungil());
}