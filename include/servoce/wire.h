#ifndef SERVOCE_WIRE_H
#define SERVOCE_WIRE_H

#include <servoce/topo.h>
#include <vector>

namespace servoce
{
	namespace curve3 {
		class curve3;
	}

	wire_shape make_polysegment(const point3* data, size_t size, bool closed = false);
	wire_shape make_polysegment(const std::vector<point3>& vec, bool closed = false);
	
	shape make_helix(double pitch, double height, double radius, double angle = 0, bool leftHanded = false, bool newStyle = true);
	shape make_long_helix(double pitch, double height, double radius, double angle = 0, bool leftHanded = false);

	/// Сшить wire или edge между собой.
	shape sew(const std::vector<const shape*>& arr);

	curve3::curve3 extract_curve(const shape& wire);
	curve3::curve3 curve_adaptor(const shape& wire);
}

#endif