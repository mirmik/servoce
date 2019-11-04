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
			curve3() {}

			Handle(Geom_Curve) Curve() { return crv; }
			const Handle(Geom_Curve) Curve() const { return crv; }

			servoce::point3 value(double arg) { return d0(arg); }
			servoce::point3 d0(double arg) { return crv->Value(arg); }

			void dump(std::ostream& out) const;
			void load(std::istream& in);

			//curve3 rotate(double angle);
		};

		class bounded_curve3 : public curve3
		{
			// TODO
		};

		class conic_curve3 : public curve3
		{
			// TODO
		};

		// Basic:
		bounded_curve3 bezier(); //TODO
		bounded_curve3 bspline(); //TODO
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

		class ACurve : public Geom_Curve
		{
			Standard_EXPORT virtual void Transform (const gp_Trsf& T) { BUG(); };
			Standard_EXPORT virtual Handle(Geom_Geometry) Copy() const { return new ACurve(); };
			Standard_EXPORT virtual void Reverse() { BUG(); };
			Standard_EXPORT virtual Standard_Real ReversedParameter (const Standard_Real U) const { BUG(); };
			Standard_EXPORT virtual Standard_Real FirstParameter() const { return -10; };
			Standard_EXPORT virtual Standard_Real LastParameter() const { return 10; };
			Standard_EXPORT virtual Standard_Boolean IsClosed() const { return false; };
			Standard_EXPORT virtual Standard_Boolean IsPeriodic() const { return false; };
			Standard_EXPORT virtual GeomAbs_Shape Continuity() const { BUG(); };
			Standard_EXPORT virtual Standard_Boolean IsCN (const Standard_Integer N) const { BUG(); };
			Standard_EXPORT virtual void D0 (const Standard_Real U, gp_Pnt& P) const 
			{ 
				P.SetX(U); 
				P.SetY(0); 
				P.SetZ(0); 
			};
			Standard_EXPORT virtual void D1 (const Standard_Real U, gp_Pnt& P, gp_Vec& V1) const { BUG(); };
			Standard_EXPORT virtual void D2 (const Standard_Real U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const { 
				P.SetX(0); 
				P.SetY(0); 
				P.SetZ(0); 
			};
			Standard_EXPORT virtual void D3 (const Standard_Real U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2, gp_Vec& V3) const { BUG(); };
			Standard_EXPORT virtual gp_Vec DN (const Standard_Real U, const Standard_Integer N) const { BUG(); };
			//void Delete() override {}
		};
	}
}

static servoce::curve3::ACurve a;

#endif