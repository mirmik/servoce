#include <servoce/shape_view.h>
#include <servoce/scene.h>

#include <local/OccViewContext.h>
#include <BRepBuilderAPI_Copy.hxx>

#include <mutex>
#include <nos/trace.h>

servoce::shape servoce::shape_view::shape() const
{
	TRACE();
	return servoce::shape(native()->Shape());
}

servoce::color servoce::shape_view::color() const
{
	TRACE();
	return m_color;
}

servoce::shape_view::shape_view(const servoce::shape& a, 
	servoce::color color, servoce::scene* scn) : scn(scn)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	BRepBuilderAPI_Copy copier(a.Shape());
	TopoDS_Shape newShape = copier.Shape();

	shp = newShape;
	m_ashp = new AIS_Shape(shp.Shape());
	m_color = color;
	Quantity_Color shpcolor (color.r, color.g, color.b,  Quantity_TOC_RGB);
	m_ashp->SetColor(shpcolor);
	if (color.a != 0.0) m_ashp->SetTransparency(color.a);
	m_ashp->SetMaterial(Graphic3d_NOM_STEEL);
}

servoce::shape_view::shape_view(const servoce::shape_view& a)
{
	TRACE();
	m_ashp = new AIS_Shape(*a.m_ashp);
	shp = a.shp;
	scn = a.scn;
	m_color = a.m_color;
}

servoce::shape_view::shape_view(servoce::shape_view&& a)
{
	TRACE();
	m_ashp = a.m_ashp;
	a.m_ashp = nullptr;
	shp = a.shp;
	scn = a.scn;
	m_color = a.m_color;
}

servoce::shape_view& servoce::shape_view::operator= (const servoce::shape_view& oth)
{
	TRACE();
	if (m_ashp != oth.m_ashp)
	{
		delete m_ashp;
		m_ashp = new AIS_Shape(*oth.m_ashp);
	}

	return *this;
}

servoce::shape_view& servoce::shape_view::operator= (servoce::shape_view&& oth)
{
	TRACE();
	delete m_ashp;
	m_ashp = oth.m_ashp;
	m_ashp = nullptr;
	return *this;
}

void servoce::shape_view::set_location(const servoce::transformation& trans)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	this->scene().viewer()->occ->m_context->SetLocation(native(), *trans.trsf);
}

void servoce::shape_view::hide(bool en)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	if (en)
		this->scene().viewer()->occ->m_context->Erase(native(), false);
	else
		this->scene().viewer()->occ->m_context->Display(native(), false);
}

void servoce::shape_view::set_color(const servoce::color& clr)
{
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	native()->SetColor(clr.Color());
	native()->SetTransparency(clr.a);
}

void servoce::shape_view::set_color(float r, float g, float b, float a)
{
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	native()->SetColor(Quantity_Color(r,g,b, Quantity_TOC_RGB));
	native()->SetTransparency(a);
}