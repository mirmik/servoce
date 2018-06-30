#include <servoce/solid.h>
#include <servoce/face.h>
#include <servoce/display.h>
#include <cmath>

int main() {

	auto base = servoce::make_box(100, 100, 100, true);
	
	auto f1 = servoce::make_ngon(35, 3).down(50);
	auto f2 = servoce::make_ngon(35, 5).rotateY(M_PI/2).left(50);
	auto f3 = servoce::make_circle(35).rotateX(M_PI/2).back(50);
	
	auto s1 = make_linear_extrude(f1, {0,0,100});
	auto s2 = make_linear_extrude(f2, {100,0,0});
	auto s3 = make_linear_extrude(f3, {0,100,0});
	
	auto m1 = base - s1 - s2 - s3;
	auto m2 = base ^ s1 ^ s2 ^ s3;
	auto m3 = s1 + s2 + s3;
	
	auto ystep = 200;
	auto xstep = 200;
	
	servoce::scene scn;

	scn.add(base.forw(ystep));

	scn.add(s1);
	scn.add(s2.left(xstep));
	scn.add(s3.right(xstep));

	scn.add(m1.back(ystep));
	scn.add(m2.left(xstep).back(ystep));
	scn.add(m3.right(xstep).back(ystep));

	servoce::display(scn);
}