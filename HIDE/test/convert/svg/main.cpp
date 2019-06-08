#include <servoce/servoce.h>
#include <servoce/convert.h>
#include <servoce/display.h>

#include <nos/print.h>
#include <nos/io/file.h>

int main() {
	auto b = servoce::rotate(servoce::vector3(1,1,1), M_PI/4)( servoce::box(10,20,30) );
	//auto b = servoce::box(10,20,30);
	//auto b = servoce::rectangle(10,20) + servoce::circle(5);
	auto txt = servoce::getSVG(b);

	nos::println(txt);

	auto file = nos::file("out.svg", "w");
	file.print(txt);

	auto project = servoce::project_builder(b);

	servoce::scene scn;
	//scn.add(project.rg1linevcompound());
	scn.add(project.vcompound().edges()[0]);
	//scn.add(project.outlinevcompound());
	//scn.add(project.outlinehcompound());
	servoce::display(scn);
}