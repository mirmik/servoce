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
	.def("translate", (RetCls(Cls::*)(double,double,double))&transformable<Cls,RetCls>::translate, py::arg("x")=0, py::arg("y")=0, py::arg("z")=0, ungil())
	.def("translate", (RetCls(Cls::*)(vector3))&transformable<Cls,RetCls>::translate, py::arg("v"), ungil())
	
	.def("move", (RetCls(transformable<Cls,RetCls>::*)(double,double,double))&transformable<Cls,RetCls>::move, py::arg("x")=0, py::arg("y")=0, py::arg("z")=0, ungil())
	.def("move", (RetCls(transformable<Cls,RetCls>::*)(vector3))&transformable<Cls,RetCls>::move, py::arg("v"), ungil())
	.def("moveX", &transformable<Cls,RetCls>::moveX, ungil())
	.def("moveY", &transformable<Cls,RetCls>::moveY, ungil())
	.def("moveZ", &transformable<Cls,RetCls>::moveZ, ungil())

	.def("mov", (RetCls(transformable<Cls,RetCls>::*)(double,double,double))&transformable<Cls,RetCls>::move, py::arg("x")=0, py::arg("y")=0, py::arg("z")=0, ungil())
	.def("mov", (RetCls(transformable<Cls,RetCls>::*)(vector3))&transformable<Cls,RetCls>::move, py::arg("v"), ungil())
	.def("movX",(RetCls(transformable<Cls,RetCls>::*)(double))&transformable<Cls,RetCls>::moveX, ungil())
	.def("movY", (RetCls(transformable<Cls,RetCls>::*)(double))&transformable<Cls,RetCls>::moveY, ungil())
	.def("movZ", (RetCls(transformable<Cls,RetCls>::*)(double))&transformable<Cls,RetCls>::moveZ, ungil())
	
	.def("up", (RetCls(transformable<Cls,RetCls>::*)(double))&transformable<Cls,RetCls>::up, ungil())
	.def("down", (RetCls(transformable<Cls,RetCls>::*)(double))&transformable<Cls,RetCls>::down, ungil())	
	.def("right", (RetCls(transformable<Cls,RetCls>::*)(double))&transformable<Cls,RetCls>::right, ungil())
	.def("left", (RetCls(transformable<Cls,RetCls>::*)(double))&transformable<Cls,RetCls>::left, ungil())
	.def("forw", (RetCls(transformable<Cls,RetCls>::*)(double))&transformable<Cls,RetCls>::forw, ungil())
	.def("back", (RetCls(transformable<Cls,RetCls>::*)(double))&transformable<Cls,RetCls>::back, ungil())
	
	.def("rotate", (RetCls(transformable<Cls,RetCls>::*)(double,double,double))&transformable<Cls,RetCls>::rotate, py::arg("x")=0, py::arg("y")=0, py::arg("z")=0, ungil())	
	.def("rotate", (RetCls(transformable<Cls,RetCls>::*)(double,vector3))&transformable<Cls,RetCls>::rotate, py::arg("a"), py::arg("v"), ungil())	
	.def("rotateX", (RetCls(transformable<Cls,RetCls>::*)(double))&transformable<Cls,RetCls>::rotateX, ungil())
	.def("rotateY", (RetCls(transformable<Cls,RetCls>::*)(double))&transformable<Cls,RetCls>::rotateY, ungil())
	.def("rotateZ", (RetCls(transformable<Cls,RetCls>::*)(double))&transformable<Cls,RetCls>::rotateZ, ungil())
	
	.def("rot", (RetCls(transformable<Cls,RetCls>::*)(double,double,double))&transformable<Cls,RetCls>::rotate, py::arg("x")=0, py::arg("y")=0, py::arg("z")=0, ungil())	
	.def("rot", (RetCls(transformable<Cls,RetCls>::*)(double,vector3))&transformable<Cls,RetCls>::rotate, py::arg("a"), py::arg("v"), ungil())	
	.def("rotX", (RetCls(transformable<Cls,RetCls>::*)(double))&transformable<Cls,RetCls>::rotateX, ungil())
	.def("rotY", (RetCls(transformable<Cls,RetCls>::*)(double))&transformable<Cls,RetCls>::rotateY, ungil())
	.def("rotZ", (RetCls(transformable<Cls,RetCls>::*)(double))&transformable<Cls,RetCls>::rotateZ, ungil())
	
	.def("mirrorO", (RetCls(transformable<Cls,RetCls>::*)())&transformable<Cls,RetCls>::mirrorO, ungil())
	.def("mirrorX", (RetCls(transformable<Cls,RetCls>::*)())&transformable<Cls,RetCls>::mirrorX, ungil())
	.def("mirrorY", (RetCls(transformable<Cls,RetCls>::*)())&transformable<Cls,RetCls>::mirrorY, ungil())
	.def("mirrorZ", (RetCls(transformable<Cls,RetCls>::*)())&transformable<Cls,RetCls>::mirrorZ, ungil())
	.def("mirrorXY", (RetCls(transformable<Cls,RetCls>::*)())&transformable<Cls,RetCls>::mirrorXY, ungil())
	.def("mirrorYZ", (RetCls(transformable<Cls,RetCls>::*)())&transformable<Cls,RetCls>::mirrorYZ, ungil())
	.def("mirrorXZ", (RetCls(transformable<Cls,RetCls>::*)())&transformable<Cls,RetCls>::mirrorXZ, ungil())
	
	.def("scale", 	 &transformable<Cls,RetCls>::scale,    ungil(), py::arg("factor"), py::arg("center") = point3())
	.def("scaleX",   (RetCls(transformable<Cls,RetCls>::*)(double))&transformable<Cls,RetCls>::scaleX,   ungil(), py::arg("factor"))
	.def("scaleY",   (RetCls(transformable<Cls,RetCls>::*)(double))&transformable<Cls,RetCls>::scaleY,   ungil(), py::arg("factor"))
	.def("scaleZ",   (RetCls(transformable<Cls,RetCls>::*)(double))&transformable<Cls,RetCls>::scaleZ,   ungil(), py::arg("factor"))
	.def("scaleXY",  (RetCls(transformable<Cls,RetCls>::*)(double,double))&transformable<Cls,RetCls>::scaleXY,  ungil(), py::arg("x"), py::arg("y"))
	.def("scaleYZ",  (RetCls(transformable<Cls,RetCls>::*)(double,double))&transformable<Cls,RetCls>::scaleYZ,  ungil(), py::arg("y"), py::arg("z"))
	.def("scaleXZ",  (RetCls(transformable<Cls,RetCls>::*)(double,double))&transformable<Cls,RetCls>::scaleXZ,  ungil(), py::arg("x"), py::arg("z"))
	.def("scaleXYZ", (RetCls(transformable<Cls,RetCls>::*)(double,double,double))&transformable<Cls,RetCls>::scaleXYZ, ungil(), py::arg("x"), py::arg("y"), py::arg("z")) 
	;
}

template <class Cls>
static inline void pywrap_self_transformable(auto cls) 
{
	cls
	.def("self_transform", [](Cls& obj, const servoce::transformation& trans){ obj.self_transform(trans); return obj; }, ungil())
	.def("translate", [](Cls& obj, double x, double y, double z){ obj.self_translate(x,y,z); return obj; }, py::arg("x")=0, py::arg("y")=0, py::arg("z")=0, ungil())
	.def("translate", [](Cls& obj, vector3 v){ obj.self_translate(v); return obj; }, py::arg("v"), ungil())
	;
}

#endif