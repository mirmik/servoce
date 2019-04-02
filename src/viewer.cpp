#include <servoce/viewer.h>
#include <servoce/scene.h>

#include <mutex>
#include <nos/print.h>
#include <nos/trace.h>

#include <local/OccViewContext.h>

//Global resource for viewer, view, scene, shape_view, OccViewContext
std::recursive_mutex viewrecursive_mutex;
Handle(Aspect_DisplayConnection) g_displayConnection;
Handle(Graphic3d_GraphicDriver) g_graphicDriver;

servoce::viewer::viewer()
{
	TRACE();
	occ = new OccViewerContext();
}


servoce::viewer::~viewer()
{
	TRACE();
}

void servoce::viewer::set_triedron_axes()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
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
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	return servoce::view( occ->create_view_window() );
}

void servoce::viewer::redraw()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_viewer->Redraw();
}

void servoce::viewer::close()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	return occ->m_viewer->Remove();
}

void servoce::viewer::clean_context()
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_context->EraseAll(false);
	//occ->m_context->RemoveAll(true);
}

void servoce::viewer::add_scene(servoce::scene& scn)
{
	TRACE();
	//scn.set_viewer(this);
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	for (auto& s : scn.shape_views)
	{
		occ->m_context->Display(s->native(), false);
	}
}

void servoce::viewer::display(servoce::shape_view& controller)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_context->Display(controller.native(), false);
}
