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
		std::vector<shape_view> * ctr;
		int idx;

		shape_view_controller(std::vector<shape_view> * ctr, int idx) : ctr(ctr), idx(idx) {}
		shape_view_controller(const shape_view_controller& oth) : ctr(oth.ctr), idx(oth.idx) {}
		shape_view_controller(shape_view_controller&& oth) : ctr(oth.ctr), idx(oth.idx) {}

		//void set_location(double x, double y, double z);
		void set_location(const servoce::transformation& trans);
	};

	struct scene
	{
		std::vector<shape_view> shapes;
		struct viewer * vwer = nullptr;

		scene() {};
		~scene() 
		{
			//printf("scene::dtor %p\n", this);
		};
		//scene(std::initializer_list<const servoce::shape_view> shps) : shapes(shps.begin(), shps.end()) {}

		shape_view_controller add(const servoce::shape& shp, servoce::color color = mech)
		{
			//printf("add %p %d\n", this, shapes.size());
			//printf("%f %f %f", color.r, color.g, color.b);
			shapes.emplace_back(shp, color);
			shapes[shapes.size() - 1].scn = this;
			return shape_view_controller(&shapes, shapes.size() - 1);
		}

		void add(const servoce::point3& pnt, servoce::color color = mech)
		{
			printf("TODO: scene.h\n");
			exit(-1);
			//PANIC_TRACED("TODO");
		}

		void append(const servoce::scene& scn)
		{
			//shapes.insert(shapes.end(), scn.shapes.begin(), scn.shapes.end());
			for (const auto& shpview : scn.shapes) 
			{
				add(shpview.shp, shpview.m_color);
			}
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