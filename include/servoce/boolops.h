#ifndef ZENGEOM_BOOLOPS_H
#define ZENGEOM_BOOLOPS_H

#include <vector>
#include <cstdlib>

namespace servoce {
	class solid;
	class face;

	namespace boolops {
		solid make_union(const solid& a, const solid& b);
		solid make_difference(const solid& a, const solid& b);
		solid make_intersect(const solid& a, const solid& b);

		face make_union(const face& a, const face& b);
		face make_difference(const face& a, const face& b);
		face make_intersect(const face& a, const face& b);

		//solid make_union(const std::vector<solid>& vec);
		solid make_union(const servoce::solid* vec, size_t size);
		solid make_union(const std::vector<const solid*>& vec);
	}
}

#endif 