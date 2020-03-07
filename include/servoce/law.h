#ifndef SERVOCE_LAW_H
#define SERVOCE_LAW_H

#include <Law_Function.hxx>
#include <GeomFill_SectionLaw.hxx>
#include <GeomFill_LocationLaw.hxx>
#include <GeomFill_TrihedronLaw.hxx>

namespace servoce
{
	class curve3;
	class edge_shape;

	class law_function
	{
		Handle(Law_Function) law;
	public:
		law_function(Handle(Law_Function) law) : law(law) {}
		Handle(Law_Function) Law() { return law; }
		const Handle(Law_Function) Law() const { return law; }
	};

	class law_section
	{
		Handle(GeomFill_SectionLaw) law;
	public:
		law_section(Handle(GeomFill_SectionLaw) law) : law(law) {}
		Handle(GeomFill_SectionLaw) Law() { return law; }
		const Handle(GeomFill_SectionLaw) Law() const { return law; }
	};

	class law_location
	{
		Handle(GeomFill_LocationLaw) law;
	public:
		law_location(Handle(GeomFill_LocationLaw) law) : law(law) {}
		Handle(GeomFill_LocationLaw) Law() { return law; }
		const Handle(GeomFill_LocationLaw) Law() const { return law; }
	};

	class law_trihedron
	{
		Handle(GeomFill_TrihedronLaw) law;
	public:
		law_trihedron(Handle(GeomFill_TrihedronLaw) law) : law(law) {}
		Handle(GeomFill_TrihedronLaw) Law() { return law; }
		const Handle(GeomFill_TrihedronLaw) Law() const { return law; }
	};

	//Handle(GeomFill_Trihedron) TrihedronByName(const std::string& triname);


	law_function law_constant_function(double radius, std::pair<double, double> range);

	law_section law_evolved_section(const servoce::curve3& crv, const law_function& func);

	law_location law_spine_and_trihedron(const servoce::curve3& crv, const law_trihedron& triname);
	law_location law_spine_and_trihedron(const servoce::edge_shape& crv, const law_trihedron& triname);

	law_trihedron law_corrected_frenet_trihedron();
	law_trihedron law_frenet_trihedron();
}

#endif