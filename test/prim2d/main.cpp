#include <servoce/face.h>
#include <servoce/display.h>

int main() {
	auto circle = servoce::make_circle(10);
	auto polygon = servoce::make_polygon( { {-10,-10}, {-10,10}, {10,-10} } );
	auto ngon = servoce::make_ngon( 10, 6 );
	auto square = servoce::make_square( 20, true );
	auto rectangle = servoce::make_rectangle( 20, 30, true );

	//auto circle = servoce::make_circle(10);	
	servoce::scene scn;
	scn.add(circle);
	scn.add(polygon.right(30));
	scn.add(ngon.right(60));
	scn.add(square.right(90));
	scn.add(rectangle.right(120));

	servoce::display(scn);
}