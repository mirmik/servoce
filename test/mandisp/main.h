
#include <QtWidgets/QMainWindow>
#include <QtOpenGL/QGLWidget>
#include <QtWidgets/QApplication>

#include <servoce/servoce.h>

#include <QtWidgets/QWidget>
#include <QtOpenGL/QGLWidget>

class Disp : public QGLWidget {
//class Disp : public QWidget {
	Q_OBJECT

	servoce::scene * scene;
	servoce::viewer * viewer;
	servoce::view * view;

	int inited = 0;
	int showed = 0;

public:
	Disp(servoce::scene * scn, QGLWidget* parent = nullptr) : QGLWidget(parent), scene(scn) {
	//Disp(servoce::view * view, QWidget* parent = nullptr) : QWidget(parent), view(view) {

		//resize(800,600);


		setBackgroundRole( QPalette::NoRole );
			
    	//setMouseTracking(true);
    	//setFocusPolicy(Qt::StrongFocus);
	
    	//setAttribute(Qt::WA_NativeWindow, true);
    	setAttribute(Qt::WA_PaintOnScreen, true); // disables qt double buffering (seems X11 only since qt4.5, ...)
    	//setAttribute(Qt::WA_NoSystemBackground, true);
    	//setAutoFillBackground(false);
	}

	QPaintEngine* paintEngine() const override {
		return nullptr;
	}


	void paintEvent(QPaintEvent* e) override {
		printf("paintevent\n");

		if (!inited) {
			init();
		}

		view->redraw();
	}

	void init() {
		printf("init!\n");
		viewer = new servoce::viewer( *scene );
		view = new servoce::view( viewer->create_view() );
		
		view->set_window(winId());
		view->fit_all();
		//view->must_be_resized();

		inited = 1;
		//update();
	}

	void showEvent(QShowEvent* e) override {
		printf("showevent\n");
		showed = 1;
		if (inited)
			view->redraw();
	}

	void resizeEvent(QResizeEvent* e) override {
		printf("resizeevent\n");
		if (!inited && showed)
			init();

		if (inited)
			view->must_be_resized();
	}
};