#include <servoce/face.h>

#include <gp_Circ.hxx>
#include <GC_MakeCircle.hxx>

#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>

servoce::face servoce::prim2d::make_circle(double r) { 
	gp_Circ EL ( gp::XOY(), r );
	Handle(Geom_Circle) anCircle = GC_MakeCircle(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle );
	TopoDS_Wire aCircle = BRepBuilderAPI_MakeWire( aEdge );
	return BRepBuilderAPI_MakeFace(aCircle).Face();
}
