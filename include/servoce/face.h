#ifndef SERVOCE_SOLID_H
#define SERVOCE_SOLID_H

#include <vector>
#include <servoce/topo.h>

class BRepPrimAPI_MakeSweep;

namespace servoce
{
	//prim2d
	shape circle(double r, bool wire = false);
	shape circle(double r, double angle, bool wire = false);
	shape circle(double r, double a1, double a2, bool wire = false);

	shape ellipse(double r1, double r2, bool wire = false);
	shape ellipse(double r1, double r2, double a1, double a2, bool wire = false);

	
	shape polygon(const servoce::point3* pnts, size_t size);
	shape polygon(const std::vector<servoce::point3>& pnts);
	shape ngon(double r, int n, bool wire = false);
	shape square(double a, bool center = false, bool wire = false);
	shape rectangle(double a, double b, bool center = false, bool wire = false);

	shape textshape(const std::string& text, const std::string fontpath, size_t size);

	shape fill(const std::vector<servoce::shape*>& arr);

	//sweep2d
	//shape make_sweep(const servoce::shape& profile, const servoce::shape& path); //Не нужна.
}

#endif