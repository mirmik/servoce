#include <servoce/camera.h>
#include <servoce/view.h>
#include <servoce/scene.h>
#include <servoce/solid.h>

int main() {
	servoce::drone_camera cam;
	cam.pitch(0);
	cam.yaw(0);

	auto model = servoce::make_box(100,100,100) + servoce::make_sphere(100);
	servoce::scene scn;
	scn.add(model);

	servoce::viewer vw(&cam, &scn);
	vw.trigedron();

	//vw.screen("mirmik.png");
	vw.see();
}