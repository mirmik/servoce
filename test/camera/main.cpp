#include <servoce/camera.h>
#include <servoce/view.h>
#include <servoce/scene.h>
#include <servoce/solid.h>

int main() {
	servoce::drone_camera cam;

	auto box = servoce::make_box(100,100,100);
	servoce::scene scn;
	scn.add(box);

	servoce::viewer vw(&cam, &scn);
	vw.trigedron();

	//vw.screen("mirmik.png");
	vw.see();
}