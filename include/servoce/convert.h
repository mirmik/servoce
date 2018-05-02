#ifndef SERVOCE_CONVERT_H
#define SERVOCE_CONVERT_H

#include <string>

namespace servoce {
	class shape;
	void make_stl(const std::string& path, const servoce::shape& shp);
}

#endif