#ifndef SERVOCE_SOLID_H
#define SERVOCE_SOLID_H

#include <vector>
#include <servoce/topo.h>
#include <servoce/math3.h>

class BRepPrimAPI_MakeSweep;

namespace servoce
{
	//prim2d
	shape make_circle(double r);
	shape make_polygon(const servoce::point3* pnts, size_t size);
	shape make_polygon(const std::vector<servoce::point3>& pnts);
	shape make_ngon(double r, int n);
	shape make_square(double a, bool center = false);
	shape make_rectangle(double a, double b, bool center = false);

	//sweep2d
	//shape make_sweep(const servoce::shape& profile, const servoce::shape& path); //Не нужна.
}

#endif