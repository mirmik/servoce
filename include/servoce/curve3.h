#ifndef SERVOCE_CURVE3_H
#define SERVOCE_CURVE3_H

#include <servoce/geombase.h>

#include <Geom_Curve.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <gp_Pnt.hxx>

#include <vector>

namespace servoce 
{
	namespace curve3
	{
		class curve3
		{
			Handle(Geom_Curve) crv;

		public:
			curve3(Geom_Curve* crv) : crv(crv) {}
			curve3(Handle(Geom_Curve) crv);
			curve3(){}

			Handle(Geom_Curve) Curve() { return crv; }
			const Handle(Geom_Curve) Curve() const { return crv; }

			servoce::point3 value(double arg) { return crv->Value(arg); }

			void dump(std::ostream& out) const;
			void load(std::istream& in);

			//curve3 rotate(double angle);
		};

		curve3 interpolate(
			const std::vector<servoce::point3>& pnts, const std::vector<servoce::vector3>& tang, bool closed);
		
		curve3 interpolate(
			const std::vector<servoce::point3>& pnts, bool closed);
	}
}

#endif