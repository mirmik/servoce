#ifndef SERVOCE_WIRE_H
#define SERVOCE_WIRE_H

#include <servoce/topo.h>
#include <vector>

namespace servoce
{
	shape make_segment(const point3& a, const point3& b);
	shape make_polysegment(const point3* data, size_t size, bool closed = false);
	shape make_polysegment(const std::vector<point3>& vec, bool closed = false);

	shape make_interpolate(const std::vector<point3>& pnts, bool closed = false);
	shape make_interpolate(const std::vector<point3>& pnts, const vector3& atang, const vector3& btang, bool closed = false);
	shape make_interpolate(const std::vector<point3>& pnts, const std::vector<vector3>& tang, bool closed = false);

	//shape make_arc_by_points(const point3& a, const point3& b, const point3& c);

	shape circle_arc(const point3& p1, const point3& p2, const point3& p3);
	
	shape make_helix(double pitch, double height, double radius, double angle = 0, bool leftHanded = false, bool newStyle = true);
	shape make_long_helix(double pitch, double height, double radius, double angle = 0, bool leftHanded = false);

	/// Сшить wire или edge между собой.
	shape sew(const std::vector<const shape*>& arr);
}

#endif