#include <servoce/servoce.h>
#include <mutex>

#include <AIS_Shape.hxx>
#include <local/OccViewContext.h>
#include <BRepBuilderAPI_Copy.hxx>

extern std::recursive_mutex viewrecursive_mutex;

servoce::shape servoce::shape_view::shape() 
{
	return servoce::shape(m_ashp->Shape());
}

servoce::color servoce::shape_view::color() 
{
	return m_color;
}


servoce::shape_view::shape_view(const servoce::shape& a, servoce::color color)
{
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
	m_ashp = new AIS_Shape(*a.m_ashp);
	shp = a.shp;
	scn = a.scn;
	m_color = a.m_color;
}

servoce::shape_view::shape_view(servoce::shape_view&& a)
{
	m_ashp = a.m_ashp;
	a.m_ashp = nullptr;
	shp = a.shp;
	scn = a.scn;
	m_color = a.m_color;
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

#define uassert(e) if (!(e)) { printf("assert: %s\n", #e); exit(-1); }

void servoce::shape_view_controller::set_location(const servoce::transformation& trans) 
{
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	uassert(ctr->m_ashp);
	uassert(ctr->scn);
	uassert(ctr->scn->vwer);
	uassert(ctr->scn->vwer->occ);
	uassert(ctr->scn->vwer->occ->m_context);

	ctr->scn->vwer->occ->m_context->SetLocation(ctr->m_ashp, *trans.trsf);
}

void servoce::shape_view_controller::hide(bool en) 
{
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	if (en)
		ctr->scn->vwer->occ->m_context->Erase(ctr->m_ashp, true);
	else
		ctr->scn->vwer->occ->m_context->Display(ctr->m_ashp, true);
}

std::vector<servoce::shape> servoce::scene::shapes_array() 
{
	std::vector<servoce::shape> arr;
	for (auto& v : shapes) arr.emplace_back(v.shape());
	return arr;	
}

std::vector<servoce::color> servoce::scene::color_array() 
{
	std::vector<servoce::color> arr;
	for (auto& v : shapes) arr.emplace_back(v.color());
	return arr;	
}