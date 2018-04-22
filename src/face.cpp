#include <servoce/face.h>

#include <gp_Circ.hxx>
#include <GC_MakeCircle.hxx>

#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>

servoce::face servoce::prim2d::make_circle(double r) { 
	gp_Circ EL ( gp::XOY(), r );
	Handle(Geom_Circle) anCircle = GC_MakeCircle(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle );
	TopoDS_Wire aCircle = BRepBuilderAPI_MakeWire( aEdge );
	return BRepBuilderAPI_MakeFace(aCircle).Face();
}

servoce::face servoce::prim2d::make_polygon(const servoce::point3* pnts, size_t size) {
	BRepBuilderAPI_MakePolygon mk;
	for (int i = 0; i < size; ++i) mk.Add(pnts[i].Pnt());
	mk.Close();
	return BRepBuilderAPI_MakeFace(mk).Face();
} 

servoce::face servoce::prim2d::make_polygon(const std::vector<servoce::point3>& pnts) {
	return make_polygon(pnts.data(), pnts.size());
} 

servoce::face servoce::prim2d::make_ngon(double r, int n) { 
	double angle;
	servoce::point3 pnts[n];
	for (int i = 0; i < n; ++i) {
		angle = 2 * M_PI / n * i;
		pnts[i] = servoce::point3(r*cos(angle), r*sin(angle), 0);
	}
	return make_polygon(pnts, n);
}
