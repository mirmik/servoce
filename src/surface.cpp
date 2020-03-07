#include <servoce/surface.h>
#include <servoce/law.h>
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

#include <GeomFill_Sweep.hxx>

servoce::surface servoce::cylinder_surface(double r)
{
	return new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), r);
}

servoce::shape servoce::surface::map(servoce::curve2::curve2& tcrv)
{
	auto mk = BRepBuilderAPI_MakeEdge(tcrv.Curve(), surf);
	TopoDS_Edge edge = mk.Edge();
	BRepLib::BuildCurves3d(edge);
	return edge;
}

servoce::surface servoce::tube_surface(const servoce::curve3& crv, double r)
{
	GeomFill_Pipe Pipe(crv.Curve(), r);
	Pipe.Perform(1e-6, false, GeomAbs_C1, BSplCLib::MaxDegree(), 1000);

	return Pipe.Surface();
}

void servoce::surface::dump(std::ostream& out) const
{
	Handle(Geom_Surface) h = dynamic_cast<Geom_Surface*>(surf.get());
	BinTools_SurfaceSet::WriteSurface(h, out);
}

void servoce::surface::load(std::istream& in)
{
	Handle(Geom_Surface) h;
	BinTools_SurfaceSet::ReadSurface (in, h);
	surf = dynamic_cast<Geom_Surface*>(h.get());
}

servoce::surface servoce::sweep_surface(const servoce::law_section& slaw, const servoce::law_location& llaw,
	double tol, int cont, int maxdegree, int maxsegm) 
{
	// Кинематическое построение поверхности по законам сечения и расположения  

	GeomFill_Sweep algo(llaw.Law());
	algo.SetTolerance(tol);
	algo.Build(slaw.Law(), GeomFill_Location, (GeomAbs_Shape)cont, maxdegree, maxsegm);
	//algo.Build(slaw.Law(), GeomFill_Section, (GeomAbs_Shape)cont, maxdegree, maxsegm);

	return algo.Surface();
}


servoce::curve3 servoce::surface::v_iso_curve(double parameter) 
{
	return Surface()->VIso(parameter);
}

servoce::curve3 servoce::surface::u_iso_curve(double parameter) 
{
	return Surface()->UIso(parameter);
}