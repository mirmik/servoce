#ifndef SERVOCE_OCCVIEWCONTEXT_H
#define SERVOCE_OCCVIEWCONTEXT_H

#include <OpenGl_GraphicDriver.hxx>
#undef Bool
#undef CursorShape
#undef None
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef Expose

#include <V3d_View.hxx>
#include <V3d_AmbientLight.hxx>
#include <V3d_DirectionalLight.hxx>

#include <Aspect_Handle.hxx>
#include <Aspect_DisplayConnection.hxx>

#ifdef WNT
  #include <WNT_Window.hxx>
#elif defined(__APPLE__) && !defined(MACOSX_USE_GLX)
  #include <Cocoa_Window.hxx>
#else
  #include <Xw_Window.hxx>
#endif
#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <AIS_Axis.hxx>
#include <Geom_Axis1Placement.hxx>


//debug
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>

#include <X11/Xlib.h>

class OccViewContext {
    Handle(Aspect_DisplayConnection) m_displayConnection;	
	Handle(Graphic3d_GraphicDriver) m_graphicDriver;

    Handle(AIS_InteractiveContext) m_context;
    Handle(V3d_Viewer) m_viewer;
	Handle(V3d_View) m_view;

	Handle(Xw_Window) m_window;

public:
	void init() {
    	m_displayConnection = new Aspect_DisplayConnection();
		m_graphicDriver = new OpenGl_GraphicDriver(m_displayConnection);
		m_viewer = new V3d_Viewer(m_graphicDriver);
		m_context = new AIS_InteractiveContext (m_viewer);  
		m_view = m_viewer->CreateView();

    	m_viewer->SetLightOn(new V3d_DirectionalLight (m_viewer, V3d_Zneg , Quantity_NOC_WHITE, true));
    	m_context->SetDisplayMode(AIS_Shaded, false);
    	m_context->DefaultDrawer ()->SetFaceBoundaryDraw(true);
	}

	/*auto& displayConnection() {
		return m_displayConnection;
	}*/

	void set_scene(const servoce::scene& scn) {
		for (auto& shp : scn.shapes) {			
			m_context->Display (shp.m_ashp, false);
		}
	}

	void set_triedron() {
		m_view->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_GOLD, 0.08, V3d_ZBUFFER);

        Handle(AIS_Axis) axX = new AIS_Axis(new Geom_Axis1Placement(gp_Pnt(0,0,0), gp_Vec(1,0,0)));
        Handle(AIS_Axis) axY = new AIS_Axis(new Geom_Axis1Placement(gp_Pnt(0,0,0), gp_Vec(0,1,0)));
        Handle(AIS_Axis) axZ = new AIS_Axis(new Geom_Axis1Placement(gp_Pnt(0,0,0), gp_Vec(0,0,1)));

        axX->SetColor(Quantity_NOC_RED);
        axY->SetColor(Quantity_NOC_GREEN);
        axZ->SetColor(Quantity_NOC_BLUE1);

        m_context->Display(axX, false);
        m_context->Display(axY, false);
        m_context->Display(axZ, false);
	}

	void set_virtual_window(int w, int h) {
		m_window = new Xw_Window (m_displayConnection, "virtual", 0, 0, w, h);
		m_window->SetVirtual  (Standard_True); 
		m_view->SetWindow  (m_window); 
	}

	void set_window(int wind) {
		m_window = new Xw_Window(m_displayConnection, wind);
		m_view->SetWindow(m_window);
	}

	void fit_all() {
		m_view->FitAll();
	}

	void dump(const std::string& path) {
		m_view->Dump(path.c_str()); 
	}

	void redraw() {
		m_view->Redraw();
	}
};

#endif