#ifndef SERVOCE_SOLID_H
#define SERVOCE_SOLID_H

#include <vector>
#include <servoce/topo.h>
#include <servoce/math3.h>

class BRepPrimAPI_MakeSweep;

namespace servoce
{
	//prim2d
	[[deprecated]] shape make_circle(double r);
	[[deprecated]] shape make_circle(double r, double angle);
	[[deprecated]] shape make_polygon(const servoce::point3* pnts, size_t size);
	[[deprecated]] shape make_polygon(const std::vector<servoce::point3>& pnts);
	[[deprecated]] shape make_ngon(double r, int n);
	[[deprecated]] shape make_square(double a, bool center = false);
	[[deprecated]] shape make_rectangle(double a, double b, bool center = false);

	shape circle(double r);
	shape circle(double r, double angle);
	shape polygon(const servoce::point3* pnts, size_t size);
	shape polygon(const std::vector<servoce::point3>& pnts);
	shape ngon(double r, int n);
	shape square(double a, bool center = false);
	shape rectangle(double a, double b, bool center = false);

	//sweep2d
	//shape make_sweep(const servoce::shape& profile, const servoce::shape& path); //Не нужна.
}

#endif