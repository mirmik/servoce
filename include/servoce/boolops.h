#ifndef ZENGEOM_BOOLOPS_H
#define ZENGEOM_BOOLOPS_H

#include <servoce/topo.h>

namespace servoce {
	namespace boolops {
		solid make_union(const solid& a, const solid& b);
		solid make_difference(const solid& a, const solid& b);
		solid make_intersect(const solid& a, const solid& b);

		face make_union(const face& a, const face& b);
		face make_difference(const face& a, const face& b);
		face make_intersect(const face& a, const face& b);
	}
}

#endif 