#include <servoce/view.h>

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

void servoce::viewer::screen(const std::string& path) {
    Handle(V3d_Viewer) m_viewer;
    Handle(AIS_InteractiveContext) m_context;
    Handle(Aspect_DisplayConnection) m_displayConnection;	
	Handle(Graphic3d_GraphicDriver) m_graphicDriver;
	Handle(Xw_Window) m_window;
	Handle(V3d_View) m_view;

    m_displayConnection = new Aspect_DisplayConnection();
	m_graphicDriver = new OpenGl_GraphicDriver(m_displayConnection);
	m_viewer = new V3d_Viewer(m_graphicDriver, (Standard_ExtString)"viewer");
	m_context = new AIS_InteractiveContext (m_viewer);  
	m_window = new Xw_Window (m_displayConnection, "virtual", 0, 0, 800, 800);
	m_view = m_viewer->CreateView();

	m_window->SetVirtual  (Standard_True); 
	m_view->SetWindow  (m_window); 

    m_viewer->SetLightOn(new V3d_DirectionalLight (m_viewer, V3d_Zneg , Quantity_NOC_WHITE, true));
    m_context->SetDisplayMode(AIS_Shaded, false);
	
	for (auto& shp : scn->shapes) {
		Handle (AIS_Shape) ais = new AIS_Shape(shp.shp.Shape());
		Handle (AIS_Shape) ais2 = new AIS_Shape(shp.shp.Shape()); 
		Quantity_Color shpcolor (shp.clr.r, shp.clr.g, shp.clr.b,  Quantity_TOC_RGB);  
        ais->SetColor(shpcolor);
		m_context->Display (ais);

        ais2->SetColor(Quantity_NOC_BLACK);
        ais2->SetDisplayMode(AIS_WireFrame);  
       	m_context->Display(ais2, false);
	}

	if (trg) {
    	m_view->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_GOLD, 0.08, V3d_ZBUFFER);

        auto axX = new AIS_Axis(new Geom_Axis1Placement(gp_Pnt(0,0,0), gp_Vec(1,0,0)));
        auto axY = new AIS_Axis(new Geom_Axis1Placement(gp_Pnt(0,0,0), gp_Vec(0,1,0)));
        auto axZ = new AIS_Axis(new Geom_Axis1Placement(gp_Pnt(0,0,0), gp_Vec(0,0,1)));

        axX->SetColor(Quantity_NOC_RED);
        axY->SetColor(Quantity_NOC_GREEN);
        axZ->SetColor(Quantity_NOC_BLUE1);

        m_context->Display(axX);
        m_context->Display(axY);
        m_context->Display(axZ);
	}

	m_view->FitAll();
	m_view->Dump(path.c_str()); 
}

void servoce::viewer::see() {
	int s;
	Display *d;
	Window w;

	XEvent e;
	//update_window(width, height);

	//Соединиться с X сервером, если X сервер на удаленной машине
	//следует разрешить на машине, где запущен X Server 
	//удаленные соединения командой xhost+ (см. man xhost)
	
	if ((d = XOpenDisplay(getenv("DISPLAY"))) == NULL) {
		printf("Can't connect X server:%s\n", strerror(errno));
		exit(1);
	}

	s = XDefaultScreen(d);

	/* Создать окно */
	w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1, 0xffffff, 0xffffff);

	/* На какие события будем реагировать */
	XSelectInput(d, w, KeyPressMask | StructureNotifyMask);

	//Вывести окно на экран
	XMapWindow(d, w);

	Handle(V3d_Viewer) m_viewer;
    Handle(AIS_InteractiveContext) m_context;
    Handle(Aspect_DisplayConnection) m_displayConnection;	
	Handle(Graphic3d_GraphicDriver) m_graphicDriver;
	Handle(Xw_Window) m_window;
	Handle(V3d_View) m_view;

    m_displayConnection = new Aspect_DisplayConnection();
	m_graphicDriver = new OpenGl_GraphicDriver(m_displayConnection);
	m_viewer = new V3d_Viewer(m_graphicDriver, (Standard_ExtString)"viewer");
	m_context = new AIS_InteractiveContext (m_viewer);  
	m_view = m_viewer->CreateView();

	for (auto& shp : scn->shapes) {
		Handle (AIS_Shape) ais = new AIS_Shape(shp.shp.Shape());
		Handle (AIS_Shape) ais2 = new AIS_Shape(shp.shp.Shape()); 
		Quantity_Color shpcolor (shp.clr.r, shp.clr.g, shp.clr.b,  Quantity_TOC_RGB);  
        ais->SetColor(shpcolor);
		m_context->Display (ais);
	
        ais2->SetColor(Quantity_NOC_BLACK);
        ais2->SetDisplayMode(AIS_WireFrame);  
       	m_context->Display(ais2, false);
	}
	
	if (trg) {
	
        auto axX = new AIS_Axis(new Geom_Axis1Placement(gp_Pnt(0,0,0), gp_Vec(1,0,0)));
        auto axY = new AIS_Axis(new Geom_Axis1Placement(gp_Pnt(0,0,0), gp_Vec(0,1,0)));
        auto axZ = new AIS_Axis(new Geom_Axis1Placement(gp_Pnt(0,0,0), gp_Vec(0,0,1)));
	
        axX->SetColor(Quantity_NOC_RED);
        axY->SetColor(Quantity_NOC_GREEN);
        axZ->SetColor(Quantity_NOC_BLUE1);
	
        m_context->Display(axX);
        m_context->Display(axY);
        m_context->Display(axZ);
	}

   	m_viewer->SetLightOn(new V3d_DirectionalLight (m_viewer, V3d_Zneg , Quantity_NOC_WHITE, true));
    m_context->SetDisplayMode(AIS_Shaded, false);

	Atom wmDeleteMessage = XInternAtom(d, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(d, w, &wmDeleteMessage, 1);

	//Бесконечный цикл обработки событий
	bool running = true;
	while (running) {
		XNextEvent(d, &e);

		switch (e.type)
    	{
    		case ConfigureNotify: {
				XConfigureEvent xce = e.xconfigure;
				static bool inited = false;
				if (!inited) {
					Handle(Xw_Window) wind = new Xw_Window(m_displayConnection, w);
					m_view->SetWindow(wind);
    				m_view->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_GOLD, 0.08, V3d_ZBUFFER);

					auto m_cam = m_view->Camera();
					m_cam->SetDirection(cam->native_dir());
					m_cam->SetUp(cam->native_up());
					m_cam->SetEye(cam->native_eye());
					//m_cam->SetScale(cam->native_scale());
	
					inited = true;
    			}
    			m_view->Redraw();
			}
			break;
	
    	    case ClientMessage:
    	        if (e.xclient.data.l[0] == wmDeleteMessage)
    	            running = false;
    	        break;
	
    	    default:
    	        break;
    	}
	}

	//Закрыть соединение с X сервером
	XCloseDisplay(d);

	return;
}