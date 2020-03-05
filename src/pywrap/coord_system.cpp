/**
	Python bind for servoce::edge_shape
*/

#include <pybind11/pybind11.h>
#include <local/pywrap_util.h>

#include <servoce/util.h>
#include <servoce/util/b64.h>

#include <servoce/coord_system.h>

namespace py = pybind11;
using namespace servoce;

void registry_coord_system(py::module & m)
{
	py::class_<coord_system>(m, "CoordSystem")
	//.def(py::pickle(
	//[](const shell_shape & self) { return b64::base64_encode(string_dump(self)); },
	//[](const std::string & in) { return restore_string_dump<shell_shape>(b64::base64_decode(in)); }), ungil())
	//.def("fill", &shell_shape::fill, ungil())
	//;

	//m.def("make_shell", (shell_shape(*)(const std::vector<const servoce::shape*>& vec))&make_shell, ungil());
	//m.def("polyhedron_shell", &polyhedron_shell, ungil());

	.def("location_update", &coord_system::location_update)
	.def("relocate", &coord_system::relocate)
	.def("on_location_update_handle", &coord_system::on_location_update_handle)
	
	.def_readwrite("location", &coord_system::location)
	.def_readwrite("global_location", &coord_system::global_location)
	;
}