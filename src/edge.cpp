#include <servoce/topo.h>
#include <servoce/wire.h>

#include <BRep_Tool.hxx>

std::pair<double,double> servoce::edge_shape::range() 
{
	double first;
	double last; 

	BRep_Tool::Range(Edge(), first, last);

	return { first, last };
}

double servoce::edge_shape::length() 
{
	
}
