#include <servoce/surface.h>
#include <Geom_CylindricalSurface.hxx>

using namespace servoce::surface;

cylinder::cylinder(double r) 
{
	surf = new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0,0,0), gp_Dir(0,0,1)), r);
}