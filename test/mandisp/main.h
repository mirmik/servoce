#include <QtWidgets/QMainWindow>
#include <QtOpenGL/QGLWidget>
#include <QtWidgets/QApplication>

#include <servoce/servoce.h>
#include <servoce/linalg/linalg.h>

#include <QtWidgets/QWidget>
#include <QtOpenGL/QGLWidget>

#include <QtGui/QtGui>

using namespace linalg::aliases;

//class Disp : public QGLWidget {
class Disp : public QWidget
{
	Q_OBJECT

	servoce::scene * scene;
	servoce::viewer * viewer;
	servoce::view * view;

	int inited = 0;
	int showed = 0;
	int fitted = 0;

public:
	//Disp(servoce::scene * scn, QGLWidget* parent = nullptr) : QGLWidget(parent), scene(scn) {
	Disp(servoce::scene * scn, QWidget* parent = nullptr) : QWidget(parent), scene(scn)
	{

		//resize(800,600);


		setBackgroundRole( QPalette::NoRole );

		//setMouseTracking(true);
		//setFocusPolicy(Qt::StrongFocus);

		//setAttribute(Qt::WA_NativeWindow, true);
		setAttribute(Qt::WA_PaintOnScreen, true); // disables qt double buffering (seems X11 only since qt4.5, ...)
		//setAttribute(Qt::WA_NoSystemBackground, true);
		//setAutoFillBackground(false);
	}

	QPaintEngine* paintEngine() const override
	{
		return nullptr;
	}

	//float4 quat {1, 0, 0, 0};
	//float4 rot = linalg::normalize( float4{1, 0, 0, 0.01} );
	void paintEvent(QPaintEvent* e) override
	{
		printf("paintevent\n");

		if (!fitted)
		{
			fitted = 1;
			view->fit_all();
			view->must_be_resized();
		}

		//quat = linalg::qmul(quat, rot);
		//auto vec = linalg::qrot(quat, linalg::normalize(float3{1, 1, 1}));

		//view->set_projection(vec.x, vec.y, vec.z);

		view->redraw();
	}

	void init()
	{
		printf("init!\n");
		viewer = new servoce::viewer( *scene );
		view = new servoce::view( viewer->create_view() );

		view->set_window(winId());
		//view->fit_all();
		//view->must_be_resized();

		inited = 1;
		//update();
	}

	void showEvent(QShowEvent* e) override
	{
		printf("showevent\n");
		init();
	}

	void resizeEvent(QResizeEvent* e) override
	{
		printf("resizeevent\n");

		if (inited)
			view->must_be_resized();
	}



	QPoint temporary1;

	void onLButtonDown( const int theFlags, const QPoint thePoint )
	{
	    Q_UNUSED(theFlags);
	    temporary1 = thePoint;
	}

	float psi = 0;
	float phi = 0;

	void onMouseMove( const int theFlags, const QPoint thePoint )
	{
		QPoint mv = thePoint - temporary1;
		temporary1 = thePoint;

		if (theFlags & Qt::LeftButton)
		{
			phi -= mv.x() * 0.01;
			psi += mv.y() * 0.01;
			view->set_projection(cos(psi) * cos(phi), cos(psi) * sin(phi), sin(psi));
		}
	}






	void wheelEvent( QWheelEvent * e )
	{
	    //onMouseWheel(e->buttons(), e->delta(), e->pos());
	}
	
	void mousePressEvent( QMouseEvent* e )
	{
	    if (e->button() == Qt::LeftButton)
	    {
	        onLButtonDown((e->buttons() | e->modifiers()), e->pos());
	    }
	    else if (e->button() == Qt::MidButton)
	    {
	        //onMButtonDown((e->buttons() | e->modifiers()), e->pos());
	    }
	    else if (e->button() == Qt::RightButton)
	    {
	        //onRButtonDown((e->buttons() | e->modifiers()), e->pos());
	    }
	}
	
	void mouseReleaseEvent( QMouseEvent* e )
	{
	
	}
	
	void mouseMoveEvent( QMouseEvent * e )
	{
	    onMouseMove(e->buttons(), e->pos());
	}

};