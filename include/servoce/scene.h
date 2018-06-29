#ifndef SERVOCE_SCENE_H
#define SERVOCE_SCENE_H

#include <servoce/topo.h>
#include <vector>
#include <cassert>

namespace servoce {
	struct color {
		float r;
		float g;
		float b;

		color() : r(0.6), g(0.6), b(0.8) {}

		color(float r, float g, float b) : r(r), g(g), b(b) {
			assert(r >= 0 && r <= 1);
			assert(g >= 0 && g <= 1);
			assert(b >= 0 && b <= 1);
		}
	};

	struct scene {
		struct shape_view {
			servoce::shape shp;
			servoce::color clr;
			shape_view(const servoce::shape& a, servoce::color color) : shp(a), clr(color) {}
		};

		std::vector<shape_view> shapes;

		void add(const servoce::shape& shp, servoce::color color = color()) {
			shapes.emplace_back(shp, color);
		}

		void add(const servoce::point3& pnt, servoce::color color = color()) {
			assert(0);
			//PANIC_TRACED("TODO");
		}

		void append(const servoce::scene& scn) {
			shapes.insert(shapes.end(), scn.shapes.begin(), scn.shapes.end());
		}
	};
}

#endif