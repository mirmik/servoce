#ifndef SERVOCE_SCENE_H
#define SERVOCE_SCENE_H

#include <servoce/shape_view.h>
#include <servoce/viewer.h>
#include <servoce/topo.h>

#include <list>
#include <memory>

class AIS_Shape;

namespace servoce
{
	struct scene;
	struct viewer;

	struct scene
	{
		std::list<std::shared_ptr<shape_view>> shape_views;
		servoce::viewer vwer;

		scene();

		servoce::viewer& viewer() { return vwer; }
		const servoce::viewer& viewer() const { return vwer; }

		std::shared_ptr<shape_view> add(const servoce::shape& shp, servoce::color color = mech);
		std::shared_ptr<shape_view> add(const servoce::point3& pnt, servoce::color color = mech);
		void append(const servoce::scene& scn);

		std::vector<servoce::shape> shapes_array();
		std::vector<servoce::color> color_array();

		std::shared_ptr<servoce::shape_view> operator[](int idx) 
		{ 
			auto it = shape_views.begin();
			std::advance(it, idx);
			return *it; 
		}
	};
}

#endif