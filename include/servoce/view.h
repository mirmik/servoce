#ifndef SERVOCE_VIEW_H
#define SERVOCE_VIEW_H

//#include <servoce/camera.h>
#include <servoce/scene.h>

class OccViewWindow;
class OccViewerContext;

namespace servoce
{
	class view
	{
		OccViewWindow* occ;

	public:
		view(OccViewWindow* view) : occ(view) {}

		void set_virtual_window(int w, int h);
		void set_window(int wind);

		void fit_all();
		void dump(const std::string& path);

		void set_triedron();

		void redraw();
		void must_be_resized();

		void see(int width = 800, int height = 600);
		void screen(const std::string& path);
	};

	class viewer
	{
		OccViewerContext* occ;

	public:
		viewer();
		viewer(const servoce::scene& scn);

		view create_view();

		/*AIS_InteractiveContext* m_context;
		V3d_Viewer* m_viewer;
		//std::vector<servoce::shape_view> sviews;

		public:
			viewer();
			viewer(const servoce::scene& scn);

			view create_view();
			void set_scene(servoce::scene* scn);
			void set_triedron_axes();*/
	};

	void see(const servoce::scene& scn);
}

#endif