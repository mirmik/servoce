#include <servoce/wire.h>
#include <servoce/solid.h>
#include <servoce/display.h>

int main() {
	servoce::point3 a(0,0,0);
	servoce::point3 b(0,10,20);

	auto segment = servoce::curve::make_segment(a, b);
	auto helix = servoce::curve::make_long_helix(1, 10, 10);
	
	servoce::scene scn;
	scn.add(segment);
	scn.add(helix.right(30));
	
	servoce::display(scn);
}