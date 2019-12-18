#ifndef SERVOCE_CURVE3_H
#define SERVOCE_CURVE3_H

#include <servoce/geombase.h>

#include <Geom_Curve.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <gp_Pnt.hxx>

#include <vector>

namespace servoce
{
	class shape;

	namespace curve3
	{
		class curve3
		{
		protected:
			Handle(Geom_Curve) crv;

		public:
			curve3(Geom_Curve* crv) : crv(crv) {}
			curve3(Handle(Geom_Curve) crv) : crv(crv) {}
			curve3() {}

			Handle(Geom_Curve) Curve() { return crv; }
			const Handle(Geom_Curve) Curve() const { return crv; }

			servoce::point3 value(double arg) { return d0(arg); }
			servoce::point3 d0(double arg) { return crv->Value(arg); }

			void dump(std::ostream& out) const;
			void load(std::istream& in);

			std::pair<double, double> range() const;

			servoce::shape edge();
			servoce::shape edge(double strt, double fini);
		};

		class bounded_curve3 : public curve3
		{
		public:
			bounded_curve3(Geom_Curve* crv) : curve3(crv) {}
			bounded_curve3(Handle(Geom_Curve) crv) : curve3(crv) {}
			bounded_curve3() {}
		};

		class conic_curve3 : public curve3
		{
			// TODO
		};

		// Basic:
		bounded_curve3 bezier(
			const std::vector<point3>& pnts);
		
		bounded_curve3 bezier(
			const std::vector<point3>& pnts, 
			const std::vector<double>& weights);

		bounded_curve3 bspline(
		    const std::vector<point3>& poles,
		    const std::vector<double>& knots,
		    const std::vector<int>& multiplicities,
		    int degree,
		    bool periodic = false
		);

		bounded_curve3 bspline(
		    const std::vector<point3>& poles,
		    const std::vector<double>& weights,
		    const std::vector<double>& knots,
		    const std::vector<int>& multiplicities,
		    int degree,
		    bool periodic = false,
		    bool check_rational = true
		);


		bounded_curve3 trimmed(); //TODO

		conic_curve3 circle(); //TODO
		conic_curve3 ellipse(); //TODO
		conic_curve3 hyperbola(); //TODO
		conic_curve3 parabola(); //TODO

		curve3 line(const point3& a, const vector3& b);
		curve3 offset(); //TODO

		// Advanced:
		curve3 interpolate(
		    const std::vector<servoce::point3>& pnts, const std::vector<servoce::vector3>& tang, bool closed);

		curve3 interpolate(
		    const std::vector<servoce::point3>& pnts, bool closed);
	}
}

#endif