#ifndef SERVOCE_BOOLOPS_H
#define SERVOCE_BOOLOPS_H

#include <vector>
#include <cstdlib>

namespace servoce
{
	class shape;

	shape make_union(const shape& a, const shape& b);
	shape make_difference(const shape& a, const shape& b);
	shape make_intersect(const shape& a, const shape& b);

	shape make_union(const std::vector<const shape*>& vec);
	shape make_difference(const std::vector<const shape*>& vec);
	shape make_intersect(const std::vector<const shape*>& vec);
}

#endif