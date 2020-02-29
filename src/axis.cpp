#include <servoce/axis.h>

#include <AIS_Axis.hxx>
#include <Geom_Axis1Placement.hxx>

std::shared_ptr<servoce::interactive_object> servoce::axis::produce_interactive() 
{
	auto gax = new Geom_Axis1Placement(Ax);
	auto ais = new AIS_Axis(gax);
	return std::make_shared<servoce::interactive_object>(ais);
}

servoce::axis servoce::axis::transform(const transformation& trans) const 
{
	auto ax = Ax.Transformed(*trans.trsf);
	return ax;
}