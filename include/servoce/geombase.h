#ifndef SERVOCE_GEOMBASE_H
#define SERVOCE_GEOMBASE_H

#include <servoce/linalg/linalg.h>

class TopoDS_Vertex;

class gp_Vec;
class gp_Pnt;
class gp_Vtx;
class TopoDS_Vertex;

namespace pybind11 
{
	class list;
	class tuple;
}

namespace servoce
{
	struct vector3 : public linalg::vec<double, 3>
	{
		using vec = linalg::vec<double, 3>;
		vector3() : vec{0,0,0} {}
		vector3(const gp_Vec& vec);
		vector3(double x, double y) : vec{ x,y,0 } {}
		vector3(double x, double y, double z) : vec { x,y,z } {}
		vector3(double* arr) : vec { arr } {}
		gp_Vec Vec() const;

		vector3(const pybind11::list&);
		vector3(const pybind11::tuple&);

		bool operator==(const vector3& oth) const { return oth.x == x && oth.y == y && oth.z == z; }
		bool operator!=(const vector3& oth) const { return oth.x != x || oth.y != y || oth.z != z; }
		vector3 operator-() const { return vector3(-x, -y, -z); }
		vector3 operator/(double a) const { return vector3(x / a, y / a, z / a); }

	} __attribute__((packed));

	struct point3 : public linalg::vec<double, 3>
	{
		using vec = linalg::vec<double, 3>;
		point3() : vec{0,0,0} {}
		point3(const gp_Pnt& pnt);
		point3(const gp_Vtx& vtx);
		point3(const TopoDS_Vertex& vtx);
		point3(double x, double y) : vec{ x,y,0 } {}
		point3(double x, double y, double z) : vec { x,y,z } {}
		point3(double* arr) : vec { arr } {}
		gp_Pnt Pnt() const;
		TopoDS_Vertex Vtx() const;

		point3(const pybind11::list&);
		point3(const pybind11::tuple&);

		static bool lexless_xyz(const point3& a, const point3& b);
		static bool early(const point3& a, const point3& b, double eps = 0.0000001);

		bool operator < (const servoce::point3& b) { 
			return lexless_xyz(*this, b);
		}
	} __attribute__((packed));
}

#endif