#ifndef ZENGEOM_BOOLOPS_H
#define ZENGEOM_BOOLOPS_H

#include <vector>
#include <cstdlib>

namespace servoce {
	class shape;
	class solid;
	class wire;
	class face;

	namespace boolops {
		solid make_union(const solid& a, const shape& b);
		solid make_difference(const solid& a, const shape& b);
		solid make_intersect(const solid& a, const shape& b);

		face make_union(const face& a, const shape& b);
		face make_difference(const face& a, const shape& b);
		face make_intersect(const face& a, const shape& b);

		wire make_union(const wire& a, const shape& b);
		wire make_difference(const wire& a, const shape& b);
		wire make_intersect(const wire& a, const shape& b);

		//solid make_union(const std::vector<solid>& vec);
		//solid make_union(const servoce::solid* vec, size_t size);
		solid make_union(const std::vector<const solid*>& vec);
		face make_union(const std::vector<const face*>& vec);

		//solid make_difference(const servoce::solid* vec, size_t size);
		solid make_difference(const std::vector<const solid*>& vec);
		face make_difference(const std::vector<const face*>& vec);

		//solid make_intersect(const servoce::solid* vec, size_t size);
		solid make_intersect(const std::vector<const solid*>& vec);
		face make_intersect(const std::vector<const face*>& vec);
	}
}

#endif 