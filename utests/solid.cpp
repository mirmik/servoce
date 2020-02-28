#include <gtest/gtest.h>
#include <servoce/solid.h>
#include <servoce/face.h>
#include <servoce/edge.h>

TEST(box, Solid) 
{
	auto a = servoce::box(10,10,20);

	EXPECT_EQ(a.faces().size(), 6);
	EXPECT_EQ(a.edges().size(), 24);
}