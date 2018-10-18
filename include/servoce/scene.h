#ifndef SERVOCE_SCENE_H
#define SERVOCE_SCENE_H

#include <servoce/topo.h>
#include <vector>
#include <cassert>

class AIS_Shape;

namespace servoce
{
	struct color { float r, g, b; };

	static constexpr color white = 	color { 1, 1, 1 };
	static constexpr color black = 	color { 0, 0, 0 };
	static constexpr color red = 	color { 1, 0, 0 };
	static constexpr color green = 	color { 0, 1, 0 };
	static constexpr color blue = 	color { 0, 0, 1 };

	static constexpr color gray = 	color { 0.5, 0.5, 0.5 };
	static constexpr color mech = 	color { 0.6, 0.6, 0.8 };

	struct shape_view
	{
		AIS_Shape* m_ashp;
		shape_view() {}
		shape_view(const servoce::shape& a, servoce::color color = servoce::color {0.6, 0.6, 0.8});
		shape_view(const shape_view& oth);
		shape_view(shape_view&& oth);

		shape_view& operator=(const shape_view& oth);
		shape_view& operator=(shape_view&& oth);
	};

	struct scene
	{
		std::vector<shape_view> shapes;

		scene() {};
		scene(std::initializer_list<const servoce::shape_view> shps) : shapes(shps.begin(), shps.end()) {}

		void add(const servoce::shape& shp, servoce::color color = mech)
		{
			shapes.emplace_back(shp, color);
		}

		void add(const servoce::point3& pnt, servoce::color color = mech)
		{
			assert(0);
			//PANIC_TRACED("TODO");
		}

		void append(const servoce::scene& scn)
		{
			shapes.insert(shapes.end(), scn.shapes.begin(), scn.shapes.end());
		}
	};
}

#endif