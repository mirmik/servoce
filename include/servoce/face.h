#ifndef SERVOCE_SOLID_H
#define SERVOCE_SOLID_H

#include <vector>
#include <servoce/topo.h>
#include <servoce/math3.h>

class BRepPrimAPI_MakeSweep;

namespace servoce {
	namespace prim2d {
		face make_circle(double r);
		face make_polygon(const servoce::point3* pnts, size_t size);
		face make_polygon(const std::vector<servoce::point3>& pnts);

		face make_ngon(double r, int n);
		face make_square(double a, bool center = false);
		face make_rectangle(double a, double b, bool center = false);
	}
	
	struct sweep_face : public face {
		TopoDS_Shape* m_first;
		TopoDS_Shape* m_last;
		sweep_face(BRepPrimAPI_MakeSweep&& builder);
		virtual ~sweep_face();
	
		shape last() { return *m_last; } 
		shape first() { return *m_first; } 
	};

	namespace sweep2d {
		sweep_face make_sweep(const servoce::shape& profile, const servoce::wire& path);
	}
}

#endif