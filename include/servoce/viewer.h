#ifndef SERVOCE_VIEWER_H
#define SERVOCE_VIEWER_H

#include <servoce/shape_view.h>
#include <servoce/view.h>

class OccViewerContext;

namespace servoce 
{
	class viewer
	{
	public:
		OccViewerContext* occ = nullptr;

	public:
		viewer();
		~viewer();
		
		view create_view();
		void close();

		void set_triedron_axes(bool en = true);
		void redraw();

		void add_scene(scene& scn);
		void clean_context();
		void display(shape_view& controller);
		void display(interactive_object& controller);
	};
}

#endif