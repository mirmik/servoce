#include <servoce/viewer.h>
#include <servoce/scene.h>

#include <mutex>

#include <local/OccViewContext.h>

//Global resource for viewer, view, scene, shape_view, OccViewContext
std::recursive_mutex viewrecursive_mutex;
Handle(Aspect_DisplayConnection) g_displayConnection = nullptr;
Handle(Graphic3d_GraphicDriver) g_graphicDriver = nullptr;

servoce::viewer::viewer()
{
#if !defined(_MSC_VER) 
	if (getenv("DISPLAY")==NULL) 
	{
		throw std::runtime_error("DISPLAY missing");
	}
#endif
}


servoce::viewer::~viewer()
{}

void servoce::viewer::set_triedron_axes(bool en)
{
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);

	if (en)
	{
		occ->m_context->Display(occ->axX, false);
		occ->m_context->Display(occ->axY, false);
		occ->m_context->Display(occ->axZ, false);
	}

	else 
	{
		occ->m_context->Erase(occ->axX, false);
		occ->m_context->Erase(occ->axY, false);
		occ->m_context->Erase(occ->axZ, false);
	}
}

servoce::view servoce::viewer::create_view()
{
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	return servoce::view( occ->create_view_window() );
}

void servoce::viewer::redraw()
{
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_viewer->Redraw();
}

void servoce::viewer::close()
{
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	return occ->m_viewer->Remove();
}

void servoce::viewer::clean_context()
{
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_context->EraseAll(false);
	//occ->m_context->RemoveAll(true);
}

/*void servoce::viewer::add_scene(servoce::scene& scn)
{
	//scn.set_viewer(this);
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);

	for (auto& s : scn.shape_views)
	{
		occ->m_context->Display(s->native(), false);
	}
}*/
/*
void servoce::viewer::display(servoce::shape_view& controller)
{
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	occ->m_context->Display(controller.native(), false);
}*/

void servoce::viewer::display(servoce::interactive_object& controller)
{
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	controller.set_context(occ->m_context);
	occ->m_context->Display(controller.native(), false);
}