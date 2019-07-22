#include <servoce/view.h>
#include <servoce/scene.h>

#include <local/OccViewContext.h>
#include <Aspect_DisplayConnection.hxx>
#include <IntCurvesFace_ShapeIntersector.hxx>

#include <mutex>

#include <assert.h>
#include <nos/trace.h>

servoce::view::view(OccViewWindow* occ) : occ(occ) 
{
	set_gradient(servoce::color(0.5,0.5,0.5), servoce::color(0.3,0.3,0.3));
	set_triedron();
}

void servoce::view::set_background(const servoce::color& clr)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);

	//occ->m_view->SetBackgroundColor(
	//    Quantity_Color(clr.r, clr.g, clr.b, Quantity_TOC_RGB)
	//);

	occ->m_view->SetBgGradientColors(
	    Quantity_Color(clr.r, clr.g, clr.b, Quantity_TOC_RGB),
	    Quantity_Color(clr.r, clr.g, clr.b, Quantity_TOC_RGB),
	    Aspect_GFM_VER,
	    Standard_True
	);
}

void servoce::view::set_gradient(const servoce::color& clr1, const servoce::color& clr2)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_view->SetBgGradientColors(
	    Quantity_Color(clr1.r, clr1.g, clr1.b, Quantity_TOC_RGB),
	    Quantity_Color(clr2.r, clr2.g, clr2.b, Quantity_TOC_RGB),
	    Aspect_GFM_VER,
	    Standard_True
	);
}

void servoce::view::redraw()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_view->Redraw();
}

void servoce::view::redraw_immediate()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_view->RedrawImmediate();
}

void servoce::view::must_be_resized()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex); 
	occ->m_view->MustBeResized();
}
void servoce::view::set_triedron(bool en)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex); 
	occ->set_triedron(en);
}
void servoce::view::dump(const std::string& path)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex); 
	occ->dump(path);
}
void servoce::view::fit_all(double koeff)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex); 
	occ->m_view->FitAll(koeff);
}
void servoce::view::set_virtual_window(int w, int h)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	this->w = w;
	this->h = h;
	occ->set_virtual_window(w, h);
}
void servoce::view::set_window(int n) { 
	TRACE();
	assert(occ);
	occ->set_window(n); 
}

void servoce::view::set_direction(float a, float b, float c)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_view->Camera()->SetDirection(gp_Dir(a, b, c));
}

std::tuple<double, double, double> servoce::view::direction()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	auto dir = occ->m_view->Camera()->Direction();
	return std::make_tuple(dir.X(), dir.Y(), dir.Z());
}

void servoce::view::pan(float a, float b)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_view->Pan(a, b);
}

void servoce::view::zoom(float a, float b, float aa, float ba)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_view->Zoom(a, b, aa, ba);
}

void servoce::view::set_eye(servoce::point3 pnt)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_view->Camera()->SetEye(pnt.Pnt());
}

servoce::point3 servoce::view::eye()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	return occ->m_view->Camera()->Eye();
}

void servoce::view::set_center(servoce::point3 pnt)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_view->Camera()->SetCenter(pnt.Pnt());
}

servoce::point3 servoce::view::center()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	return occ->m_view->Camera()->Center();
}

void servoce::view::set_orthogonal()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_view->Camera()->SetUp(gp_Dir(0, 0, 1));
}

servoce::view::~view() 
{
	TRACE();
	delete occ;
}

std::vector<unsigned char> servoce::view::rawarray()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	Image_PixMap pixmap;
	occ->m_view->ToPixMap( pixmap, w, h);

	return std::vector<unsigned char>(pixmap.Data(), pixmap.Data() + 3 * w * h);
}

std::vector<unsigned char> servoce::view::rawarray(int w, int h)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	this->w = w;
	this->h = h;
	return rawarray();
}


#if defined(WNT) || defined(_MSC_VER)
void servoce::view::see(int width, int height) { BUG(); }
#elif defined(__APPLE__) && !defined(MACOSX_USE_GLX)
void servoce::view::see(int width, int height) { BUG(); }
#else
void servoce::view::see(int width, int height)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
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
				static bool inited = false;

				if (!inited)
				{
					set_window(w);
					set_triedron();
					fit_all(0.01);

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
#endif




void servoce::see(servoce::scene& scn)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	auto vv = scn.viewer().create_view();
	vv.see();
}

void servoce::view::reset_orientation()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_view->ResetViewOrientation();
}

void servoce::view::autoscale()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_view->FitAll(0.7);
}

void servoce::view::centering()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_view->Camera()->SetCenter(gp_Pnt(0, 0, 0));
	occ->m_view->ResetViewOrientation();
}

void servoce::view::start_rotation(int x, int y, float treshold)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_view->StartRotation(x, y, treshold);
}

void servoce::view::rotation(int x, int y)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_view->Rotation(x, y);
}

std::pair<servoce::point3, bool> servoce::view::intersect_point( double x, double y )
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	auto m_view = occ->m_view;
	auto m_context = occ->parent->m_context;

	auto selector = m_context->MainSelector();
	selector->Pick(x, y, m_view);

	const Standard_Integer aDetectedNb = selector->NbPicked();

	auto viewLine = occ->viewline(x, y, m_view);

	for (Standard_Integer aDetIter = 1; aDetIter <= aDetectedNb; ++aDetIter)
	{
		Handle(SelectMgr_EntityOwner) anOwner = selector->Picked(aDetIter);

		Handle(AIS_InteractiveObject) anObj
		    = Handle(AIS_InteractiveObject)::DownCast (anOwner->Selectable());

		if (anObj->Type() != AIS_KOI_Shape)
			continue;

		Handle_AIS_Shape hShape = Handle_AIS_Shape::DownCast(anObj);
		const TopoDS_Shape &shape = hShape->Shape();

		gp_Pnt ip;

		TopLoc_Location loc = m_context->Location(hShape);
		TopoDS_Shape loc_shape = shape.Located(loc);

		IntCurvesFace_ShapeIntersector shapeIntersector;
		shapeIntersector.Load(loc_shape, Precision::Confusion());
		shapeIntersector.Perform(viewLine, -RealLast(), RealLast());

		if (shapeIntersector.NbPnt() >= 1)
		{
			ip = shapeIntersector.Pnt(shapeIntersector.NbPnt());
		}
		else
			continue;

		return std::make_pair(servoce::point3(ip), true);
	}
	return std::make_pair(servoce::point3(), false);
}

double servoce::view::scale()
{
	TRACE();
	return occ->m_view->Scale();
}

void servoce::view::set_scale(double arg)
{
	TRACE();
	occ->m_view->SetScale(arg);
}

std::pair<uint16_t, uint16_t> servoce::view::size() 
{
	TRACE();
	double w, h;
	occ->m_view->Size(w, h);
	return {w, h};
}

void servoce::view::destroy() 
{
	TRACE();
	occ->m_view->Remove();
}