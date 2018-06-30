#ifndef SERVOCE_VIEW_H
#define SERVOCE_VIEW_H

#include <servoce/camera.h>
#include <servoce/scene.h>

namespace servoce {
	class viewer {
		servoce::camera* cam;
		servoce::scene* scn;

		int width = 800;
		int height = 600;

		bool trg = false;

	public:
		viewer(camera* cam, scene* scn) : cam(cam), scn(scn) {}

		void trigedron(bool en = true) { trg = en; }

		void see();
		void screen(const std::string& path);
	};
}

#endif