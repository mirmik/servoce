#ifndef SERVOCE_ANALYTIC_CURVE3_H
#define SERVOCE_ANALYTIC_CURVE3_H

#include <servoce/curve3.h>
#include <pybind11/pybind11.h>

namespace servoce
{
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
			P.SetY(U * U);
			P.SetZ(U);
		};
		Standard_EXPORT virtual void D1 (const Standard_Real U, gp_Pnt& P, gp_Vec& V1) const { BUG(); };
		Standard_EXPORT virtual void D2 (const Standard_Real U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const
		{
			P.SetX(U);
			P.SetY(U * U);
			P.SetZ(U);

			V1.SetX(1);
			V1.SetY(2 * U);
			V1.SetZ(1);

			V2.SetX(0);
			V2.SetY(2);
			V2.SetZ(0);
		};
		Standard_EXPORT virtual void D3 (const Standard_Real U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2, gp_Vec& V3) const { BUG(); };
		Standard_EXPORT virtual gp_Vec DN (const Standard_Real U, const Standard_Integer N) const { BUG(); };
		//void Delete() override {}
	};

	class analytic_curve3 
	{
	public:
		analytic_curve3(){}
		pybind11::function func;

		std::string doit(int x) 
		{
			return pybind11::str(func(x));
		}
	};
}

#endif