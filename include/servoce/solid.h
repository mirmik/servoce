#ifndef ZENGEOM_SOLID_H
#define ZENGEOM_SOLID_H

#include <servoce/topo.h>
#include <servoce/math3.h>

namespace servoce {
	namespace prim3d {
		solid make_box(double x, double y, double z, bool center = false);
		solid make_sphere(double r);
		solid make_cylinder(double r, double h, bool center = false);
		solid make_cone(double r1, double r2, double h, bool center = false);
		solid make_torus(double r1, double r2);
	}

	namespace sweep3d {
		solid make_linear_extrude(const servoce::shape& base, const servoce::vector3& vec);
		solid make_pipe(const servoce::shape& profile, const servoce::wire& path);
	}
}

#endif