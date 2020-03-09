
#include <pybind11/pybind11.h>
#include <local/pywrap_util.h>

#include <servoce/util.h>
#include <servoce/util/b64.h>

#include <servoce/interactive_object.h>

#include <pywrap/transformable.h>
#include <pywrap/displayable.h>

namespace py = pybind11;
using namespace servoce;

void registry_interactive_object(py::module & m)
{
	auto cls = py::class_<interactive_object, std::shared_ptr<interactive_object>>(m, "interactive_object")
	.def(py::init<const servoce::shape&>(), ungil())
	.def(py::init<const servoce::shape&, const servoce::color&>(), ungil())
	.def("set_color", (void(interactive_object::*)(const servoce::color&))&interactive_object::set_color, ungil())
	.def("set_color", (void(interactive_object::*)(float,float,float,float))&interactive_object::set_color, py::arg("r"), py::arg("g"), py::arg("b"), py::arg("a")=0, ungil())
	.def("color", &interactive_object::color, ungil())
	.def("set_location", &interactive_object::set_location, ungil())
	.def("relocate", &interactive_object::relocate, ungil())
	.def("hide", &interactive_object::hide, ungil())
	.def("bbox", &servoce::interactive_object::bounding_box, ungil())
	.def("copy", &interactive_object::copy, py::arg("bind_to_scene")=true, ungil())
	;

//	pywrap_self_transformable<servoce::interactive_object>(cls);
	pywrap_transformable<servoce::interactive_object, std::shared_ptr<servoce::interactive_object>>(cls);
}