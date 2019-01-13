#include <servoce/surface.h>
#include <Geom_CylindricalSurface.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom2d_TrimmedCurve.hxx>

#include <TopoDS_Wire.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepLib.hxx>

#include <nos/print.h>
#include <nos/trace.h>

servoce::surface::surface servoce::surface::cylinder(double r) 
{
	return new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0,0,0), gp_Dir(0,0,1)), r);
}

servoce::shape servoce::surface::surface::map(servoce::curve2::curve2& tcrv) 
{
	TRACE();
	auto mk = BRepBuilderAPI_MakeEdge(tcrv.Curve(), surf);
	TopoDS_Edge edge = mk.Edge();
	//nos::println("servoce::surface::surface::map", mk.IsDone());
	//TopoDS_Wire threadingWire1 = BRepBuilderAPI_MakeWire(mk.Edge());
	nos::println("build3d");
	BRepLib::BuildCurves3d(edge);
	nos::println("build3d..ok");
	return edge;
}