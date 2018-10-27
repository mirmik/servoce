#include <servoce/camera.h>
#include <servoce/view.h>
#include <servoce/display.h>
#include <servoce/scene.h>
#include <servoce/solid.h>

int main() {
	servoce::drone_camera cam;
	cam.pitch(0);
	cam.yaw(0);

	auto model = servoce::make_box(100,100,100) + servoce::make_sphere(100);
	auto model2 = servoce::make_sphere(100).left(200);
	auto model3 = servoce::make_box(100,100,100).right(200);
	
	servoce::scene scn { 
		model,
		{ model2, servoce::green },
		{ model3, servoce::blue },
	};

//	servoce::see(scn);
	
	servoce::viewer vw(scn);
	servoce::view v = vw.create_view();


	v.screen("screen.png");
	//servoce::screen(scn);
}