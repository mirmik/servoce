#include <servoce/view.h>
#include <servoce/scene.h>

#include <local/OccViewContext.h>
#include <Aspect_DisplayConnection.hxx>
#include <IntCurvesFace_ShapeIntersector.hxx>

#include <mutex>

#include <assert.h>
#include <nos/trace.h>

//servoce::viewer::viewer(servoce::scene& scn) : viewer()
//{
//	occ->set_scene(scn);
//	scn.vwer = this;
//}

servoce::view::~view() 
{
	TRACE();
	delete occ;
}

void servoce::view::set_gradient()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_view->SetBgGradientColors(
	    Quantity_Color(0.5, 0.5, 0.5, Quantity_TOC_RGB),
	    Quantity_Color(0.3, 0.3, 0.3, Quantity_TOC_RGB),
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
void servoce::view::set_triedron()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex); 
	occ->set_triedron();
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
	//occ->m_view->SetEye(p.X(), p.Y(), p.Z());
}

servoce::point3 servoce::view::eye()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	//double x, y, z;
	//occ->m_view->Eye(x, y, z);
	//return servoce::point3( x, y, z );
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
	occ->m_view->Camera()->SetUp(gp_Dir(0, 0, 1));//m_view->SetUp(0, 0, 1);
	//occ->m_view->Camera()->OrthogonalizedUp();
	//occ->m_view->Camera()->SetProjectionType(Graphic3d_Camera::Projection::Projection_Orthographic);
	//return occ->m_view->Camera()->Center();
}

//void servoce::view::screen(const std::string& path)
//{
//set_triedron();

/*set_virtual_window(800, 600);
fit_all();
redraw();
//dump(path);
*/
/*auto display = XOpenDisplay(NULL);

XWindowAttributes gwa;
XGetWindowAttributes(display, occ->winddesc, &gwa);
int width = gwa.width;
int height = gwa.height;

XImage *ximage = XGetImage(display, occ->winddesc,
               0, 0, width, height, AllPlanes, ZPixmap); */

/*Image_PixMap pixmap;
occ->m_view->ToPixMap(
	pixmap,
	800,
	600,
	Graphic3d_BT_RGB,
	Standard_True,
	V3d_SDO_MONO
);


const unsigned char * data = pixmap.Data();

uint w = 800;
uint h = 600;
uint c = 3;*/

//for(int c = 0; c < 3 * 800 * 600; ++c)
//	dprhexln(*(data + c));


//pixmap.Save("a.png");*/

//occ->m_view->Dump("a.png", Graphic3d_BT_BRG);
//}

std::vector<unsigned char> servoce::view::rawarray()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	Image_PixMap pixmap;
	occ->m_view->ToPixMap( pixmap, w, h//,
	                       //Graphic3d_BT_RGB
	                       //Standard_True
	                       //V3d_SDO_MONO
	                     );

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
					fit_all(0.01);

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
#endif




void servoce::see(servoce::scene& scn)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	//auto v = viewer(scn);
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

		//std::cout << ip.X() << ' ' << ip.Y() << ' ' << ip.Z() << std::endl;

		return std::make_pair(servoce::point3(ip), true);
	}
	return std::make_pair(servoce::point3(), false);
}



//servoce::shape_view_controller servoce::viewer::add(const servoce::shape& obj, servoce::color color)
//{

//}

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


/*std::pair<uint16_t, uint16_t> servoce::view::size() 
{

}

void servoce::view::resize(std::pair<uint16_t, uint16_t> sz) 
{

}*/


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