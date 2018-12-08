#ifndef SERVOCE_SOLID_H
#define SERVOCE_SOLID_H

#include <vector>
#include <servoce/topo.h>
#include <servoce/math3.h>

class BRepPrimAPI_MakeSweep;

namespace servoce
{
	//prim2d
	shape circle(double r);
	shape circle(double r, double angle);
	shape circle(double r, double a1, double a2);

	shape circle_wire(double r);
	shape circle_wire(double r, double angle);
	shape circle_wire(double r, double a1, double a2);
	
	shape polygon(const servoce::point3* pnts, size_t size);
	shape polygon(const std::vector<servoce::point3>& pnts);
	shape ngon(double r, int n);
	shape square(double a, bool center = false);
	shape rectangle(double a, double b, bool center = false);

	//sweep2d
	//shape make_sweep(const servoce::shape& profile, const servoce::shape& path); //Не нужна.
}

#endif