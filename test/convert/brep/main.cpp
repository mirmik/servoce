#include <servoce/servoce.h>
#include <servoce/display.h>

int main() {
	auto b = servoce::make_box(10,20,30);
	servoce::brep_write(b, "box.brep");

	auto bb = servoce::brep_read("box.brep");


	servoce::scene scn;
	scn.add(bb);
	servoce::display(scn);
}