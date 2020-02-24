#ifndef ZENCAD_SURFACE_H
#define ZENCAD_SURFACE_H

#include <servoce/curve2.h>
#include <servoce/shape.h>

class Geom_CylindricalSurface;
class Geom_Surface;

namespace servoce 
{
	namespace surface 
	{
		class surface 
		{
		public:
			Geom_Surface* surf;
			surface(Geom_Surface* surf) : surf(surf) {}
			servoce::shape map(servoce::curve2::curve2& tcrv);
		};

		surface cylinder(double r);
	}
}

#endif