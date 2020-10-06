#include <servoce/boundbox.h>
#include <servoce/shape.h>
#include <servoce/solid.h>

#include <Bnd_Box.hxx>
#include <gp_Pnt.hxx>

servoce::point3 servoce::boundbox::corner_max() 
{
	return { _Box.CornerMax() };
}

servoce::point3 servoce::boundbox::corner_min() 
{
	return { _Box.CornerMin() };
}

servoce::shape servoce::boundbox::shape() 
{
	double x = xmax-xmin;
	double y = ymax-ymin;
	double z = zmax-zmin;

	return servoce::move(xmin,ymin,zmin)(servoce::box(x,y,z));
}