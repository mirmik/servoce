#ifndef ZENCAD_SURFACE_H
#define ZENCAD_SURFACE_H

#include <servoce/curve2.h>
#include <servoce/curve3.h>
#include <servoce/shape.h>
#include <servoce/law.h>

#include <servoce/surface_algo.h>

class Geom_CylindricalSurface;
class Geom_Surface;

namespace servoce
{
	class curve3;

	class surface : public surface_algo<surface>
	{
	public:
		Handle(Geom_Surface) surf;
		surface() : surf(nullptr) {}
		surface(Geom_Surface* surf) : surf(surf) {}
		surface(Handle(Geom_Surface) surf) : surf(surf) {}
		servoce::shape map(servoce::curve2::curve2& tcrv);

		Handle(Geom_Surface) Surface() { return surf; }
		const Handle(Geom_Surface) Surface() const { return surf; }

		auto& AdaptorSurface() { return *surf; }
		const auto& AdaptorSurface() const { return *surf; }

		void dump(std::ostream& out) const;
		void load(std::istream& in);

		std::pair<double, double> urange()
		{
			double u1, u2, v1, v2;
			surf->Bounds(u1, u2, v1, v2);
			return {u1, u2};
		}

		std::pair<double, double> vrange()
		{
			double u1, u2, v1, v2;
			surf->Bounds(u1, u2, v1, v2);
			return {v1, v2};
		}

		curve3 v_iso_curve(double parameter);
		curve3 u_iso_curve(double parameter);
	};

	surface cylinder_surface(double r);
	surface tube_surface(const servoce::curve3& crv, double r);

	surface sweep_surface(const law_section& slaw, const law_location& llaw, double tol, int cont, int maxdegree, int maxsegm);
}

#endif