#ifndef SERVOCE_SCENE_H
#define SERVOCE_SCENE_H

#include <servoce/shape_view.h>
#include <servoce/interactive_object.h>
#include <servoce/viewer.h>
#include <servoce/shape.h>

#include <list>
#include <memory>

class AIS_Shape;
class AIS_InteractiveContext;

namespace servoce
{
	class scene;
	class viewer;

	class scene
	{
	public:
		//std::list<std::shared_ptr<shape_view>> shape_views;
		std::list<std::shared_ptr<interactive_object>> iobjs;
		std::shared_ptr<servoce::viewer> vwer;

		scene();

		std::shared_ptr<servoce::viewer> viewer()
		{
			if (vwer.get() == nullptr)
				throw std::runtime_error("viewer is not inited");
			return vwer;
		}
		const std::shared_ptr<servoce::viewer> viewer() const
		{
			if (vwer.get() == nullptr)
				throw std::runtime_error("viewer is not inited");
			return vwer;
		}

		std::shared_ptr<interactive_object> add(const servoce::shape& shp, servoce::color color = mech);
		std::shared_ptr<interactive_object> add(const servoce::point3& pnt, servoce::color color = mech);
		std::shared_ptr<interactive_object> add(std::shared_ptr<servoce::interactive_object> iobj);

		//void append(const servoce::scene& scn);

		//std::vector<servoce::shape> shapes_array();
		//std::vector<servoce::color> color_array();

		AIS_InteractiveContext* InteractiveContext();

		std::shared_ptr<servoce::interactive_object> operator[](int idx)
		{
			auto it = iobjs.begin();
			std::advance(it, idx);
			return *it;
		}

		size_t total() {return iobjs.size();}
	};
}

#endif