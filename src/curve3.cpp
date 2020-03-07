#include <servoce/curve3.h>
#include <servoce/wire.h>
#include <servoce/edge.h>

#include <TColgp_HArray1OfPnt.hxx>
#include <TColStd_HArray1OfBoolean.hxx>
#include <BinTools_CurveSet.hxx>

#include <GeomAPI_Interpolate.hxx>
#include <Geom_Line.hxx>

#include <Geom_Circle.hxx>
#include <Geom_BezierCurve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <GeomAdaptor_HCurve.hxx>

#include <servoce/opencascade_types.h>

using namespace servoce;

conic_curve3 servoce::circle_curve3(double radius) 
{
	return new Geom_Circle(gp::XOY(), radius);
}

servoce::curve3 servoce::line_curve3(const servoce::point3& a, const servoce::vector3& b) 
{
	return new Geom_Line(a.Pnt(), b.Dir());
}

servoce::curve3 servoce::interpolate_curve3(
    const std::vector<servoce::point3>& pnts, const std::vector<servoce::vector3>& tang, bool closed)
{
	Handle(TColgp_HArray1OfPnt) _pnts = new TColgp_HArray1OfPnt(1, pnts.size());

	for (unsigned int i = 0; i < pnts.size(); ++i)
		_pnts->SetValue(i + 1, pnts[i].Pnt());

	GeomAPI_Interpolate algo(_pnts, /*_params,*/ closed, 0.0000001);

	if (tang.size())
	{
		TColgp_Array1OfVec _tang(1, tang.size());
		Handle(TColStd_HArray1OfBoolean) _bools = new TColStd_HArray1OfBoolean(1, tang.size());

		for (unsigned int i = 0; i < pnts.size(); ++i)
			_tang.SetValue(i + 1, tang[i].Vec());

		for (unsigned int i = 0; i < pnts.size(); ++i)
			_bools->SetValue(i + 1, tang[i] != servoce::vector3(0, 0, 0));

		algo.Load(_tang, _bools);
	}

	algo.Perform();
	return dynamic_cast<Geom_Curve*>(algo.Curve().get());
}

servoce::curve3 servoce::interpolate_curve3(
    const std::vector<servoce::point3>& pnts, bool closed)
{
	Handle(TColgp_HArray1OfPnt) _pnts = new TColgp_HArray1OfPnt(1, pnts.size());

	for (unsigned int i = 0; i < pnts.size(); ++i)
		_pnts->SetValue(i + 1, pnts[i].Pnt());

	GeomAPI_Interpolate algo(_pnts, /*_params,*/ closed, 0.0000001);

	algo.Perform();
	return dynamic_cast<Geom_Curve*>(algo.Curve().get());
}

void servoce::curve3::dump(std::ostream& out) const
{
	Handle(Geom_Curve) h = dynamic_cast<Geom_Curve*>(crv.get());
	BinTools_CurveSet::WriteCurve(h, out);
}

void servoce::curve3::load(std::istream& in)
{
	Handle(Geom_Curve) h;
	BinTools_CurveSet::ReadCurve (in, h);
	crv = dynamic_cast<Geom_Curve*>(h.get());
}

servoce::bounded_curve3 servoce::bspline_curve3(
	const std::vector<point3>& poles,
	const std::vector<double>& knots,
	const std::vector<int>& multiplicities,
	int degree,
	bool periodic
)
{
	auto _poles = opencascade_array1_of_pnt(poles);
	auto _knots = opencascade_array1_of_real(knots);
	auto _multiplicities = opencascade_array1_of_int(multiplicities);

	Geom_BSplineCurve * crv = new Geom_BSplineCurve(
		_poles, _knots, _multiplicities, 
		degree, periodic);
	return crv;
}

servoce::bounded_curve3 servoce::bspline_curve3(
	const std::vector<point3>& poles,
	const std::vector<double>& weights,
	const std::vector<double>& knots,
	const std::vector<int>& multiplicities,
	int degree,
	bool periodic,
	bool check_rational 
) 
{
	auto _poles = opencascade_array1_of_pnt(poles);
	auto _weigths = opencascade_array1_of_real(weights);
	auto _knots = opencascade_array1_of_real(knots);
	auto _multiplicities = opencascade_array1_of_int(multiplicities);

	Geom_BSplineCurve * crv = new Geom_BSplineCurve(
		_poles, _knots, _weigths, _multiplicities, 
		degree, periodic, check_rational);
	return crv;
}

servoce::bounded_curve3 servoce::bezier_curve3(
	const std::vector<point3>& poles) 
{
	auto _poles = opencascade_array1_of_pnt(poles);

	Geom_BezierCurve * curve = new Geom_BezierCurve(_poles);
	return curve;
}

servoce::bounded_curve3 servoce::bezier_curve3(
	const std::vector<point3>& poles, 
	const std::vector<double>& weights) 
{
	auto _poles = opencascade_array1_of_pnt(poles);
	auto _weights = opencascade_array1_of_real(weights);

	Geom_BezierCurve * curve = new Geom_BezierCurve(_poles, _weights);
	return curve;
}

servoce::shape servoce::curve3::edge() 
{
	return servoce::make_edge(*this);
}

servoce::shape servoce::curve3::edge(double strt, double fini) 
{
	return servoce::make_edge(*this, strt, fini);
}

std::pair<double,double> 
servoce::curve3::range() const 
{
	return { crv->FirstParameter(), crv->LastParameter() };
}

Handle(Adaptor3d_HCurve) servoce::curve3::HCurveAdaptor() const 
{
	return (Handle(Adaptor3d_HCurve)) new GeomAdaptor_HCurve(Curve());
}


servoce::curve3 servoce::curve3::transform(const servoce::transformation& trans) const
{
	return Handle(Geom_Curve)::DownCast(Curve()->Transformed(*trans.trsf));
}