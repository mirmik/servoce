#include <servoce/display.h>
#include <local/display.h>
//#include <shower/display.h>

#include <QtWidgets/QApplication>

void servoce::display(const servoce::scene& scn) {
	QLocale curLocale(QLocale("en_EN"));
	QLocale::setDefault(curLocale);

	int argc = 0;
	QApplication a(argc, nullptr);
	auto w = new disp::DisplayWidget;
	w->setScene(&scn);

	w->show();
	a.exec();
}

/*#include <servoce/widgets/gtk_widget.h>
void servoce::show(const servoce::scene& scn) {
	servoce::gtk_widget_show(scn);
}*/

/*void servoce::show_future(const servoce::scene& scn) {
	QLocale curLocale(QLocale("en_EN"));
	QLocale::setDefault(curLocale);

	int argc = 0;
	QApplication a(argc, nullptr);
	auto w = new future::disp::MainWidget;
	w->display->setScene(&scn);

	w->show();
	a.exec();	
}*/