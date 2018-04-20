#include <servoce/wire.h>
#include <servoce/solid.h>
#include <servoce/display.h>

int main() {
	servoce::point3 a(0,0,0);
	servoce::point3 b(0,10,20);

	auto segment = servoce::curve::make_segment(a, b);
	
	servoce::scene scn;
	scn.add(segment);
	scn.add(helix);
	
	servoce::display(scn);
}