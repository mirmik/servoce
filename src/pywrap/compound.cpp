/**
	Python bind for servoce::solid_shape
*/

#include <pybind11/pybind11.h>
#include <local/pywrap_util.h>

#include <servoce/util.h>
#include <servoce/util/b64.h>

#include <servoce/compound.h>

#include <pywrap/transformable.h>
#include <servoce/transformable_shape_impl.h>

namespace py = pybind11;
using namespace servoce;

void registry_solid_shape(py::module & m)
{
	auto cls = py::class_<compound_shape, shape>(m, "Compound")
	.def(py::pickle(
	[](const compound_shape & self) { return b64::base64_encode(string_dump(self)); },
	[](const std::string & in) { return restore_string_dump<compound_shape>(b64::base64_decode(in)); }), ungil())
	;
	pywrap_transformable<servoce::compound_shape>(cls);
}