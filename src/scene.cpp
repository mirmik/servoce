#include <servoce/servoce.h>

#include <AIS_Shape.hxx>
#include <local/OccViewContext.h>

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

#define uassert(e) if (!(e)) { printf("assert: %s", #e); exit(-1); }

void servoce::shape_view_controller::set_location(double x, double y, double z) 
{
	printf("set_location\n");
	fflush(stdout);

	uassert(ctr);
	uassert(ctr->m_ashp);
	uassert(ctr->scn);
	uassert(ctr->scn->vwer);
	uassert(ctr->scn->vwer->occ);
	uassert(ctr->scn->vwer->occ->m_context);

	auto trf = gp_Trsf();
	trf.SetTranslation(gp_Vec(x,y,z));

	printf("set_location\n");
	fflush(stdout);

	ctr->scn->vwer->occ->m_context->SetLocation(ctr->m_ashp, trf);

	printf("set_location\n");
	fflush(stdout);

	ctr->scn->vwer->occ->m_viewer->Redraw();

	printf("set_location\n");
	fflush(stdout);
}