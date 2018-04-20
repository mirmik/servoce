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


	w.show();
	a.exec();
}