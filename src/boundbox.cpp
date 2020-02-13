#include <servoce/boundbox.h>

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
