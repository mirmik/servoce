#ifndef SERVOCE_WIRE_H
#define SERVOCE_WIRE_H

#include <servoce/topo.h>
#include <vector>

namespace servoce
{
	namespace curve3 {
		class curve3;
	}

	edge_shape make_segment(const point3& a, const point3& b);
	wire_shape make_polysegment(const point3* data, size_t size, bool closed = false);
	wire_shape make_polysegment(const std::vector<point3>& vec, bool closed = false);

	edge_shape make_interpolate(const std::vector<point3>& pnts, bool closed = false);
	edge_shape make_interpolate(const std::vector<point3>& pnts, const vector3& atang, const vector3& btang, bool closed = false);
	edge_shape make_interpolate(const std::vector<point3>& pnts, const std::vector<vector3>& tang, bool closed = false);

	//shape make_arc_by_points(const point3& a, const point3& b, const point3& c);

	edge_shape bezier(const std::vector<point3>& pnts);
	edge_shape bezier(const std::vector<point3>& pnts, const std::vector<double>& weights);

	edge_shape bspline(
		const std::vector<point3>& poles,
		const std::vector<double>& knots,
		const std::vector<int>& multiplicities,
		int degree,
		bool periodic=false
	);

	edge_shape bspline(
		const std::vector<point3>& poles,
		const std::vector<double>& weights,
		const std::vector<double>& knots,
		const std::vector<int>& multiplicities,
		int degree,
		bool periodic=false,
		bool check_rational=true 
	);

	edge_shape circle_arc(const point3& p1, const point3& p2, const point3& p3);
	
	shape make_helix(double pitch, double height, double radius, double angle = 0, bool leftHanded = false, bool newStyle = true);
	shape make_long_helix(double pitch, double height, double radius, double angle = 0, bool leftHanded = false);

	/// Сшить wire или edge между собой.
	shape sew(const std::vector<const shape*>& arr);

	edge_shape make_edge(const servoce::curve3::curve3& crv);
	edge_shape make_edge(const servoce::curve3::curve3& crv, double strt, double fini);

	curve3::curve3 extract_curve(const shape& wire);
	curve3::curve3 curve_adaptor(const shape& wire);
}

#endif