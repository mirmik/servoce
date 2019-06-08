#include <servoce/solid.h>
#include <servoce/boolops.h>

#include <servoce/display.h>

int main() {
	auto m1 = servoce::make_torus(3,3);
	auto m2 = servoce::make_section(m1);

	servoce::scene scn;
	scn.add(m2);
	servoce::display(scn);
}