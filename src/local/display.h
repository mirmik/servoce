#ifndef SERVOCE_LOCAL_DISPLAY_H
#define SERVOCE_LOCAL_DISPLAY_H

#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMainWindow>

#include <QtOpenGL/QGLWidget>

#include <AIS_InteractiveContext.hxx>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>

#include <gxx/math/quaternion.h>

#include <servoce/scene.h>

namespace servoce {
	namespace disp {
		class DisplayWidget : public QGLWidget {
			Q_OBJECT
		
		public:
			Handle(V3d_Viewer) m_viewer;
			Handle(V3d_View) m_view;
			Handle(AIS_InteractiveContext) m_context;
		
		private:
			QPoint temporary1;
			malgo::quaternion<double> quat_orient;
		
			double phi = - cos(M_PI / 4);
			double psi = 0.61548;
		
		public:
			void init();
			const servoce::scene* scn;
			void setScene(const servoce::scene* scn) { this->scn = scn; }

		protected:
			virtual void showEvent(QShowEvent* e) override;
			virtual void paintEvent(QPaintEvent* e) override;
			virtual void resizeEvent(QResizeEvent* e) override;
		
			virtual void mousePressEvent(QMouseEvent* e) override;
			virtual void mouseReleaseEvent(QMouseEvent* e) override;
			virtual void mouseMoveEvent(QMouseEvent * e) override;
			virtual void wheelEvent(QWheelEvent * e) override;
		
			virtual void onLButtonDown(const int theFlags, const QPoint thePoint);
			virtual void onMButtonDown(const int theFlags, const QPoint thePoint);
			virtual void onRButtonDown(const int theFlags, const QPoint thePoint);
			virtual void onMouseWheel(const int theFlags, const int theDelta, const QPoint thePoint);
			virtual void onLButtonUp(const int theFlags, const QPoint thePoint);
			virtual void onMButtonUp(const int theFlags, const QPoint thePoint);
			virtual void onRButtonUp(const int theFlags, const QPoint thePoint);
			virtual void onMouseMove(const int theFlags, const QPoint thePoint);
		
		public:
			DisplayWidget(QWidget* parent = nullptr) : QGLWidget(parent) {
				setBackgroundRole( QPalette::NoRole );
			}
		
		public:
			const Handle_AIS_InteractiveContext& getContext() const;
		
		public slots:
			void autoscale();
		};

		class MainWidget : public QMainWindow {
			Q_OBJECT
		
			QAction* mStlExport;
			QAction* mExitAction;
			QAction* mScreen;
			QAction* mAboutAction;
			QAction* mAutoscale;
		
			QMenu* mFileMenu;
			QMenu* mNavigationMenu;
			QMenu* mHelpMenu;
			
		public:
			DisplayWidget* display;
		
		private:
			void createActions();
			void createMenus();
			void createToolbars();
		
		private slots:
			void about(void);
			void export_stl();
			void screenshot();
		
		public:
			MainWidget(QWidget* parent = nullptr);		
		};
	}	
}

#endif