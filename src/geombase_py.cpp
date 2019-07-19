#include <servoce/geombase.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

servoce::point2::point2(const py::list& lst)
{
	x = lst.size() >= 1 ? lst[0].cast<double>() : 0;
	y = lst.size() >= 2 ? lst[1].cast<double>() : 0;
}

servoce::point2::point2(const py::tuple& lst)
{
	x = lst.size() >= 1 ? lst[0].cast<double>() : 0;
	y = lst.size() >= 2 ? lst[1].cast<double>() : 0;
}

servoce::point3::point3(const py::list& lst)
{
	x = lst.size() >= 1 ? lst[0].cast<double>() : 0;
	y = lst.size() >= 2 ? lst[1].cast<double>() : 0;
	z = lst.size() >= 3 ? lst[2].cast<double>() : 0;
}

servoce::point3::point3(const py::tuple& lst)
{
	x = lst.size() >= 1 ? lst[0].cast<double>() : 0;
	y = lst.size() >= 2 ? lst[1].cast<double>() : 0;
	z = lst.size() >= 3 ? lst[2].cast<double>() : 0;
}

servoce::vector3::vector3(const py::list& lst)
{
	x = lst.size() >= 1 ? lst[0].cast<double>() : 0;
	y = lst.size() >= 2 ? lst[1].cast<double>() : 0;
	z = lst.size() >= 3 ? lst[2].cast<double>() : 0;
}

servoce::vector3::vector3(const py::tuple& lst)
{
	x = lst.size() >= 1 ? lst[0].cast<double>() : 0;
	y = lst.size() >= 2 ? lst[1].cast<double>() : 0;
	z = lst.size() >= 3 ? lst[2].cast<double>() : 0;
}

servoce::quaternion::quaternion(const py::list& lst)
{
	x = lst.size() >= 1 ? lst[0].cast<double>() : 0;
	y = lst.size() >= 2 ? lst[1].cast<double>() : 0;
	z = lst.size() >= 3 ? lst[2].cast<double>() : 0;
	w = lst.size() >= 4 ? lst[3].cast<double>() : 0;
}

servoce::quaternion::quaternion(const py::tuple& lst)
{
	x = lst.size() >= 1 ? lst[0].cast<double>() : 0;
	y = lst.size() >= 2 ? lst[1].cast<double>() : 0;
	z = lst.size() >= 3 ? lst[2].cast<double>() : 0;
	w = lst.size() >= 4 ? lst[3].cast<double>() : 0;
}
