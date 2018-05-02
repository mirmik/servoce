#ifndef SERVOCE_WIRE_H
#define SERVOCE_WIRE_H

#include <servoce/topo.h>
#include <servoce/math3.h>
#include <vector>

namespace servoce {
	namespace curve {
		wire make_segment(const point3& a, const point3& b);
		wire make_polysegment(const std::vector<point3>& vec, bool closed = false);
		
		wire make_interpolate(const std::vector<point3>& pnts, bool closed);
		//wire make_interpolate(const std::vector<point3>& pnts, const vector3& atang, const vector3& btang);
		wire make_interpolate(const std::vector<point3>& pnts, const std::vector<vector3>& tang, bool closed);

		wire make_arc_by_points(const point3& a, const point3& b, const point3& c);
		
		wire make_circle(double r, double a, double b);
		wire make_circle(double r);

		wire make_helix(double pitch, double height, double radius, double angle = 0, bool leftHanded = false, bool newStyle = true);
		wire make_long_helix(double pitch, double height, double radius, double angle = 0, bool leftHanded = false);
	
		wire make_complex_wire(const std::vector<const wire*>& arr);

		wire simplify_with_bspline(const wire& wr);
	}
}

#endif