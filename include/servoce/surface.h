#ifndef ZENCAD_SURFACE_H
#define ZENCAD_SURFACE_H

#include <servoce/math3.h>
#include <servoce/curve2.h>
#include <servoce/topo.h>

struct Geom_CylindricalSurface;
struct Geom_Surface;

namespace servoce 
{
	namespace surface 
	{
		struct surface 
		{
			Geom_Surface* surf;
			surface(Geom_Surface* surf) : surf(surf) {}
			servoce::shape map(servoce::curve2::curve2& tcrv);
		};

		surface cylinder(double r);
	}
}

#endif