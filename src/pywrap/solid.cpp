/**
	Python bind for servoce::solid_shape
*/

#include <pybind11/pybind11.h>
#include <local/pywrap_util.h>

#include <servoce/util.h>
#include <servoce/util/b64.h>

#include <servoce/solid.h>
#include <servoce/shell.h>

namespace py = pybind11;
using namespace servoce;

void registry_solid_shape(py::module & m)
{
	py::class_<solid_shape, shape>(m, "Solid")
	.def(py::pickle(
	[](const solid_shape & self) { return b64::base64_encode(string_dump(self)); },
	[](const std::string & in) { return restore_string_dump<solid_shape>(b64::base64_decode(in)); }), ungil())
	;

	m.def("box", 		box, ungil(), py::arg("x"), py::arg("y"), py::arg("z"), py::arg("center") = false);

	m.def("sphere", 	(solid_shape(*)(double))&sphere, ungil(), py::arg("r"));
	m.def("sphere", 	(solid_shape(*)(double, double))&sphere, ungil(), py::arg("r"), py::arg("yaw"));
	m.def("sphere", 	(solid_shape(*)(double, double, double))&sphere, ungil(), py::arg("r"), py::arg("pitch0"), py::arg("pitch1"));
	m.def("sphere", 	(solid_shape(*)(double, double, double, double))&sphere, ungil(), py::arg("r"), py::arg("pitch0"), py::arg("pitch1"), py::arg("yaw"));

	m.def("cylinder", 	(solid_shape(*)(double, double, bool)) &cylinder, ungil(), py::arg("r"), py::arg("h"), py::arg("center") = false);
	m.def("cylinder", 	(solid_shape(*)(double, double, double, bool)) &cylinder, ungil(), py::arg("r"), py::arg("h"), py::arg("yaw"), py::arg("center") = false);

	m.def("cone", 		(solid_shape(*)(double, double, double, bool)) &cone, ungil(), py::arg("r1"), py::arg("r2"), py::arg("h"), py::arg("center") = false);
	m.def("cone", 		(solid_shape(*)(double, double, double, double, bool)) &cone, ungil(), py::arg("r1"), py::arg("r2"), py::arg("h"), py::arg("yaw"), py::arg("center") = false);

	m.def("torus", 		(solid_shape(*)(double, double)) &torus, ungil(), py::arg("r1"), py::arg("r2"));
	m.def("torus", 		(solid_shape(*)(double, double, double)) &torus, ungil(), py::arg("r1"), py::arg("r2"), py::arg("yaw"));
	m.def("torus", 		(solid_shape(*)(double, double, double, double)) &torus, ungil(), py::arg("r1"), py::arg("r2"), py::arg("pitch0"), py::arg("pitch1"));
	m.def("torus", 		(solid_shape(*)(double, double, double, double, double)) &torus, ungil(), py::arg("r1"), py::arg("r2"), py::arg("pitch0"), py::arg("pitch1"), py::arg("yaw"));
	m.def("halfspace", 	&halfspace, ungil());

	m.def("thicksolid", &thicksolid, ungil());

	m.def("make_solid", &make_solid, ungil());
}