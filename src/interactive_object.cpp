#include <servoce/interactive_object.h>
#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>

#include <mutex>

extern std::recursive_mutex viewrecursive_mutex;

servoce::color servoce::interactive_object::color() const
{
	Quantity_Color clr;
	m_ais->Color(clr);
	return clr;
}

void servoce::interactive_object::set_color(const servoce::color& clr)
{
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	m_ais->SetColor(clr.Color());
	m_ais->SetTransparency(clr.a);
}

void servoce::interactive_object::set_color(float r, float g, float b, float a)
{
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	m_ais->SetColor(Quantity_Color(r,g,b, Quantity_TOC_RGB));
	m_ais->SetTransparency(a);
}

void servoce::interactive_object::set_location(const servoce::transformation& trans)
{
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	if (m_context)
		m_context->SetLocation(native(), *trans.trsf);
}

void servoce::interactive_object::hide(bool en)
{
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	if (m_context)
	{
		if (en)
			m_context->Erase(m_ais, false);
		else
			m_context->Display(m_ais, false);
	}
}

servoce::interactive_object::interactive_object(const servoce::shape& shp) :
	interactive_object(new AIS_Shape(shp.Shape()))	
{}

servoce::interactive_object::interactive_object(const servoce::shape& shp, const servoce::color& clr) :
	interactive_object(shp)	
{
	set_color(clr);
}

servoce::boundbox servoce::interactive_object::bounding_box() 
{
	Bnd_Box box;
	m_ais->BoundingBox(box);
	return {box};
}