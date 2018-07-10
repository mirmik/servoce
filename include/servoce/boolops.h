#ifndef ZENGEOM_BOOLOPS_H
#define ZENGEOM_BOOLOPS_H

#include <vector>
#include <cstdlib>

namespace servoce {
	class shape;

	shape make_union(const shape& a, const shape& b);
	shape make_difference(const shape& a, const shape& b);
	shape make_intersect(const shape& a, const shape& b);

		/*face make_union(const face& a, const shape& b);
		face make_difference(const face& a, const shape& b);
		face make_intersect(const face& a, const shape& b);

		wire make_union(const wire& a, const shape& b);
		wire make_difference(const wire& a, const shape& b);
		wire make_intersect(const wire& a, const shape& b);*/

	shape make_union(const std::vector<const shape*>& vec);
	shape make_difference(const std::vector<const shape*>& vec);
	shape make_intersect(const std::vector<const shape*>& vec);
		
		//solid make_union(const servoce::solid* vec, size_t size);
		/*solid make_union(const std::vector<const solid*>& vec);
		face make_union(const std::vector<const face*>& vec);

		//solid make_difference(const servoce::solid* vec, size_t size);
		face make_difference(const std::vector<const face*>& vec);

		//solid make_intersect(const servoce::solid* vec, size_t size);
		face make_intersect(const std::vector<const face*>& vec);*/
	
}

#endif 