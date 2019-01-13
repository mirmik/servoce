#ifndef ZENCAD_CURVE2_H
#define ZENCAD_CURVE2_H

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
		};

		struct trimmed_curve2 : curve2
		{
			trimmed_curve2(Geom2d_TrimmedCurve* tcrv);
			trimmed_curve2(const curve2& crv, double start, double stop);
		};

		curve2 ellipse(double major, double minor);
	}
}

#endif