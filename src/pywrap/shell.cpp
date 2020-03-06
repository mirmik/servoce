/**
	Python bind for servoce::edge_shape
*/

#include <pybind11/pybind11.h>
#include <local/pywrap_util.h>

#include <servoce/util.h>
#include <servoce/util/b64.h>

#include <servoce/shell.h>
#include <servoce/solid.h>
#include <servoce/face.h>

namespace py = pybind11;
using namespace servoce;

void registry_shell_shape(py::module & m)
{
	py::class_<shell_shape, shape>(m, "Shell")
	.def(py::pickle(
	[](const shell_shape & self) { return b64::base64_encode(string_dump(self)); },
	[](const std::string & in) { return restore_string_dump<shell_shape>(b64::base64_decode(in)); }), ungil())
	.def("fill", &shell_shape::fill, ungil())
	;

	m.def("make_shell", (shell_shape(*)(const std::vector<const servoce::shape*>& vec))&make_shell, ungil());
	m.def("polyhedron_shell", &polyhedron_shell, ungil());
	
	m.def("ruled_shell", &ruled_shell, ungil());
}