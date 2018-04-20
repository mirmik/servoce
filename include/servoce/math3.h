#ifndef ZENGEOM_MATH3_H
#define ZENGEOM_MATH3_H

//#include <gp_Vec.hxx>

namespace servoce {
	namespace math3 {
		struct vector {
			double x, y, z;
			vector(double x, double y, double z) : x(x), y(y), z(z) {}
		};
	}
}

#endif