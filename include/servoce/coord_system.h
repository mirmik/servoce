#ifndef SERVOCE_COORD_SYSTEM_H
#define SERVOCE_COORD_SYSTEM_H

#include <servoce/transformable.h>
#include <servoce/transformable_impl.h>
#include <servoce/trans.h>

#include <servoce/self_transformable.h>

#include <memory>
#include <list>

namespace servoce 
{
	class coord_system //: public self_transformable
	{
	public:
		std::shared_ptr<coord_system> parent = nullptr;
		std::list<std::shared_ptr<coord_system>> childs;

		transformation location;
		transformation global_location;

		void location_update(bool deep = true) 
		{
			if (parent) 
			{
				global_location = parent->global_location * location;
			}

			else 
			{
				global_location = location;
			}

			on_location_update_handle();

			if (deep) 
				for (auto c : childs) 
					c->location_update(true);
		}

		virtual void on_location_update_handle() = 0;

		void relocate(transformation trans, bool deep = true) 
		{
			location = trans;
			location_update(deep);
		}

		void add_child(std::shared_ptr<coord_system> child) 
		{
			childs.push_back(child);
		}
	};
}

#endif