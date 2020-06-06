#ifndef SERVOCE_OPENCASCADE_TYPES_H
#define SERVOCE_OPENCASCADE_TYPES_H

#include <TColgp_Array1OfPnt.hxx>
#include <TColgp_Array2OfPnt.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>

#include <vector>

#include <servoce/geombase.h>

namespace servoce 
{
	TColgp_Array1OfPnt opencascade_array1_of_pnt(const std::vector<point3>&);
	TColgp_Array2OfPnt opencascade_array2_of_pnt(const std::vector<std::vector<point3>>&);
	TColStd_Array1OfReal opencascade_array1_of_real(const std::vector<double>&);
	TColStd_Array1OfInteger opencascade_array1_of_int(const std::vector<int>&);
}

#endif