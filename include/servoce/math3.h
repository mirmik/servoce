#ifndef ZENGEOM_MATH3_H
#define ZENGEOM_MATH3_H

class gp_Vec;
class gp_Pnt;

namespace servoce {
	struct vector3 {
		double x, y, z;
		vector3() {}
		vector3(double x, double y) : x(x), y(y), z(0) {}
		vector3(double x, double y, double z) : x(x), y(y), z(z) {}
		gp_Vec Vec() const;
		bool operator==(const vector3& oth) const { return oth.x == x && oth.y == y && oth.z == z; }
		bool operator!=(const vector3& oth) const { return oth.x != x || oth.y != y || oth.z != z; }
	};

	struct point3 {
		double x, y, z;
		point3() {}
		point3(double x, double y) : x(x), y(y), z(0) {}
		point3(double x, double y, double z) : x(x), y(y), z(z) {}
		gp_Pnt Pnt() const;
	};
}

#endif