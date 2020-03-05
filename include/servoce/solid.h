#ifndef ZENGEOM_SOLID_H
#define ZENGEOM_SOLID_H

#include <servoce/shape.h>

namespace servoce
{
	class shell_shape;

	class solid_shape : public shape
	{
	public:
		//wire_shape(TopoDS_Wire& arg) : shape(arg) {}
		solid_shape() {}
		solid_shape(const TopoDS_Solid& arg) : shape((const TopoDS_Shape&)arg) {}
	};

	//class sweep_solid_shape {};

	solid_shape box(double x, double y, double z, bool center = false);
	solid_shape sphere(double r);
	solid_shape sphere(double r, double an1);
	solid_shape sphere(double r, double an1, double an2);
	solid_shape sphere(double r, double an1, double an2, double an3);
	solid_shape cylinder(double r, double h, bool center = false);
	solid_shape cylinder(double r, double h, double angle, bool center = false);
	solid_shape cylinder(double r, double h, double a1, double a2, bool center = false);
	solid_shape cone(double r1, double r2, double h, bool center = false);
	solid_shape cone(double r1, double r2, double h, double angle, bool center = false);
	solid_shape cone(double r1, double r2, double h, double a1, double a2, bool center = false);
	solid_shape torus(double r1, double r2);
	solid_shape torus(double r1, double r2, double ua);
	solid_shape torus(double r1, double r2, double va1, double va2);
	solid_shape torus(double r1, double r2, double va1, double va2, double ua);


	//sweep3d
	shape make_linear_extrude(const shape& base, const servoce::vector3& vec, bool center = false);
	shape make_linear_extrude(const shape& base, double z, bool center = false);
	shape make_pipe_0(const shape& profile, const shape& spine);
	shape make_pipe(const shape& profile, const shape& spine, const std::string mode, bool force_approx_c1=false);
	//shape make_pipe_shell(const std::vector<const shape*>& profile, const shape& spine, bool isFrenet = false, bool approx_c1=false);
	shape make_pipe_shell(
		const std::vector<const shape*>& wires, 
		const shape& spine, 
		bool frenet=false, 
		bool force_approx_c1=false, 
		const vector3& binormal = vector3(0,0,0),
		const vector3& parallel= vector3(0,0,0),
		bool discrete=false,
		bool solid=true);
	//shape make_pipe_shell(const shape& profile, const shape& spine, 
	//	const shape& auxiliary_spine, bool curvilinear_equivalence);

	shape loft(const std::vector<shape>& vec, bool smooth=false);
	shape revol(const shape& proto, double angle = 0.0);

	solid_shape halfspace();
	shape thicksolid(const shape& proto, const std::vector<point3>& pnt, double thickness);

	shape fillet(const shape& shp, double r, const std::vector<point3>& refs);
	shape fillet(const shape& shp, double r);
	shape chamfer(const shape& shp, double r, const std::vector<point3>& refs);
	shape chamfer(const shape& shp, double r);

	shape unify(const shape& proto);

	servoce::solid_shape make_solid(const servoce::shell_shape& shp);
}

#endif
