#include <servoce/geombase.h>

#include <gp_Vec.hxx>
#include <gp_Pnt.hxx>
#include <TopoDS_Vertex.hxx>

#include <BRep_Tool.hxx>

#include <servoce/util/math.h>

servoce::vector3::vector3(const gp_Vec& pnt) 
	: x(pnt.X()), y(pnt.Y()), z(pnt.Z()) {}

servoce::point3::point3(const gp_Pnt& pnt) 
	: x(pnt.X()), y(pnt.Y()), z(pnt.Z()) {}

servoce::point3::point3(const TopoDS_Vertex& pnt) : point3(BRep_Tool::Pnt(pnt)) {};


bool servoce::point3::lexless_xyz(const point3& a, const point3& b) 
{
	double xdiff = a.x - b.x;
	double ydiff = a.y - b.y;
	double zdiff = a.z - b.z;

	if (!early_zero(xdiff, 0.0000001)) 
	{
		return xdiff < 0;
	}

	if (!early_zero(ydiff, 0.0000001)) 
	{
		return ydiff < 0;	
	}

	if (!early_zero(zdiff, 0.0000001)) 
	{	
		return zdiff < 0;	
	}

	return false;

	//return std::lexicographical_compare(&a.x, &a.z, &b.x, &b.z);
}


bool servoce::point3::early(const point3& a, const point3& b) 
{
	double xdiff = a.x - b.x;
	double ydiff = a.y - b.y;
	double zdiff = a.z - b.z;

	double eps = 0.0000001;

	return early_zero(xdiff, eps) && early_zero(ydiff, eps) && early_zero(zdiff, eps);
}