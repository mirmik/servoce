#include <servoce/surface.h>
#include <Geom_CylindricalSurface.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom2d_TrimmedCurve.hxx>

servoce::surface::surface servoce::surface::cylinder(double r) 
{
	return new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0,0,0), gp_Dir(0,0,1)), r);
}

servoce::shape servoce::surface::surface::map(servoce::curve2::trimmed_curve2& tcrv) 
{
	return BRepBuilderAPI_MakeEdge(tcrv.Curve(), surf).Shape();
}