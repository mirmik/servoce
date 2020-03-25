#ifndef SERVOCE_PYWRAP_CURVE_ALGO_3_H
#define SERVOCE_PYWRAP_CURVE_ALGO_3_H

#include <servoce/curve_algo.h>

namespace py = pybind11;
using namespace servoce;

template <class Cls, class U>
static inline void pywrap_curve_algo3(U& cls) 
{	
	cls.def("line_parameters", &Cls::line_parameters);
	cls.def("circle_parameters", &Cls::circle_parameters);
}

#endif