/**
	Python bind for servoce::face_shape
*/

#include <pybind11/pybind11.h>
#include <local/pywrap_util.h>

#include <servoce/util.h>
#include <servoce/util/b64.h>

#include <servoce/sweep.h>
#include <servoce/topo.h>
#include <servoce/triangulation.h>

namespace py = pybind11;
using namespace servoce;

void registry_other(py::module & m)
{
	m.def("triangulation", &servoce::triangulation);
}