
#include <QtWidgets/QMainWindow>
#include <QtOpenGL/QGLWidget>
#include <QtWidgets/QApplication>

#include <servoce/servoce.h>

#include <QtWidgets/QWidget>
#include <QtOpenGL/QGLWidget>

class Disp : public QGLWidget {
//class Disp : public QWidget {
	Q_OBJECT

	servoce::view * view;

public:
	Disp(servoce::view * view, QGLWidget* parent = nullptr) : QGLWidget(parent), view(view) {
	//Disp(servoce::view * view, QWidget* parent = nullptr) : QWidget(parent), view(view) {

		setBackgroundRole( QPalette::NoRole );
			
    	//setMouseTracking(true);
    	//setFocusPolicy(Qt::StrongFocus);
	
    	//setAttribute(Qt::WA_NativeWindow, true);
    	//setAttribute(Qt::WA_PaintOnScreen, true); // disables qt double buffering (seems X11 only since qt4.5, ...)
    	//setAttribute(Qt::WA_NoSystemBackground, true);
    	//setAutoFillBackground(false);

	}

	void paintEvent(QPaintEvent* e) override {
		printf("paintevent\n");

		view->redraw();
	}
};