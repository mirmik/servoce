#include <servoce/surface.h>
#include <Geom_CylindricalSurface.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom2d_TrimmedCurve.hxx>

#include <TopoDS_Wire.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepLib.hxx>

#include <BSplCLib.hxx>
#include <GeomFill_Pipe.hxx>

#include <BinTools_SurfaceSet.hxx>

servoce::surface::surface servoce::surface::cylinder(double r)
{
	return new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), r);
}

servoce::shape servoce::surface::surface::map(servoce::curve2::curve2& tcrv)
{
	auto mk = BRepBuilderAPI_MakeEdge(tcrv.Curve(), surf);
	TopoDS_Edge edge = mk.Edge();
	BRepLib::BuildCurves3d(edge);
	return edge;
}

servoce::surface::surface servoce::surface::tube(const servoce::curve3::curve3& crv, double r)
{
	GeomFill_Pipe Pipe(crv.Curve(), r);
	Pipe.Perform(1e-6, false, GeomAbs_C1, BSplCLib::MaxDegree(), 1000);

	return Pipe.Surface();
}

void servoce::surface::surface::dump(std::ostream& out) const
{
	Handle(Geom_Surface) h = dynamic_cast<Geom_Surface*>(surf.get());
	BinTools_SurfaceSet::WriteSurface(h, out);
}

void servoce::surface::surface::load(std::istream& in)
{
	Handle(Geom_Surface) h;
	BinTools_SurfaceSet::ReadSurface (in, h);
	surf = dynamic_cast<Geom_Surface*>(h.get());
}