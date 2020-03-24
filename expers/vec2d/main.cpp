#include <servoce/scene.h>
#include <servoce/display.h>
#include <servoce/solid.h>

int main() 
{
	auto scn = servoce::scene();

	scn.add(servoce::box(10,20,30,false));

	servoce::show(scn);
}