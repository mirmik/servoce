#include <servoce/math3.h>

#include <gp_Vec.hxx>

gp_Vec servoce::vector3::Vec() const { return gp_Vec(x,y,z); }
gp_Pnt servoce::point3::Pnt() const { return gp_Pnt(x,y,z); }