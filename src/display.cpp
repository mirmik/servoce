#include <servoce/display.h>
#include <local/display.h>

#include <QtWidgets/QApplication>

void servoce::display(const servoce::scene& scn) {
	QLocale curLocale(QLocale("en_EN"));
	QLocale::setDefault(curLocale);

	int argc = 0;
	QApplication a(argc, nullptr);
	disp::MainWidget w;
	w.display->setScene(&scn);


	gxx::println("trace: before display");
	w.show();
	gxx::println("trace: before display");
	a.exec();

	gxx::println("trace: after display");
}