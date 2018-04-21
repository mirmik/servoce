#include <servoce/solid.h>
#include <servoce/boolops.h>
#include <servoce/display.h>

int main() {
	auto box = servoce::prim3d::make_box(10,10,10);
	auto sphere = servoce::prim3d::make_sphere(10);

	auto u = servoce::boolops::make_union(box, sphere);
	auto d = servoce::boolops::make_difference(box, sphere);
	auto i = servoce::boolops::make_intersect(box, sphere);

	servoce::scene scn;
	scn.add(u);
	scn.add(d.left(30));
	scn.add(i.right(30));

	servoce::display(scn);
}