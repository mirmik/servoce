#include <pybind11/pybind11.h>
#include <local/pywrap_util.h>

#include <servoce/util.h>
#include <servoce/util/b64.h>

#include <servoce/axis.h>

#include <pywrap/displayable.h>
#include <pywrap/transformable.h>

namespace py = pybind11;
using namespace servoce;

void pywrap_transformable(auto cls) {}

void registry_displayable(py::module & m)
{
	//py::class_<servoce::displayable>(m, "Displayable");

	auto axis = py::class_<servoce::axis>(m, "Axis");

	pywrap_displayable<servoce::axis>(axis);
	pywrap_transformable<servoce::axis>(axis);
}