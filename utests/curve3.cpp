#include <gtest/gtest.h>
#include <servoce/curve3.h>

TEST(api, Curve3) 
{
	servoce::curve3::line({0,0,0}, {10,10,10});

	auto a = servoce::curve3::interpolate({{0,0,0}, {0,0,1}},{{0,0,0}, {0,0,1}},false);
	auto b = servoce::curve3::interpolate({{0,0,0}, {0,0,1}},false);	
}

TEST(line, Curve3) 
{
	auto line = servoce::curve3::line({0,0,0}, {1,0,0});
	auto line2 = servoce::curve3::line({0,0,0}, {10,0,0});	

	EXPECT_EQ(line.d0(0), servoce::point3(0,0,0));
	EXPECT_EQ(line.d0(1), servoce::point3(1,0,0));
	EXPECT_EQ(line2.d0(1), servoce::point3(1,0,0));
}