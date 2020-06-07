#ifndef SERVOCE_COLOR_H
#define SERVOCE_COLOR_H

#include <Quantity_Color.hxx>

namespace pybind11
{
	class list;
	class tuple;
	class object;
}

namespace servoce
{
	struct color
	{
		double r=0, g=0, b=0, a=0;
		
		constexpr color() : color(0.6, 0.6, 0.8) {}
		constexpr color(const color& oth) : color(oth.r, oth.g, oth.b, oth.a) {}
		constexpr color(double r, double g, double b) : r(r), g(g), b(b) {}
		constexpr color(double r, double g, double b, double a) : r(r), g(g), b(b), a(a) {}
		color(const pybind11::list&);
		color(const pybind11::tuple&);

		color(const Quantity_Color& clr) : r(clr.Red()), g(clr.Green()), b(clr.Blue()) {}
		Quantity_Color Color() const { return Quantity_Color(r, g, b, Quantity_TOC_RGB); }
	};

	static constexpr color white  { 1, 1, 1 };
	static constexpr color black  { 0, 0, 0 };
	static constexpr color red    { 1, 0, 0 };
	static constexpr color green  { 0, 1, 0 };
	static constexpr color blue   { 0, 0, 1 };
	static constexpr color yellow { 1, 1, 0 };
	static constexpr color gray   { 0.5, 0.5, 0.5 };
	static constexpr color mech   { 0.6, 0.6, 0.8 };
}

#endif