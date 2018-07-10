#include <servoce/view.h>
#include <local/OccViewContext.h>

void servoce::viewer::screen(const std::string& path) {
	OccViewContext oc;

	oc.init();
	oc.set_virtual_window(800,600);
	oc.set_scene(*scn);
	oc.set_triedron();
	oc.fit_all();
	oc.dump(path);
}

void servoce::viewer::see() {
	int s;
	Display *d;
	Window w;
	XEvent e;
	
	if ((d = XOpenDisplay(getenv("DISPLAY"))) == NULL) {
		printf("Can't connect X server:%s\n", strerror(errno));
		exit(1);
	}

	s = XDefaultScreen(d);
	w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1, 0xffffff, 0xffffff);
	XSelectInput(d, w, KeyPressMask | StructureNotifyMask);
	XMapWindow(d, w);

	OccViewContext oc;

	oc.init();
	oc.set_scene(*scn);

	Atom wmDeleteMessage = XInternAtom(d, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(d, w, &wmDeleteMessage, 1);

	bool running = true;
	while (running) {
		XNextEvent(d, &e);

		switch (e.type)
    	{
    		case ConfigureNotify: {
				XConfigureEvent xce = e.xconfigure;
				static bool inited = false;
				if (!inited) {
					oc.set_window(w);
					oc.set_triedron();
					oc.fit_all();

					/*auto m_cam = m_view->Camera();
					m_cam->SetDirection(cam->native_dir());
					m_cam->SetUp(cam->native_up());
					m_cam->SetEye(cam->native_eye());*/
					//m_cam->SetScale(cam->native_scale());
	
					inited = true;
    			}
    			oc.redraw();
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

	XCloseDisplay(d);

	return;
}