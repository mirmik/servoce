#ifndef SERVOCE_CONVERT_H
#define SERVOCE_CONVERT_H

#include <string>

namespace servoce
{
	class shape;
	bool make_stl(const servoce::shape& shp, const std::string& path, double deflection = 0.01);

	void brep_write(const servoce::shape& shp, const std::string& path);
	servoce::shape brep_read(const std::string& path);
}

#endif