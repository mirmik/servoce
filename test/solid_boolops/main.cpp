#include <servoce/solid.h>
#include <servoce/boolops.h>
#include <servoce/display.h>

int main() {
	auto box = servoce::prim3d::make_box(10,10,10);
	auto sphere = servoce::prim3d::make_sphere(10);
	auto cylinder = servoce::prim3d::make_cylinder(10,10);

	std::vector<const servoce::solid*> vec {&box, &sphere, &cylinder};

	auto uu = servoce::boolops::make_union(vec);
	auto u = servoce::boolops::make_union(box, sphere);
	auto d = servoce::boolops::make_difference(box, sphere);
	auto i = servoce::boolops::make_intersect(box, sphere);

	servoce::scene scn;
	scn.add(uu);
	scn.add(u.left(60));
	scn.add(d.left(30));
	scn.add(i.right(30));

	servoce::display(scn);
}