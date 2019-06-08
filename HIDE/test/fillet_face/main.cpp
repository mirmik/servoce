#include <servoce/face.h>
#include <servoce/display.h>

int main() {
	auto ngon = servoce::make_ngon( 10, 6 );
	
	servoce::scene scn;
	scn.add(ngon.fillet(3, {0}).left(-60));
	scn.add(ngon.fillet(3, {1}).left(-30));
	scn.add(ngon.fillet(3, {2}).left(0));
	scn.add(ngon.fillet(3, {3}).left(30));
	scn.add(ngon.fillet(3, {4}).left(60));
	scn.add(ngon.fillet(3, {5}).left(90));
	
	servoce::display(scn);
}