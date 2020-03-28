#ifndef SERVOCE_TRIANGULATION_H
#define SERVOCE_TRIANGULATION_H

#include <servoce/geombase.h>
#include <servoce/shape.h>
#include <servoce/face.h>

namespace servoce 
{
	std::pair<std::vector<servoce::point3>, std::vector<std::tuple<int,int,int>>> 
	triangulation(servoce::shape& shp, double deflection);

	std::pair<std::vector<servoce::point3>, std::vector<std::tuple<int,int,int>>> 
	triangulation(servoce::face_shape& shp, double deflection);
}

#endif