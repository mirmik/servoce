#ifndef SERVOCE_LOCAL_DISPLAY_H
#define SERVOCE_LOCAL_DISPLAY_H

#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMainWindow>
#include <QtOpenGL/QGLWidget>

#include <servoce/scene.h>
#include <nos/print.h>

namespace servoce
{
	namespace disp
	{
		class DisplayMinimal : public QGLWidget
		{
			Q_OBJECT

			const servoce::scene& _scene;
			bool inited = false;

			std::shared_ptr<servoce::viewer> _viewer;
			std::shared_ptr<servoce::view> _view;

		public:

			DisplayMinimal(const servoce::scene& scn) : QGLWidget(), _scene(scn)
			{
				setBackgroundRole(QPalette::NoRole);
				setAttribute(Qt::WA_PaintOnScreen, true);
			}

			void showEvent(QShowEvent* ev) override
			{
				if (inited != true)
				{
					_viewer = _scene.viewer();

					if (_view == nullptr)
					{
						_view = _viewer->create_shared_view(false);
						_view->set_triedron();
						_view->set_gradient(servoce::color(0.5, 0.5, 0.5), servoce::color(0.3, 0.3, 0.3));
					}

					_view->set_window(winId());
					_view->autoscale();

					inited = true;
				}
			}

			void paintEvent(QPaintEvent* ev) override
			{
				_view->redraw();
			}

			void autoscale()
			{
				_view->fit_all(0.05);
			}
		};
	}
}

#endif