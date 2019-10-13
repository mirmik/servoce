#include <servoce/curve3.h>

#include <TColgp_HArray1OfPnt.hxx>
#include <TColStd_HArray1OfBoolean.hxx>
#include <BinTools_CurveSet.hxx>

#include <GeomAPI_Interpolate.hxx>
#include <Geom_Line.hxx>

servoce::curve3::curve3 servoce::curve3::line(const servoce::point3& a, const servoce::vector3& b) 
{
	return new Geom_Line(a.Pnt(), b.Dir());
}

servoce::curve3::curve3 servoce::curve3::interpolate(
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

servoce::curve3::curve3 servoce::curve3::interpolate(
    const std::vector<servoce::point3>& pnts, bool closed)
{
	Handle(TColgp_HArray1OfPnt) _pnts = new TColgp_HArray1OfPnt(1, pnts.size());

	for (unsigned int i = 0; i < pnts.size(); ++i)
		_pnts->SetValue(i + 1, pnts[i].Pnt());

	GeomAPI_Interpolate algo(_pnts, /*_params,*/ closed, 0.0000001);

	algo.Perform();
	return dynamic_cast<Geom_Curve*>(algo.Curve().get());
}

void servoce::curve3::curve3::dump(std::ostream& out) const
{
	Handle(Geom_Curve) h = dynamic_cast<Geom_Curve*>(crv.get());
	BinTools_CurveSet::WriteCurve(h, out);
}

void servoce::curve3::curve3::load(std::istream& in)
{
	Handle(Geom_Curve) h;
	BinTools_CurveSet::ReadCurve (in, h);
	crv = dynamic_cast<Geom_Curve*>(h.get());
}










