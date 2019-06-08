#include <servoce/solid.h>
#include <servoce/display.h>

int main() {
	auto box = servoce::prim3d::make_box(10,10,10,true);

	std::string str = box.string_dump();
	servoce::shape::restore_string_dump(str);


	while(1);

}