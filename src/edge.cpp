#include <servoce/shape.h>
#include <servoce/edge.h>
#include <servoce/wire.h>
#include <servoce/face.h>

#include <BRep_Tool.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>

#include <GCPnts_AbscissaPoint.hxx>
#include <GCPnts_UniformAbscissa.hxx>

#include <TopoDS_Wire.hxx>
#include <TopAbs.hxx>
#include <assert.h>

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

servoce::face_shape servoce::edge_shape::fill()
{
	assert(Shape().ShapeType() == TopAbs_EDGE);
	return BRepBuilderAPI_MakeFace(Wire_orEdgeToWire()).Face();
}
