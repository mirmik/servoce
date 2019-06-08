#include <servoce/servoce.h>
#include <servoce/display.h>
#include <servoce/trans.h>

int main() {
	auto sphere = servoce::sphere(10);
	servoce::scene scn;

	auto tr = servoce::scaleX(2);

	auto trsphere = tr(sphere);

	scn.add(trsphere,	servoce::white);
	servoce::display(scn);
}