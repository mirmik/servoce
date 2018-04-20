#ifndef SERVOCE_SCENE_H
#define SERVOCE_SCENE_H

#include <servoce/topo.h>
#include <vector>

namespace servoce {
	struct scene {
		struct shape_view {
			servoce::shape shp;
			shape_view(const servoce::shape& a) : shp(a) {}
		};

		std::vector<shape_view> shapes;

		void add(const servoce::shape& shp) {
			shapes.emplace_back(shp);
		}
	};
}

#endif