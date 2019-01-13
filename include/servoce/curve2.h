#ifndef ZENCAD_CURVE2_H
#define ZENCAD_CURVE2_H

#include <servoce/geombase.h>

struct Geom2d_Curve;
struct Geom2d_TrimmedCurve;

namespace servoce 
{
	namespace curve2
	{
		struct curve2 
		{
			Geom2d_Curve* crv;
			curve2(Geom2d_Curve* crv) : crv(crv) {}
			//curve2(const Geom2d_Curve& crv);
			const Geom2d_Curve* Curve() const;
			Geom2d_Curve* Curve();
			point2 value(double arg);

			void dump(std::ostream& out) const;
			void load(std::istream& in);
		};

		struct trimmed_curve2 : curve2
		{
			trimmed_curve2(Geom2d_TrimmedCurve* tcrv);
			trimmed_curve2(const curve2& crv, double start, double stop);
			const Geom2d_TrimmedCurve* TrimmedCurve() const;
			Geom2d_TrimmedCurve* TrimmedCurve();
		};

		curve2 ellipse(double major, double minor);
		curve2 segment(servoce::point2 a, servoce::point2 b);
	}
}

#endif