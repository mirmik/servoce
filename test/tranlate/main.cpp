#include <servoce/solid.h>
#include <servoce/boolops.h>

#include <servoce/display.h>

int main() {
	auto m1 = servoce::prim3d::make_box(10,10,10);
	auto m2 = m1.translate(10,20,30);

	servoce::scene scn;
	scn.add(m1);
	scn.add(m2);
	servoce::display(scn);
}