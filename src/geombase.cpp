#include <servoce/geombase.h>
#include <servoce/util/math.h>

#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <gp_Dir.hxx>
#include <gp_Quaternion.hxx>

#include <TopoDS_Vertex.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>

#include <BRep_Tool.hxx>

servoce::point2::point2(const gp_Pnt2d& pnt)
	: vec(pnt.X(), pnt.Y()) {}

servoce::vector3::vector3(const gp_Vec& pnt)
	: vec(pnt.X(), pnt.Y(), pnt.Z()) {}

servoce::point3::point3(const gp_Pnt& pnt)
	: vec(pnt.X(), pnt.Y(), pnt.Z()) {}

servoce::point3::point3(const TopoDS_Vertex& pnt) 
	: point3(BRep_Tool::Pnt(pnt)) {}

servoce::quaternion::quaternion(const gp_Quaternion& q)
	: quat(q.X(), q.Y(), q.Z(), q.W()) {}

gp_Vec servoce::vector3::Vec() const
{
	return gp_Vec(x, y, z);
}

gp_Dir servoce::vector3::Dir() const
{
	return gp_Dir(x, y, z);
}

gp_Pnt servoce::point3::Pnt() const
{
	return gp_Pnt(x, y, z);
}

gp_Pnt2d servoce::point2::Pnt() const
{
	return gp_Pnt2d(x, y);
}

TopoDS_Vertex servoce::point3::Vtx() const
{
	return BRepBuilderAPI_MakeVertex(Pnt());
}


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

bool servoce::point3::early(const point3& a, const point3& b, double eps)
{
	double xdiff = a.x - b.x;
	double ydiff = a.y - b.y;
	double zdiff = a.z - b.z;

	return early_zero(xdiff, eps) && early_zero(ydiff, eps) && early_zero(zdiff, eps);
}

bool servoce::vector3::early(const vector3& a, const vector3& b, double eps)
{
	double xdiff = a.x - b.x;
	double ydiff = a.y - b.y;
	double zdiff = a.z - b.z;

	return early_zero(xdiff, eps) && early_zero(ydiff, eps) && early_zero(zdiff, eps);
}


bool servoce::point2::early(const point2& a, const point2& b, double eps)
{
	double xdiff = a.x - b.x;
	double ydiff = a.y - b.y;

	return early_zero(xdiff, eps) && early_zero(ydiff, eps);
}

bool servoce::point2::lexless_xy(const point2& a, const point2& b)
{
	double xdiff = a.x - b.x;
	double ydiff = a.y - b.y;

	if (!early_zero(xdiff, 0.0000001))
	{
		return xdiff < 0;
	}

	if (!early_zero(ydiff, 0.0000001))
	{
		return ydiff < 0;
	}

	return false;
}