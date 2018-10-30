#ifndef SERVOCE_GEOMBASE_H
#define SERVOCE_GEOMBASE_H

class TopoDS_Vertex;

class gp_Vec;
class gp_Pnt;

namespace pybind11 
{
	class list;
}

namespace servoce
{
	struct vector3
	{
		double x, y, z;
		vector3() : x(0), y(0), z(0) {}
		vector3(const gp_Vec& pnt);
		vector3(double x, double y) : x(x), y(y), z(0) {}
		vector3(double x, double y, double z) : x(x), y(y), z(z) {}
		gp_Vec Vec() const;
		bool operator==(const vector3& oth) const { return oth.x == x && oth.y == y && oth.z == z; }
		bool operator!=(const vector3& oth) const { return oth.x != x || oth.y != y || oth.z != z; }
		vector3 operator-() const { return vector3(-x, -y, -z); }
		vector3 operator/(double a) const { return vector3(x / a, y / a, z / a); }

		vector3(const pybind11::list&);
	};

	struct point3
	{
		double x, y, z;
		point3() : x(0), y(0), z(0) {}
		point3(const gp_Pnt& pnt);
		point3(double x, double y) : x(x), y(y), z(0) {}
		point3(double x, double y, double z) : x(x), y(y), z(z) {}
		gp_Pnt Pnt() const;
		TopoDS_Vertex Vtx() const;

		point3(const pybind11::list&);
	};
}

#endif