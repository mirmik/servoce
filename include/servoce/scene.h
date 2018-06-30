#ifndef SERVOCE_SCENE_H
#define SERVOCE_SCENE_H

#include <servoce/topo.h>
#include <vector>
#include <cassert>

namespace servoce {
	struct color { float r, g, b; };

	static constexpr color white = 	color { 1,1,1 };
	static constexpr color black = 	color { 0,0,0 };
	static constexpr color red = 	color { 1,0,0 };
	static constexpr color green = 	color { 0,1,0 };
	static constexpr color blue = 	color { 0,0,1 };

	static constexpr color gray = 	color { 0.5,0.5,0.5 };
	static constexpr color mech = 	color { 0.6,0.6,0.8 };

	struct scene {
		struct shape_view {
			servoce::shape shp;
			servoce::color clr;
			shape_view(const servoce::shape& a, servoce::color color) : shp(a), clr(color) {}
		};

		std::vector<shape_view> shapes;

		void add(const servoce::shape& shp, servoce::color color = mech) {
			shapes.emplace_back(shp, color);
		}

		void add(const servoce::point3& pnt, servoce::color color = mech) {
			assert(0);
			//PANIC_TRACED("TODO");
		}

		void append(const servoce::scene& scn) {
			shapes.insert(shapes.end(), scn.shapes.begin(), scn.shapes.end());
		}
	};
}

#endif