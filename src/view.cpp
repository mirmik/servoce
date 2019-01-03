#include <servoce/view.h>
#include <local/OccViewContext.h>
#include <Aspect_DisplayConnection.hxx>
//#include <Standart_Real.hxx>

//#include <gxx/debug/dprint.h>
//#include <nos/print.h>

#include <IntCurvesFace_ShapeIntersector.hxx>


Handle(Aspect_DisplayConnection) g_displayConnection;
Handle(Graphic3d_GraphicDriver) g_graphicDriver;

servoce::viewer::viewer()
{
	occ = new OccViewerContext();
}

servoce::viewer::viewer(servoce::scene& scn) : viewer()
{
	occ->set_scene(scn);
	scn.vwer = this;
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


void servoce::viewer::redraw()
{
	return occ->m_viewer->Redraw();
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
void servoce::view::set_virtual_window(int w, int h) 
{ 
	this->w = w;
	this->h = h;
	occ->set_virtual_window(w, h); 
}
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
	this->w = w;
	this->h = h;
	return rawarray();
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




void servoce::see(servoce::scene& scn)
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

void servoce::view::centering() {
	occ->m_view->Camera()->SetCenter(gp_Pnt(0,0,0));
	occ->m_view->ResetViewOrientation();
}

void servoce::view::start_rotation(int x, int y, float treshold) {
	occ->m_view->StartRotation(x, y, treshold);
}

void servoce::view::rotation(int x, int y) {
	occ->m_view->Rotation(x, y);
}

std::pair<servoce::point3, bool> servoce::view::intersect_point( double x, double y ) 
{
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

        if (shapeIntersector.NbPnt() >= 1) {    
            ip = shapeIntersector.Pnt(shapeIntersector.NbPnt());
        } else
            continue;

        //std::cout << ip.X() << ' ' << ip.Y() << ' ' << ip.Z() << std::endl;

        return std::make_pair(servoce::point3(ip), true);
    }
    return std::make_pair(servoce::point3(), false);
}

servoce::shape_view_controller servoce::viewer::add(const servoce::shape& obj, servoce::color color) 
{

}