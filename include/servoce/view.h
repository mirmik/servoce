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
		void set_projection(float a, float b, float c);
		void pan(float a, float b);
		void zoom(float a, float b, float aa, float ba);

		void start_mouse_rotation();
		void mouse_rotation();

		void dump(const std::string& path);

		void set_triedron();

		void redraw();
		void must_be_resized();

		void set_gradient();

		void see(int width = 800, int height = 600);
		void screen(const std::string& path);

		void reset_orientation();
		void autoscale();
		void start_rotation(int x, int y, float tresh);
		void rotation(int x, int y);
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
			void set_scene(servoce::scene* scn);*/
		void set_triedron_axes();
	};

	void see(const servoce::scene& scn);
}

#endif