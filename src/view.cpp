#include <servoce/view.h>
#include <local/OccViewContext.h>

servoce::viewer::viewer()
{
	occ = new OccViewerContext();
}

servoce::viewer::viewer(const servoce::scene& scn) : viewer()
{
	occ->set_scene(scn);
}

servoce::view servoce::viewer::create_view()
{
	return servoce::view( occ->create_view_window() );
}

void servoce::view::redraw() { occ->redraw(); }
void servoce::view::must_be_resized() { occ->must_be_resized(); }
void servoce::view::set_triedron() { occ->set_triedron(); }
void servoce::view::dump(const std::string& path) { occ->dump(path); }
void servoce::view::fit_all() { occ->fit_all(); }
void servoce::view::set_virtual_window(int w, int h) { occ->set_virtual_window(w, h); }
void servoce::view::set_window(int n) { occ->set_window(n); }

void servoce::view::screen(const std::string& path)
{
	set_virtual_window(800, 600);
	set_triedron();
	fit_all();
	dump(path);
}

void servoce::view::see(int width, int height)
{
	int s;
	Display *d;
	Window w;
	XEvent e;

	if ((d = XOpenDisplay(getenv("DISPLAY"))) == NULL)
	{
		printf("Can't connect X server:%s\n", strerror(errno));
		exit(1);
	}

	s = XDefaultScreen(d);
	w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1, 0xffffff, 0xffffff);
	XSelectInput(d, w, KeyPressMask | StructureNotifyMask);
	XMapWindow(d, w);

	/*OccViewerContext oc;
	auto vw = oc.create_vw();

	oc.set_scene(*scn);
	oc.set_triedron_axes();
	*/
	Atom wmDeleteMessage = XInternAtom(d, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(d, w, &wmDeleteMessage, 1);

	bool running = true;

	while (running)
	{
		XNextEvent(d, &e);

		switch (e.type)
		{
		case ConfigureNotify:
		{
			//XConfigureEvent xce = e.xconfigure;
			static bool inited = false;

			if (!inited)
			{
				set_window(w);
				set_triedron();
				fit_all();

				/*auto m_cam = m_view->Camera();
				m_cam->SetDirection(cam->native_dir());
				m_cam->SetUp(cam->native_up());
				m_cam->SetEye(cam->native_eye());*/
				//m_cam->SetScale(cam->native_scale());

				inited = true;
			}

			redraw();
		}
		break;

		case ClientMessage:
			if (e.xclient.data.l[0] == (signed)wmDeleteMessage)
				running = false;

			break;

		default:
			break;
		}
	}

	XCloseDisplay(d);

	return;
}


servoce::shape_view::shape_view(const servoce::shape& a, servoce::color color)
{
	m_ashp = new AIS_Shape(a.Shape());
	Quantity_Color shpcolor (color.r, color.g, color.b,  Quantity_TOC_RGB);
	m_ashp->SetColor(shpcolor);
	m_ashp->SetMaterial(Graphic3d_NOM_STEEL);
}

servoce::shape_view::shape_view(const servoce::shape_view& a)
{
	m_ashp = new AIS_Shape(*a.m_ashp);
}

servoce::shape_view::shape_view(servoce::shape_view&& a)
{
	m_ashp = a.m_ashp;
	a.m_ashp = nullptr;
}

servoce::shape_view& servoce::shape_view::operator= (const servoce::shape_view& oth)
{
	if (m_ashp != oth.m_ashp)
	{
		delete m_ashp;
		m_ashp = new AIS_Shape(*oth.m_ashp);
	}

	return *this;
}

servoce::shape_view& servoce::shape_view::operator= (servoce::shape_view&& oth)
{
	delete m_ashp;
	m_ashp = oth.m_ashp;
	m_ashp = nullptr;
	return *this;
}


void servoce::see(const servoce::scene& scn)
{
	auto v = viewer(scn);
	auto vv = v.create_view();
	vv.see();
}