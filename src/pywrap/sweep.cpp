/**
	Python bind for servoce::face_shape
*/

#include <pybind11/pybind11.h>
#include <local/pywrap_util.h>

#include <servoce/util.h>
#include <servoce/util/b64.h>

#include <servoce/sweep.h>
#include <servoce/topo.h>

namespace py = pybind11;
using namespace servoce;

void registry_sweep_shape(py::module & m)
{
	m.def("tube", (std::tuple<face_shape, edge_shape, edge_shape> (*)(
		const edge_shape& spine, 
		double r, 
		double tol,
		int cont, 
		int maxdegree, 
		int maxsegm))
	&make_tube, 
		py::arg("spine"), 
		py::arg("r"), 
		py::arg("tol"), 
		py::arg("cont"), 
		py::arg("maxdegree"), 
		py::arg("maxsegm"), 
		ungil());
	
	m.def("tube", (std::tuple<shell_shape, edge_shape, edge_shape> (*)(
		const wire_shape& spine, 
		double r, 
		double tol,
		int cont, 
		int maxdegree, 
		int maxsegm))
	&make_tube, 
		py::arg("spine"), 
		py::arg("r"), 
		py::arg("tol"), 
		py::arg("cont"), 
		py::arg("maxdegree"), 
		py::arg("maxsegm"), 
		ungil());


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
}