#include <servoce/geombase.h>

#include <gp_Vec.hxx>
#include <gp_Pnt.hxx>

servoce::vector3::vector3(const gp_Vec& pnt) 
	: x(pnt.X()), y(pnt.Y()), z(pnt.Z()) {}

servoce::point3::point3(const gp_Pnt& pnt) 
	: x(pnt.X()), y(pnt.Y()), z(pnt.Z()) {}
