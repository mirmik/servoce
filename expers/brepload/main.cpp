#include <servoce/servoce.h>
#include <servoce/display.h>

int main() 
{
	servoce::curve3::curve3 curve { new servoce::curve3::ACurve() };
	auto shp = servoce::make_edge(curve, -1, 1);
	auto shp2 = servoce::sphere(30);

	servoce::scene scn;

	scn.add(shp);
	//scn.add(shp2);
	servoce::display(scn);

	//auto b = servoce::box(20,20,20);
	//servoce::brep_write(shp, "model.brep");
}