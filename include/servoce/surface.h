#ifndef ZENCAD_SURFACE_H
#define ZENCAD_SURFACE_H

#include <servoce/math3.h>

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
		};

		static inline surface cylinder(double r);
	}
}

#endif