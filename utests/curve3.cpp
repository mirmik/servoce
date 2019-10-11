#include <gtest/gtest.h>
#include <servoce/curve3.h>

TEST(api, Curve3) 
{
	auto a = servoce::curve3::interpolate({{0,0,0}, {0,0,1}},{{0,0,0}, {0,0,1}},false);
	auto b = servoce::curve3::interpolate({{0,0,0}, {0,0,1}},false);
}
