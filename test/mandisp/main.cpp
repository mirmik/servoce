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

	servoce::viewer viewer( scn );
	servoce::view view( viewer.create_view() );

	Disp w(&view);
	view.set_window(w.winId());
	view.fit_all();
	
	w.show();

	a.exec();
}