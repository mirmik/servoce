#ifndef SERVOCE_VIEW_H
#define SERVOCE_VIEW_H

#include <servoce/geombase.h>
#include <servoce/color.h>
#include <vector>
#include <memory>

struct OccViewWindow;

namespace servoce
{
	class scene;
	class shape_view_controller;

	class view
	{
	public:
		void set_virtual_window(int w, int h);
		void set_window(uintptr_t wind);
		
		void fit_all(double margin);
		void set_direction(float a, float b, float c);
		std::tuple<double, double, double> direction();
		void pan(float a, float b);
		void zoom(float a, float b, float aa, float ba);
		
		double scale();
		void set_scale(double arg);

		void start_mouse_rotation();
		void mouse_rotation();

		void dump(const std::string& path);

		void set_triedron(bool en = true);
		void set_background(const servoce::color& clr);
		void set_gradient(const servoce::color& clr1, const servoce::color& clr2);

		std::pair<uint16_t, uint16_t> size();

		void destroy();
		void redraw();
		void redraw_immediate();
		void must_be_resized();

		void remove();


		servoce::point3 eye();
		void set_eye(servoce::point3 pnt);
		servoce::point3 center();
		void set_center(servoce::point3 pnt);

		void set_orthogonal();

		void export2d();

		void see(int width = 800, int height = 600);

		void reset_orientation();
		void autoscale();
		void centering();
		void start_rotation(int x, int y, float tresh);
		void rotation(int x, int y);

		std::vector<unsigned char> rawarray();
		std::vector<unsigned char> rawarray(int w, int h);

		std::pair<servoce::point3, bool> intersect_point( double x, double y ); 

		view(OccViewWindow* occ, bool pretty);
		view(OccViewWindow* occ);
		view(const view&) = delete;
		view(view&& other) { occ = other.occ; other.occ = nullptr; }
		~view();

		void set_perspective(bool en=true);
	
	private:
		int w = 0;
		int h = 0;
		OccViewWindow* occ = nullptr;
	};

	void see(servoce::scene& scn);
}

#endif
