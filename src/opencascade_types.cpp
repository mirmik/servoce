#include <servoce/opencascade_types.h>

TColgp_Array1OfPnt servoce::opencascade_array1_of_pnt(const std::vector<point3>& arr)
{
	TColgp_Array1OfPnt ret(1, arr.size());
	for (unsigned int i = 0; i < arr.size(); ++i) ret.SetValue(i + 1, arr[i].Pnt());
	return ret;
}

TColgp_Array2OfPnt servoce::opencascade_array2_of_pnt(const std::vector<std::vector<point3>>& arr)
{
	TColgp_Array2OfPnt ret(1, arr.size(), 1, arr[0].size());
	for (unsigned int r = 0; r < arr.size(); ++r) 
		for (unsigned int c = 0; c < arr[0].size(); ++c) 
			ret.SetValue(r+1, c+1, arr[r][c].Pnt());
	return ret;
}

TColStd_Array1OfReal servoce::opencascade_array1_of_real(const std::vector<double>& arr)
{

	TColStd_Array1OfReal ret(1, arr.size());
	for (unsigned int i = 0; i < arr.size(); ++i) ret.SetValue(i + 1, arr[i]);
	return ret;
}

TColStd_Array1OfInteger servoce::opencascade_array1_of_int(const std::vector<int>& arr)
{
	TColStd_Array1OfInteger ret(1, arr.size());
	for (unsigned int i = 0; i < arr.size(); ++i) ret.SetValue(i + 1, arr[i]);
	return ret;
}
