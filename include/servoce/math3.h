#ifndef ZENGEOM_MATH3_H
#define ZENGEOM_MATH3_H

//#include <gp_Vec.hxx>

namespace servoce {
	struct vector3 {
		double x, y, z;
		vector3(double x, double y, double z) : x(x), y(y), z(z) {}
	};

	struct point3 {
		double x, y, z;
		point3(double x, double y, double z) : x(x), y(y), z(z) {}
	};
}

#endif