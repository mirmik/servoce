#ifndef ZENGEOM_MATH3_H
#define ZENGEOM_MATH3_H

class gp_Vec;
class gp_Pnt;

namespace servoce {
	struct vector3 {
		double x, y, z;
		vector3(double x, double y, double z) : x(x), y(y), z(z) {}
		gp_Vec Vec() const;
	};

	struct point3 {
		double x, y, z;
		point3(double x, double y, double z) : x(x), y(y), z(z) {}
		gp_Pnt Pnt() const;
	};
}

#endif