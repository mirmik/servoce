#include <gtest/gtest.h>
#include <servoce/curve3.h>

TEST(api, Curve3) 
{
	servoce::line_curve3({0,0,0}, {10,10,10});

	auto a = servoce::interpolate_curve3({{0,0,0}, {0,0,1}},{{0,0,0}, {0,0,1}},false);
	auto b = servoce::interpolate_curve3({{0,0,0}, {0,0,1}},false);	
}

TEST(line, Curve3) 
{
	auto line = servoce::line_curve3({0,0,0}, {1,0,0});
	auto line2 = servoce::line_curve3({0,0,0}, {10,0,0});	

	EXPECT_EQ(line.d0(0), servoce::point3(0,0,0));
	EXPECT_EQ(line.d0(1), servoce::point3(1,0,0));
	EXPECT_EQ(line2.d0(1), servoce::point3(1,0,0));
}