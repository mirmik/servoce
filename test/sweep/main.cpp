#include <servoce/face.h>
#include <servoce/solid.h>
#include <servoce/wire.h>
#include <servoce/display.h>

int main() {
	auto circ = servoce::prim2d::make_circle(30);
	auto path = servoce::curve::make_segment(servoce::point3(0,0,0), servoce::point3(0,10,10));
	auto linext = servoce::sweep3d::make_linear_extrude(circ, servoce::vector3(0,10,10)); 
	auto pipe = servoce::sweep3d::make_pipe(circ, path); 

	servoce::scene scn;
	//scn.add(linext + pipe.right(30));
	
	scn.add(linext.last());
	scn.add(linext.first());

	servoce::display(scn);
}