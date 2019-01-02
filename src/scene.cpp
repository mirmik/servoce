#include <servoce/servoce.h>

#include <AIS_Shape.hxx>
#include <local/OccViewContext.h>
#include <BRepBuilderAPI_Copy.hxx>

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
	BRepBuilderAPI_Copy copier(a.Shape());
	TopoDS_Shape newShape = copier.Shape();
	
	shp = newShape;
	m_ashp = new AIS_Shape(shp.Shape());
	m_color = color;
	Quantity_Color shpcolor (color.r, color.g, color.b,  Quantity_TOC_RGB);
	m_ashp->SetColor(shpcolor);
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

/*void servoce::shape_view_controller::set_location(double x, double y, double z) 
{
	uassert((*ctr)[idx].m_ashp);
	uassert((*ctr)[idx].scn);
	uassert((*ctr)[idx].scn->vwer);
	uassert((*ctr)[idx].scn->vwer->occ);
	uassert((*ctr)[idx].scn->vwer->occ->m_context);

	auto trf = gp_Trsf();
	trf.SetTranslation(gp_Vec(x,y,z));

	(*ctr)[idx].scn->vwer->occ->m_context->SetLocation((*ctr)[idx].m_ashp, trf);
	(*ctr)[idx].scn->vwer->occ->m_viewer->Redraw();
}*/


void servoce::shape_view_controller::set_location(const servoce::transformation& trans) 
{
	uassert((*ctr)[idx].m_ashp);
	uassert((*ctr)[idx].scn);
	uassert((*ctr)[idx].scn->vwer);
	uassert((*ctr)[idx].scn->vwer->occ);
	uassert((*ctr)[idx].scn->vwer->occ->m_context);

	gp_XYZ xyz;
	double angle;
	
	trans.trsf->GetRotation(xyz, angle);
	std::cout << xyz.X() << " " << xyz.Y() << " " << xyz.Z() << " " << angle << std::endl; 

	(*ctr)[idx].scn->vwer->occ->m_context->SetLocation((*ctr)[idx].m_ashp, *trans.trsf);
//	(*ctr)[idx].m_ashp->Redisplay();
	//(*ctr)[idx].scn->vwer->occ->m_viewer->Redraw();
}