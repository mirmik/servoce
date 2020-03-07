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
	m.def("offset_shape", &offset_shape, ungil());

	m.def("make_solid", py::overload_cast<const servoce::shell_shape&>(&make_solid), ungil());
	m.def("make_solid", py::overload_cast<const std::vector<const servoce::shell_shape*>&>(&make_solid), ungil());

	m.def("pipe_0", 		make_pipe_0, ungil(), py::arg("profile"), py::arg("spine"));
	m.def("pipe", 			make_pipe, ungil(), py::arg("profile"), py::arg("spine"), py::arg("mode"), py::arg("force_approx_c1") = false);

	m.def("linear_extrude", (shape(*)(const shape&, const vector3&, bool)) &make_linear_extrude, ungil(), py::arg("shp"), py::arg("vec"), py::arg("center") = false);
	m.def("linear_extrude", (shape(*)(const shape&, double, bool)) &make_linear_extrude, ungil(), py::arg("shp"), py::arg("z"), py::arg("center") = false);
	m.def("linear_extrude", [](const shape & shp, const py::list & lst, bool center) { return servoce::make_linear_extrude(shp, vector3(lst[0].cast<double>(), lst[1].cast<double>(), lst[2].cast<double>()), center); }, ungil(), py::arg("shp"), py::arg("vec"), py::arg("center") = false);
	//m.def("pipe_shell", 	(shape(*)(const shape& profile, const shape& path, const shape& auxiliary_spine, bool curvilinear_equivalence))&make_pipe_shell, ungil(), py::arg("prof"), py::arg("path"), py::arg("auxspine"), py::arg("curvilinear_equivalence"));
	//m.def("pipe_shell", 	(shape(*)(const shape& profile, const shape& path, bool isFrenet))&make_pipe_shell, ungil(), py::arg("profile"), py::arg("spine"), py::arg("frenet") = false);
	m.def("pipe_shell",
	      (shape(*)(
	           const std::vector<const shape*>& wires,
	           const shape & spine,
	           bool isFrenet,
	           bool approx_c1,
	           const vector3 & binormal,
	           const vector3 & parallel,
	           bool discrete,
	           bool solid,
	           int transition))
	      &make_pipe_shell,
	      ungil(),
	      py::arg("profiles"),
	      py::arg("spine"),
	      py::arg("frenet") = false,
	      py::arg("force_approx_c1") = false,
	      py::arg("binormal") = vector3(0, 0, 0),
	      py::arg("parallel") = vector3(0, 0, 0),
	      py::arg("discrete") = false,
	      py::arg("solid") = true,
	      py::arg("transition") = 0);


	m.def("pipe_shell",
	      (shape(*)(
	           const std::vector<const shape*>& profiles,
	           const shape & spine,
	           bool frenet,
	           bool solid,
	           int transition))
	      &make_pipe_shell,
	      ungil(),
	      py::arg("profiles"),
	      py::arg("spine"),
	      py::arg("frenet") = false,
	      py::arg("solid") = true,
	      py::arg("transition") = 0);


	m.def("loft", 			loft, ungil(), py::arg("arr"), py::arg("smooth") = false);
	m.def("revol", 			revol, ungil());
}