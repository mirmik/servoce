#include <servoce/display.h>
#include <local/display.h>
//#include <shower/display.h>

#include <QtWidgets/QApplication>

void servoce::show(const servoce::scene& scn) {
	QLocale curLocale(QLocale("en_EN"));
	QLocale::setDefault(curLocale);

	int argc = 0;
	QApplication a(argc, nullptr);
	auto w = new disp::DisplayMinimal(scn);
	
	w->show();
	a.exec();
}
