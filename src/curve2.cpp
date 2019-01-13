#include <servoce/curve2.h>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2d_Ellipse.hxx>
#include <gp_Ax2d.hxx>

using namespace servoce::curve2;

trimmed_curve2::trimmed_curve2(Geom2d_TrimmedCurve* tcrv) : curve2(tcrv) {}

trimmed_curve2::trimmed_curve2(const curve2& crv, double start, double stop) 
	: curve2(new Geom2d_TrimmedCurve(crv.crv, start, stop)) {}

curve2 ellipse(double major, double minor)
{
	return new Geom2d_Ellipse(gp_Ax2d(gp_Pnt2d(0,0), gp_Dir2d(1,0)), major, minor);
}