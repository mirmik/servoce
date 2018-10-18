#include <servoce/solid.h>
#include <servoce/face.h>
#include <servoce/display.h>
#include <servoce/servoce.h>
#include <cmath>		

#include <QtWidgets/QMainWindow>
#include <QtOpenGL/QGLWidget>
#include <QtWidgets/QApplication>

#include <main.h>

int main(int argc, char**argv) {

	auto m = servoce::make_box(100, 100, 100, true);
	servoce::scene scn { m };
	
	QApplication a(argc, argv);

	//servoce::viewer viewer( scn );
	//servoce::view view( viewer.create_view() );

	QMainWindow mw;
	Disp w(&scn);

	mw.setCentralWidget(&w);

	mw.show();
	//mw.resize(800,600);	

	a.exec();
}