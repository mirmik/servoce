#include <servoce/shape_view.h>
#include <AIS_InteractiveContext.hxx>

servoce::color servoce::interactive_object::color() const
{
	Quantity_Color clr;
	m_ais->Color(clr);
	return clr;
}

void servoce::interactive_object::set_color(const servoce::color& clr)
{
	m_ais->SetColor(clr.Color());
}

void servoce::interactive_object::set_location(const servoce::transformation& trans)
{
	if (m_context)
		m_context->SetLocation(native(), *trans.trsf);
}

void servoce::interactive_object::hide(bool en)
{

	if (m_context)
	{
		if (en)
			m_context->Erase(m_ais, true);
		else
			m_context->Display(m_ais, true);
	}
}