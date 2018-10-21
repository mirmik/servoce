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

void servoce::viewer::set_triedron_axes()
{
	Handle(AIS_Axis) axX = new AIS_Axis(new Geom_Axis1Placement(gp_Pnt(0, 0, 0), gp_Vec(1, 0, 0)));
	Handle(AIS_Axis) axY = new AIS_Axis(new Geom_Axis1Placement(gp_Pnt(0, 0, 0), gp_Vec(0, 1, 0)));
	Handle(AIS_Axis) axZ = new AIS_Axis(new Geom_Axis1Placement(gp_Pnt(0, 0, 0), gp_Vec(0, 0, 1)));

	axX->SetColor(Quantity_NOC_RED);
	axY->SetColor(Quantity_NOC_GREEN);
	axZ->SetColor(Quantity_NOC_BLUE1);

	occ->m_context->Display(axX, false);
	occ->m_context->Display(axY, false);
	occ->m_context->Display(axZ, false);
}

servoce::view servoce::viewer::create_view()
{
	return servoce::view( occ->create_view_window() );
}

void servoce::view::set_gradient()
{
	occ->m_view->SetBgGradientColors(
	    Quantity_Color(0.5, 0.5, 0.5, Quantity_TOC_RGB),
	    Quantity_Color(0.3, 0.3, 0.3, Quantity_TOC_RGB),
	    Aspect_GFM_VER,
	    Standard_True
	);
	//if (!occ->m_window->IsMapped()) 
	//	occ->m_window->Map();
}

void servoce::view::redraw() { occ->redraw(); }
void servoce::view::must_be_resized() { occ->must_be_resized(); }
void servoce::view::set_triedron() { occ->set_triedron(); }
void servoce::view::dump(const std::string& path) { occ->dump(path); }
void servoce::view::fit_all() { occ->fit_all(); }
void servoce::view::set_virtual_window(int w, int h) { occ->set_virtual_window(w, h); }
void servoce::view::set_window(int n) { occ->set_window(n); }

void servoce::view::set_projection(float a, float b, float c)
{
	occ->m_view->SetProj(a, b, c);
}

void servoce::view::pan(float a, float b)
{
	occ->m_view->Pan(a, b);
}

void servoce::view::zoom(float a, float b, float aa, float ba)
{
	occ->m_view->Zoom(a, b, aa, ba);
}

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

void servoce::view::reset_orientation() {
	occ->m_view->ResetViewOrientation();
}

void servoce::view::autoscale() {
	occ->m_view->FitAll();
}

void servoce::view::start_rotation(int x, int y, float treshold) {
	occ->m_view->StartRotation(x, y, treshold);
}

void servoce::view::rotation(int x, int y) {
	occ->m_view->Rotation(x, y);
}