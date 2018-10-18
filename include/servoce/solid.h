#ifndef ZENGEOM_SOLID_H
#define ZENGEOM_SOLID_H

#include <servoce/topo.h>
#include <servoce/math3.h>

namespace servoce
{
	//prim3d
	shape make_box(double x, double y, double z, bool center = false);
	shape make_sphere(double r);
	shape make_cylinder(double r, double h, bool center = false);
	shape make_cylinder(double r, double h, double angle, bool center = false);
	shape make_cone(double r1, double r2, double h, bool center = false);
	shape make_torus(double r1, double r2);

	//sweep3d
	shape make_linear_extrude(const shape& base, const servoce::vector3& vec, bool center = false);
	shape make_linear_extrude(const shape& base, double z, bool center = false);
	shape make_pipe(const shape& profile, const shape& path);
	shape make_pipe_shell(const shape& profile, const shape& path, bool isFrenet = false);
}

#endif