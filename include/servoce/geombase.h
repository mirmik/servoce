#ifndef SERVOCE_GEOMBASE_H
#define SERVOCE_GEOMBASE_H

#include <servoce/linalg/linalg.h>
#include <igris/dprint.h>
#include <nos/print.h>
#include <nos/fprint.h>

class TopoDS_Vertex;

class gp_Vec;
class gp_Dir;
class gp_Pnt;
class gp_Pnt2d;
class gp_Quaternion;
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
	class point3;
	class matrix33;

	class point2 : public linalg::vec<double, 2>
	{
	public:
		using vec = linalg::vec<double, 2>;

		point2() : vec{0, 0} {}
		point2(double x, double y) : vec{ x, y } {}
		point2(double arr[2]) : vec(arr[0], arr[1]) {}

		point2(const gp_Pnt2d& pnt);
		point2(const vec& oth) : vec(oth) {}
		gp_Pnt2d Pnt() const;

		point2(const pybind11::list&);
		point2(const pybind11::tuple&);

		static bool lexless_xy(const point2& a, const point2& b);
		static bool early(const point2& a, const point2& b, double eps = 0.0000001);

		bool operator < (const servoce::point2& b) const
		{
			return lexless_xy(*this, b);
		}
	};

	class vector3 : public linalg::vec<double, 3>
	{
	public:
		using vec = linalg::vec<double, 3>;

		vector3() : vec{0, 0, 0} {}
		vector3(double x, double y) : vec{ x, y, 0 } {}
		vector3(double x, double y, double z) : vec { x, y, z } {}
		vector3(double arr[3]) : vec(arr[0], arr[1], arr[2]) {}
		
		vector3(const vec& oth) : vec(oth) {}
		vector3(const vector3& oth) : vec(oth) {}
		vector3(const gp_Vec& vec);

		point3 to_point3() const;

		gp_Vec Vec() const;
		gp_Dir Dir() const;

		vector3(const pybind11::list&);
		vector3(const pybind11::tuple&);

		double length() const { return linalg::length(*this); }
		vector3 normalize() const { return vector3(linalg::normalize(*this)); }
		
		vector3 cross(const vector3& oth) const { return vector3(linalg::cross(*this, oth)); }

		bool operator==(const vector3& oth) const { return oth.x == x && oth.y == y && oth.z == z; }
		bool operator!=(const vector3& oth) const { return oth.x != x || oth.y != y || oth.z != z; }
		vector3 operator-() const { return vector3(-x, -y, -z); }

		matrix33 outerprod(const vector3& oth);

		ssize_t print_to(nos::ostream& out) const
		{
			return nos::fprint_to(out, "vector3({},{},{})", x, y, z);
		}
	};

	class point3 : public linalg::vec<double, 3>
	{
	public:
		using vec = linalg::vec<double, 3>;

		point3() : vec{0, 0, 0} {}
		point3(double x, double y) : vec{ x, y, 0 } {}
		point3(double x, double y, double z) : vec { x, y, z } {}
		point3(double arr[3]) : vec(arr[0], arr[1], arr[2]) {}

		point3(const gp_Pnt& pnt);
		point3(const gp_Vtx& vtx);
		point3(const TopoDS_Vertex& vtx);
		point3(const vec& oth) : vec(oth) {}
		gp_Pnt Pnt() const;
		TopoDS_Vertex Vtx() const;

		point3(const pybind11::list&);
		point3(const pybind11::tuple&);

		static bool lexless_xyz(const point3& a, const point3& b);
		static bool early(const point3& a, const point3& b, double eps = 0.0000001);

		double distance(const point3& o) const
		{
			double xd = x - o.x;
			double yd = y - o.y;
			double zd = z - o.z;
			return sqrt(xd * xd + yd * yd + zd * zd);
		}

		point3 lerp(const point3& o, double koeff) const
		{
			return point3(linalg::lerp<vec,vec,double>(*this, o, koeff));
		}

		bool operator < (const servoce::point3& b) const { return lexless_xyz(*this, b); }
		bool operator == (const servoce::point3& oth) const { return x == oth.x && y == oth.y && z == oth.z; }

		ssize_t print_to(nos::ostream& out) const
		{
			return nos::fprint_to(out, "point3({},{},{})", x, y, z);
		}
	};

	class matrix33 : public linalg::mat<double,3,3> 
	{
		using parent = linalg::mat<double,3,3>;

	public:
		matrix33(	
				double a00, double a01, double a02, 
				double a10, double a11, double a12, 
				double a20, double a21, double a22) 
			:
				parent({a00,a10,a20}, {a01,a11,a21}, {a02,a12,a22})
		{

		}	

		matrix33(const parent& oth) : parent(oth) {}

		double* data() 
		{
			return parent::arr;
		}

		static constexpr int rows() { return 3; }
		static constexpr int cols() { return 3; }
	};

	class quaternion : public linalg::vec<double,4>
	{
	public:
		using quat = linalg::vec<double,4>;

		quaternion() : quat{0, 0, 0, 1} {}
		quaternion(double x, double y, double z, double w) : quat{ x, y, z, w } {}

		quaternion(const quat& q) : quat(q) {};
		quaternion(const gp_Quaternion& vec);

		quaternion normalize() { return quaternion(linalg::normalize(*this)); }
		//quaternion(double* arr) : quat { arr } {}
		gp_Quaternion Quaternion() const;

		quaternion(const pybind11::list&);
		quaternion(const pybind11::tuple&);

		matrix33 to_matrix() 
		{
			return linalg::qmat(*this);
		}

		vector3 rotation_vector() const
		{
			double angle = linalg::qangle(*this);
			if (::fabs(angle) < 0.000001) 
				return {0,0,0};
			return vector3(linalg::qaxis(*this) * angle);
		}

		quaternion inverse() { return linalg::qconj(*this); }
		vector3 rotate(const vector3& vec) { return linalg::qrot(*this, vec); }

	//	bool operator==(const vector3& oth) const { return oth.x == x && oth.y == y && oth.z == z; }
	//	bool operator!=(const vector3& oth) const { return oth.x != x || oth.y != y || oth.z != z; }
	//	vector3 operator-() const { return vector3(-x, -y, -z); }
	};

	static inline vector3 operator/(const vector3& v, double a)
	{ return vector3(v.x / a, v.y / a, v.z / a); }

	static inline vector3 operator*(const vector3& v, double a)
	{ return vector3(v.x * a, v.y * a, v.z * a); }

	static inline vector3 operator*(double a, const vector3& v)
	{ return vector3(v.x * a, v.y * a, v.z * a); }

	static inline vector3 operator+(const vector3& a, const vector3& b)
	{ return vector3(a.x + b.x, a.y + b.y, a.z + b.z); }

	static inline vector3 operator-(const vector3& a, const vector3& b)
	{ return vector3(a.x - b.x, a.y - b.y, a.z - b.z); }

	static inline vector3 operator-(const point3& a, const point3& b)
	{ return vector3(a.x - b.x, a.y - b.y, a.z - b.z); }

	static inline point3 operator+(const point3& a, const vector3& b)
	{ return point3(a.x + b.x, a.y + b.y, a.z + b.z); }

	static inline point3 operator-(const point3& a, const vector3& b)
	{ return point3(a.x - b.x, a.y - b.y, a.z - b.z); }

	

	static inline quaternion operator*(const quaternion& a, const quaternion& b)
	{ 
		return linalg::qmul((const linalg::vec<double,4> &)a, (const linalg::vec<double,4> &)b); 
	}

	inline point3 vector3::to_point3() const { return point3(x,y,z); }


	inline matrix33 vector3::outerprod(const vector3& oth) { return linalg::outerprod(*this, oth); }
}

#endif