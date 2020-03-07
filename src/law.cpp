#include <servoce/law.h>
#include <servoce/curve3.h>
#include <servoce/edge.h>

#include <Law_Constant.hxx>
#include <GeomFill_EvolvedSection.hxx>

#include <GeomFill_Trihedron.hxx>
#include <GeomFill_CurveAndTrihedron.hxx>

#include <GeomFill_CorrectedFrenet.hxx>
#include <GeomFill_Frenet.hxx>

#include <map>

using namespace servoce;


/*Handle(GeomFill_Trihedron) servoce::TrihedronByName(const std::string& triname)
{
	Handle(GeomFill_Trihedron) tri;

	std::map<std::string, GeomFill_Trihedron> map =
	{
		{ "corrected_frenet", GeomFill_IsCorrectedFrenet },
		{ "fixed", GeomFill_IsFixed },
		{ "frenet", GeomFill_IsFrenet },
		{ "constant_normal", GeomFill_IsConstantNormal },
		{ "darboux", GeomFill_IsDarboux },
		{ "guide_ac", GeomFill_IsGuideAC },
		{ "guide_plan", GeomFill_IsGuidePlan },
		{ "guide_ac_with_contact", GeomFill_IsGuideACWithContact },
		{ "guide_plan_with_contact", GeomFill_IsGuidePlanWithContact },
		{ "discrete_trihedron", GeomFill_IsDiscreteTrihedron }
	};

	try
	{
		tri = new GeomFill_Trihedron(map.at(triname));
	}

	catch (...)
	{
		throw std::runtime_error("undefined trihedron");
	}

	return tri;
}*/

law_function servoce::law_constant_function(double radius, std::pair<double, double> range)
{
	Handle(Law_Constant) aFunc = new Law_Constant();
	aFunc->Set(radius, range.first, range.second);
	return (Handle(Law_Function)) aFunc;
}

law_section servoce::law_evolved_section(const servoce::curve3& crv, const law_function& func)
{
	return (Handle(GeomFill_SectionLaw)) new GeomFill_EvolvedSection(crv.Curve(), func.Law());
}

law_location servoce::law_spine_and_trihedron(const servoce::edge_shape& crv, const law_trihedron& trilaw)
{
	Handle(GeomFill_LocationLaw) aLoc = new GeomFill_CurveAndTrihedron(trilaw.Law());
	aLoc->SetCurve (crv.HCurveAdaptor());
	return aLoc;
}

law_location servoce::law_spine_and_trihedron(const servoce::curve3& crv, const law_trihedron& trilaw)
{
	Handle(GeomFill_LocationLaw) aLoc = new GeomFill_CurveAndTrihedron(trilaw.Law());
	aLoc->SetCurve (crv.HCurveAdaptor());
	return aLoc;
}

law_trihedron servoce::law_corrected_frenet_trihedron() 
{
	return (Handle(GeomFill_TrihedronLaw)) new GeomFill_CorrectedFrenet;
}

law_trihedron servoce::law_frenet_trihedron() 
{
	return (Handle(GeomFill_TrihedronLaw)) new GeomFill_Frenet;
}