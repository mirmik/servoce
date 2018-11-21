#ifndef SERVOCE_UTIL_MATH_H
#define SERVOCE_UTIL_MATH_H

template <typename T, typename P>
static inline bool early_zero(T a, P prec) {
	return fabs(a) < prec;
}

#endif