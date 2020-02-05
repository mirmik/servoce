#ifndef SERVOCE_VIEWER_H
#define SERVOCE_VIEWER_H

#include <servoce/shape_view.h>
#include <servoce/interactive_object.h>
#include <servoce/view.h>

class OccViewerContext;

template<typename T>
class lazy_ptr
{
private:
	T *child;

public:
	lazy_ptr() : child(0) {}
	~lazy_ptr() { delete child; }
	
	T &operator*()
	{
		if (!child) child = new T;

		return *child;
	}

	const T &operator*() const { return *child; }
	T *operator->() { return &**this; }
	const T *operator->() const { return &**this; }
};

namespace servoce
{
	class viewer
	{
	public:
		lazy_ptr<OccViewerContext> occ;

	public:
		viewer();
		~viewer();

		view create_view();
		void close();

		void set_triedron_axes(bool en = true);
		void redraw();

		//void add_scene(scene& scn);
		void clean_context();
		//void display(shape_view& controller);
		void display(interactive_object& controller);
	};
}

#endif