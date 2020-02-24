#ifndef SERVOCE_PYWRAP_UTIL_H
#define SERVOCE_PYWRAP_UTIL_H

#include <servoce/geombase.h>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <vector>

namespace py = pybind11;
using ungil = py::call_guard<py::gil_scoped_release>;

std::vector<servoce::point3> points(const py::list& lst);

#endif