#include <servoce/color.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

servoce::color::color(const py::list& lst)
{
	r = lst.size() >= 1 ? lst[0].cast<double>() : 0;
	g = lst.size() >= 2 ? lst[1].cast<double>() : 0;
	b = lst.size() >= 3 ? lst[2].cast<double>() : 0;
	a = lst.size() >= 4 ? lst[3].cast<double>() : 0;
}

servoce::color::color(const py::tuple& lst)
{
	r = lst.size() >= 1 ? lst[0].cast<double>() : 0;
	g = lst.size() >= 2 ? lst[1].cast<double>() : 0;
	b = lst.size() >= 3 ? lst[2].cast<double>() : 0;
	a = lst.size() >= 4 ? lst[3].cast<double>() : 0;
}