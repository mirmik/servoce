#ifndef ZENGEOM_SOLID_H
#define ZENGEOM_SOLID_H

#include <servoce/topo.h>
#include <servoce/math3.h>

class BRepPrimAPI_MakeSweep;

namespace servoce {
	namespace prim3d {
		solid make_box(double x, double y, double z, bool center = false);
		solid make_sphere(double r);
		solid make_cylinder(double r, double h, bool center = false);
		solid make_cone(double r1, double r2, double h, bool center = false);
		solid make_torus(double r1, double r2);
	}

	struct sweep_solid : public solid {
		TopoDS_Shape* m_first;
		TopoDS_Shape* m_last;
		sweep_solid(BRepPrimAPI_MakeSweep&& builder);
		virtual ~sweep_solid();
	};

	namespace sweep3d {
		sweep_solid make_linear_extrude(const servoce::shape& base, const servoce::vector3& vec);
		sweep_solid make_pipe(const servoce::shape& profile, const servoce::wire& path);
	}
}

#endif