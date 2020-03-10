#ifndef SERVOCE_PROJECT_H
#define SERVOCE_PROJECT_H

#include <servoce/geombase.h>

namespace servoce 
{
	class edge_shape;

	servoce::point3 project(const servoce::point3& pnt, const servoce::edge_shape& tgt);
}

#endif