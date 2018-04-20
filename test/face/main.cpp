#include <servoce/face.h>
#include <servoce/display.h>

int main() {
	auto circle = servoce::prim2d::make_circle(10);
	
	servoce::scene scn;
	scn.add(circle);

	servoce::display(scn);
}