#include <servoce/solid.h>
#include <servoce/display.h>

int main() {
	auto box = servoce::prim3d::make_box(10,10,10,true);
	auto sphere = servoce::prim3d::make_sphere(10);
	auto cylinder = servoce::prim3d::make_cylinder(10,10,true);
	auto cone = servoce::prim3d::make_cone(10,5,10,true);
	auto torus = servoce::prim3d::make_torus(10, 3);

	servoce::scene scn;
	scn.add(box.left(60));
	scn.add(sphere.left(30));
	scn.add(cylinder);
	scn.add(cone.right(30));
	scn.add(torus.right(60));

	servoce::display(scn);
}