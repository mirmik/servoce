#ifndef SERVOCE_PYWRAP_TRANSFORMABLE_H
#define SERVOCE_PYWRAP_TRANSFORMABLE_H

#include <servoce/trans.h>
#include <servoce/transformable.h>
#include <servoce/transformable_impl.h>

#include <servoce/geombase.h>

namespace py = pybind11;
using namespace servoce;

template <class Cls, class RetCls=Cls>
static inline void pywrap_transformable(auto cls) 
{
	cls
	.def("transform", (RetCls(Cls::*)(const servoce::transformation& trans) const) &Cls::transform, ungil())
	.def("transform", (RetCls(Cls::*)(const servoce::general_transformation& trans) const) &Cls::transform, ungil())	
	.def("translate", (RetCls(Cls::*)(double,double,double))&Cls::translate, py::arg("x")=0, py::arg("y")=0, py::arg("z")=0, ungil())
	.def("translate", (RetCls(Cls::*)(vector3))&Cls::translate, py::arg("v"), ungil())
	
	.def("move", (RetCls(Cls::*)(double,double,double))&Cls::move, py::arg("x")=0, py::arg("y")=0, py::arg("z")=0, ungil())
	.def("move", (RetCls(Cls::*)(vector3))&Cls::move, py::arg("v"), ungil())
	.def("moveX", &Cls::moveX, ungil())
	.def("moveY", &Cls::moveY, ungil())
	.def("moveZ", &Cls::moveZ, ungil())

	.def("mov", (RetCls(Cls::*)(double,double,double))&Cls::move, py::arg("x")=0, py::arg("y")=0, py::arg("z")=0, ungil())
	.def("mov", (RetCls(Cls::*)(vector3))&Cls::move, py::arg("v"), ungil())
	.def("movX", &Cls::moveX, ungil())
	.def("movY", &Cls::moveY, ungil())
	.def("movZ", &Cls::moveZ, ungil())
	
	.def("up", &Cls::up, ungil())
	.def("down", &Cls::down, ungil())	
	.def("right", &Cls::right, ungil())
	.def("left", &Cls::left, ungil())
	.def("forw", &Cls::forw, ungil())
	.def("back", &Cls::back, ungil())
	
	.def("rotate", (RetCls(Cls::*)(double,double,double))&Cls::rotate, py::arg("x")=0, py::arg("y")=0, py::arg("z")=0, ungil())	
	.def("rotate", (RetCls(Cls::*)(double,vector3))&Cls::rotate, py::arg("a"), py::arg("v"), ungil())	
	.def("rotateX", &Cls::rotateX, ungil())
	.def("rotateY", &Cls::rotateY, ungil())
	.def("rotateZ", &Cls::rotateZ, ungil())
	
	.def("rot", (RetCls(Cls::*)(double,double,double))&Cls::rotate, py::arg("x")=0, py::arg("y")=0, py::arg("z")=0, ungil())	
	.def("rot", (RetCls(Cls::*)(double,vector3))&Cls::rotate, py::arg("a"), py::arg("v"), ungil())	
	.def("rotX", &Cls::rotateX, ungil())
	.def("rotY", &Cls::rotateY, ungil())
	.def("rotZ", &Cls::rotateZ, ungil())
	
	.def("mirrorX", &Cls::mirrorX, ungil())
	.def("mirrorY", &Cls::mirrorY, ungil())
	.def("mirrorZ", &Cls::mirrorZ, ungil())
	.def("mirrorXY", &Cls::mirrorXY, ungil())
	.def("mirrorYZ", &Cls::mirrorYZ, ungil())
	.def("mirrorXZ", &Cls::mirrorXZ, ungil())
	
	.def("scale", 	 &Cls::scale,    ungil(), py::arg("factor"), py::arg("center") = point3())
	.def("scaleX",   &Cls::scaleX,   ungil(), py::arg("factor"))
	.def("scaleY",   &Cls::scaleY,   ungil(), py::arg("factor"))
	.def("scaleZ",   &Cls::scaleZ,   ungil(), py::arg("factor"))
	.def("scaleXY",  &Cls::scaleXY,  ungil(), py::arg("x"), py::arg("y"))
	.def("scaleYZ",  &Cls::scaleYZ,  ungil(), py::arg("y"), py::arg("z"))
	.def("scaleXZ",  &Cls::scaleXZ,  ungil(), py::arg("x"), py::arg("z"))
	.def("scaleXYZ", &Cls::scaleXYZ, ungil(), py::arg("x"), py::arg("y"), py::arg("z")) 
	;
}

#endif