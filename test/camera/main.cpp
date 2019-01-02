#include <servoce/camera.h>
#include <servoce/view.h>
#include <servoce/display.h>
#include <servoce/scene.h>
#include <servoce/solid.h>

#include <nos/print.h>

int main() {
	servoce::drone_camera cam;
	cam.pitch(0);
	cam.yaw(0);

	auto model = servoce::box(100,100,100) + servoce::sphere(100);
	auto model2 = servoce::sphere(100).left(200);
	auto model3 = servoce::box(100,100,100).right(200);
	
	servoce::scene scn;
	scn.add(model);
	scn.add(model2, servoce::green);
	scn.add(model3, servoce::blue);

//	servoce::see(scn);
	
	servoce::viewer vw(scn);
	servoce::view v = vw.create_view();

	//v.see();

	v.set_virtual_window(800, 600);
	v.fit_all();

	nos::println(v.rawarray());
	//servoce::screen(scn);
}