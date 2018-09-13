#include <servoce/solid.h>
#include <servoce/scene.h>
#include <servoce/display.h>

int main() {
	auto base = servoce::make_box(100, 100, 100, true);

	servoce::scene scn;

	scn.add(base);
	servoce::show_future(scn);
}