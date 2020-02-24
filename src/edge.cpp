#include <servoce/shape.h>
#include <servoce/edge.h>
#include <servoce/wire.h>

#include <BRep_Tool.hxx>
#include <BRepAdaptor_Curve.hxx>

#include <GCPnts_AbscissaPoint.hxx>
#include <GCPnts_UniformAbscissa.hxx>

std::pair<double,double> servoce::edge_shape::range() 
{
	double first;
	double last; 

	BRep_Tool::Range(Edge(), first, last);

	return { first, last };
}

BRepAdaptor_Curve servoce::edge_shape::AdaptorCurve() const 
{
	return BRepAdaptor_Curve(Edge());
}
