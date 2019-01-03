#ifndef ZENGEOM_SOLID_H
#define ZENGEOM_SOLID_H

#include <servoce/topo.h>
#include <servoce/math3.h>

namespace servoce
{
	shape box(double x, double y, double z, bool center = false);
	shape sphere(double r);
	shape cylinder(double r, double h, bool center = false);
	shape cylinder(double r, double h, double angle, bool center = false);
	shape cylinder(double r, double h, double a1, double a2, bool center = false);
	shape cone(double r1, double r2, double h, bool center = false);
	shape cone(double r1, double r2, double h, double angle, bool center = false);
	shape cone(double r1, double r2, double h, double a1, double a2, bool center = false);
	shape torus(double r1, double r2);
	shape torus(double r1, double r2, double ua);
	shape torus(double r1, double r2, double va1, double va2);
	shape torus(double r1, double r2, double va1, double va2, double ua);


	//sweep3d
	shape make_linear_extrude(const shape& base, const servoce::vector3& vec, bool center = false);
	shape make_linear_extrude(const shape& base, double z, bool center = false);
	shape make_pipe(const shape& profile, const shape& path);
	shape make_pipe_shell(const shape& profile, const shape& path, bool isFrenet = false);

	shape loft(const std::vector<shape>& vec);

	shape halfspace();
}

#endif