#include <servoce/prs3d.h>

#include <Prs3d_Arrow.hxx>
#include <Geom_CartesianPoint.hxx>
#include <AIS_Line.hxx>
#include <Prs3d_Drawer.hxx>
#include <Prs3d_ArrowAspect.hxx>
#include <Prs3d_LineAspect.hxx>
#include <AIS_InteractiveContext.hxx>

static Aspect_TypeOfLine line_type_to_TypeOfLine(servoce::line_style style) 
{
	switch (style) 
	{
		case servoce::line_style::solid_line: return Aspect_TOL_SOLID;
		case servoce::line_style::dash_line: return Aspect_TOL_DASH;
		case servoce::line_style::dot_line: return Aspect_TOL_DOT;
		case servoce::line_style::dotdash_line: return Aspect_TOL_DOTDASH;
	}
	throw std::runtime_error("wrong line_style");
}

servoce::interactive_object servoce::draw::arrow(
	const servoce::point3& pnt, 
	const servoce::vector3& vec, 
	const servoce::color& clr, 
	double arrlen,
	double width)
{
	gp_Pnt location = pnt.Pnt();
	gp_Vec direction = vec.Vec();

	Handle(Geom_CartesianPoint) geomPoint1 = new Geom_CartesianPoint(location);
	Handle(Geom_CartesianPoint) geomPoint2 = new Geom_CartesianPoint(location.Translated(direction));
	Handle(AIS_Line) aisLine = new AIS_Line(geomPoint1, geomPoint2);

	Handle(Prs3d_Drawer) aDrawer = new Prs3d_Drawer;

	Handle(Prs3d_ArrowAspect) arrowAspect =	new Prs3d_ArrowAspect;
	arrowAspect->SetLength(arrlen);
	aDrawer->SetArrowAspect(arrowAspect);
	aDrawer->SetLineArrowDraw(Standard_True);
	
	Handle(Prs3d_LineAspect) lineAspect = new Prs3d_LineAspect(
		clr.Color(), 
		line_type_to_TypeOfLine(line_style::solid_line), 
		width);
	aDrawer->SetLineAspect(lineAspect);
	
	aisLine->SetAttributes(aDrawer);
	
	return servoce::interactive_object(aisLine);
}

servoce::interactive_object servoce::draw::line(
		    const servoce::point3& pnt1,
		    const servoce::point3& pnt2,
			const servoce::color& clr, 
			line_style style,
			double width
		    ) 
{
	Handle(Geom_CartesianPoint) geomPoint1 = new Geom_CartesianPoint(pnt1.Pnt());
	Handle(Geom_CartesianPoint) geomPoint2 = new Geom_CartesianPoint(pnt2.Pnt());

	Handle(AIS_Line) aisLine = new AIS_Line(geomPoint1, geomPoint2);
	Handle(Prs3d_LineAspect) aspect = new Prs3d_LineAspect(
		clr.Color(), 
		line_type_to_TypeOfLine(style), 
		width);
	//aspect->SetTypeOfLine(Aspect_TOL_SOLID);
	Handle(Prs3d_Drawer) aDrawer = new Prs3d_Drawer;
	aDrawer->SetLineAspect(aspect);

	aisLine->SetAttributes(aDrawer);

	//aisLine->SetColor(Quantity_Color(clr.r, clr.g, clr.b, Quantity_TOC_RGB));

	return servoce::interactive_object(aisLine);
}