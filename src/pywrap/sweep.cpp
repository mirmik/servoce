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
}