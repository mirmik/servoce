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

	struct scene;
	struct viewer;

	struct shape_view
	{
		servoce::shape shp;
		scene* scn = nullptr;
		AIS_Shape* m_ashp = nullptr;
		servoce::color m_color;

		shape_view() {}
		shape_view(const servoce::shape& a, servoce::color color = servoce::color {0.6, 0.6, 0.8});
		shape_view(const shape_view& oth);
		shape_view(shape_view&& oth);

		servoce::shape shape();
		servoce::color color();

		shape_view& operator=(const shape_view& oth);
		shape_view& operator=(shape_view&& oth);
	};

	struct shape_view_controller 
	{
		shape_view * ctr;

		shape_view_controller(shape_view * ctr) : ctr(ctr) {}
		shape_view_controller(const shape_view_controller& oth) : ctr(oth.ctr) {}

		void set_location(double x, double y, double z);
	};

	struct scene
	{
		std::vector<shape_view> shapes;
		struct viewer * vwer = nullptr;

		scene() {};
		scene(std::initializer_list<const servoce::shape_view> shps) : shapes(shps.begin(), shps.end()) {}

		shape_view_controller add(const servoce::shape& shp, servoce::color color = mech)
		{
			shapes.emplace_back(shp, color);
			shapes[shapes.size() - 1].scn = this;
			return shape_view_controller(&shapes[shapes.size() - 1]);
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

		shape_view& operator[](size_t i) 
		{
			return shapes[i];
		}

		const shape_view& operator[](size_t i) const
		{
			return shapes[i];
		}
	};
}

#endif