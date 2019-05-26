#ifndef SERVOCE_GEOMBASE_H
#define SERVOCE_GEOMBASE_H

#include <servoce/linalg/linalg.h>

class TopoDS_Vertex;

class gp_Vec;
class gp_Pnt;
class gp_Pnt2d;
class gp_Vtx;
class TopoDS_Vertex;

namespace pybind11 
{
	class list;
	class tuple;
	class object;
}

namespace servoce
{
	class vector3 : public linalg::vec<double, 3>
	{
	public:
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

	};// __attribute__((packed));

	class point3 : public linalg::vec<double, 3>
	{
	public:
		using vec = linalg::vec<double, 3>;
		point3() : vec{0,0,0} {}
		point3(const gp_Pnt& pnt);
		point3(const gp_Vtx& vtx);
		point3(const TopoDS_Vertex& vtx);
		point3(double x, double y) : vec{ x,y,0 } {}
		point3(double x, double y, double z) : vec { x,y,z } {}
		point3(linalg::vec<double, 3> v) : vec { v } {}
		point3(double* arr) : vec { arr } {}
		gp_Pnt Pnt() const;
		TopoDS_Vertex Vtx() const;

		point3(const pybind11::list&);
		point3(const pybind11::tuple&);

		static bool lexless_xyz(const point3& a, const point3& b);
		static bool early(const point3& a, const point3& b, double eps = 0.0000001);

		double distance(const point3& o) 
		{
			double xd = x-o.x;
			double yd = y-o.y;
			double zd = z-o.z;
			return sqrt(xd*xd + yd*yd + zd*zd);
		}

		point3 lerp(const point3& o, double koeff) 
		{
			return point3(linalg::lerp(*this, o, koeff));
		}

		bool operator < (const servoce::point3& b) { 
			return lexless_xyz(*this, b);
		}
	};// __attribute__((packed));


	static inline vector3 operator/(const vector3& v, double a) 
	{ return vector3(v.x / a, v.y / a, v.z / a); }
	
	static inline vector3 operator*(const vector3& v, double a) 
	{ return vector3(v.x * a, v.y * a, v.z * a); }

	static inline vector3 operator+(const vector3& a,const vector3& b) 
	{ return vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
	
	static inline vector3 operator-(const vector3& a,const vector3& b) 
	{ return vector3(a.x - b.x, a.y - b.y, a.z - b.z); }

	static inline vector3 operator-(const point3& a,const point3& b) 
	{ return vector3(a.x - b.x, a.y - b.y, a.z - b.z); }

	static inline point3 operator+(const point3& a,const vector3& b) 
	{ return point3(a.x + b.x, a.y + b.y, a.z + b.z); }

	static inline point3 operator-(const point3& a,const vector3& b) 
	{ return point3(a.x - b.x, a.y - b.y, a.z - b.z); }



	class point2 : public linalg::vec<double, 2>
	{
	public:
		using vec = linalg::vec<double, 2>;
		point2() : vec{0,0} {}
		point2(const gp_Pnt2d& pnt);
		point2(double x, double y) : vec{ x,y } {}
		point2(double* arr) : vec { arr } {}
		gp_Pnt2d Pnt() const;
		
		point2(const pybind11::list&);
		point2(const pybind11::tuple&);

		static bool lexless_xy(const point2& a, const point2& b);
		static bool early(const point2& a, const point2& b, double eps = 0.0000001);

		bool operator < (const servoce::point2& b) { 
			return lexless_xy(*this, b);
		}
	};// __attribute__((packed));
}

#endif