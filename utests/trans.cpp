#include <gtest/gtest.h>
#include <servoce/trans.h>

TEST(api, Trans) 
{
	servoce::point3 m(0,0,1);

	auto t = servoce::short_rotate({0,0,1}, {1,0,0});

	EXPECT_TRUE(servoce::point3::early(t(m), servoce::point3(1,0,0)));
}