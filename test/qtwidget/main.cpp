#include <servoce/solid.h>
#include <servoce/boolops.h>

#include <servoce/display.h>

int main() {
	auto m1 = servoce::prim3d::make_box(1,1,1);
	auto m2 = servoce::prim3d::make_sphere(1);

	auto m3 = servoce::boolops::make_union(m1, m2);

	servoce::scene scn;
	scn.add(m1);
	scn.add(m2);
	scn.add(m3);

	servoce::display(scn);
}