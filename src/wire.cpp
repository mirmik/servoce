#include <servoce/wire.h>
#include <local/util.h>

#include <exception>

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>

#include <TopoDS_Wire.hxx>
#include <TopoDS_Shape.hxx>
#include <BRepLib.hxx>

#include <gp_Circ.hxx>
#include <GC_MakeCircle.hxx>

#include <gp_Lin2d.hxx>
#include <GCE2d_MakeSegment.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Geom_ConicalSurface.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
//#include <Handle_TColgp_HArray1OfPnt.hxx>
#include <TColStd_HArray1OfBoolean.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <TColgp_Array1OfVec.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <BRep_Tool.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <gxx/print.h>

servoce::face servoce::wire::to_face() {
	return BRepBuilderAPI_MakeFace(Wire()).Face();
}

servoce::wire servoce::curve::make_segment(const servoce::point3& a, const servoce::point3& b) {
	return BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(a.Pnt(), b.Pnt())).Wire();
}

servoce::wire servoce::curve::make_polysegment(const std::vector<servoce::point3>& pnts, bool closed) {
	if (pnts.size() <= 1) 
		throw std::logic_error("Need at least two points for polysegment");

	BRepBuilderAPI_MakeWire mkWire;
	for (int i = 0; i < pnts.size() - 1; ++i) {
		mkWire.Add(BRepBuilderAPI_MakeEdge(pnts[i].Pnt(), pnts[i+1].Pnt()));
	}
	if (closed) mkWire.Add(BRepBuilderAPI_MakeEdge(pnts[pnts.size()-1].Pnt(), pnts[0].Pnt()));
	return mkWire.Wire(); 
}

//Взято в коде FreeCad.
servoce::wire servoce::curve::make_helix(
	double pitch, double height, double radius, 
	double angle, bool leftHanded, bool newStyle
) {
	if (fabs(pitch) < Precision::Confusion())
		Standard_Failure::Raise("Pitch of helix too small");

	if (fabs(height) < Precision::Confusion())
		Standard_Failure::Raise("Height of helix too small");

	if ((height > 0 && pitch < 0) || (height < 0 && pitch > 0))
		Standard_Failure::Raise("Pitch and height of helix not compatible");

	gp_Ax2 cylAx2(gp_Pnt(0.0,0.0,0.0) , gp::DZ());
	Handle(Geom_Surface) surf;
	if (angle < Precision::Confusion()) {
		if (radius < Precision::Confusion())
			Standard_Failure::Raise("Radius of helix too small");
		surf = new Geom_CylindricalSurface(cylAx2, radius);
	}
	else {
		angle = to_radian(angle);
		if (angle < Precision::Confusion())
			Standard_Failure::Raise("Angle of helix too small");
		surf = new Geom_ConicalSurface(gp_Ax3(cylAx2), angle, radius);
	}

	gp_Pnt2d aPnt(0, 0);
	gp_Dir2d aDir(2. * M_PI, pitch);
	Standard_Real coneDir = 1.0;
	if (leftHanded) {
		aDir.SetCoord(-2. * M_PI, pitch);
		coneDir = -1.0;
	}
	gp_Ax2d aAx2d(aPnt, aDir);

	Handle(Geom2d_Line) line = new Geom2d_Line(aAx2d);
	gp_Pnt2d beg = line->Value(0);
	gp_Pnt2d end = line->Value(sqrt(4.0*M_PI*M_PI+pitch*pitch)*(height/pitch));

	if (newStyle) {
		// See discussion at 0001247: Part Conical Helix Height/Pitch Incorrect
		if (angle >= Precision::Confusion()) {
			// calculate end point for conical helix
			Standard_Real v = height / cos(angle);
			Standard_Real u = coneDir * (height/pitch) * 2.0 * M_PI;
			gp_Pnt2d cend(u, v);
			end = cend;
		}
	}

	Handle(Geom2d_TrimmedCurve) segm = GCE2d_MakeSegment(beg , end);

	TopoDS_Edge edgeOnSurf = BRepBuilderAPI_MakeEdge(segm , surf);
	TopoDS_Wire wire = BRepBuilderAPI_MakeWire(edgeOnSurf);
	BRepLib::BuildCurves3d(wire);
	return wire;
}

//***********
// makeLongHelix is a workaround for an OCC problem found in helices with more than
// some magic number of turns.  See Mantis #0954.
//***********
servoce::wire servoce::curve::make_long_helix(double pitch, double height,
									  double radius, double angle,
									  bool leftHanded)
{
	if (pitch < Precision::Confusion())
		Standard_Failure::Raise("Pitch of helix too small");

	if (height < Precision::Confusion())
		Standard_Failure::Raise("Height of helix too small");

	gp_Ax2 cylAx2(gp_Pnt(0.0,0.0,0.0) , gp::DZ());
	Handle(Geom_Surface) surf;
	Standard_Boolean isCylinder;

	if (angle < Precision::Confusion()) {   // Cylindrical helix
		if (radius < Precision::Confusion())
			Standard_Failure::Raise("Radius of helix too small");
		surf= new Geom_CylindricalSurface(cylAx2, radius);
		isCylinder = true;
	}
	else {                                  // Conical helix
		//angle = to_radian(angle);
		if (angle < Precision::Confusion())
			Standard_Failure::Raise("Angle of helix too small");
		surf = new Geom_ConicalSurface(gp_Ax3(cylAx2), angle, radius);
		isCylinder = false;
	}

	Standard_Real turns = height/pitch;
	unsigned long wholeTurns = floor(turns);
	Standard_Real partTurn = turns - wholeTurns;

	gp_Pnt2d aPnt(0, 0);
	gp_Dir2d aDir(2. * M_PI, pitch);
	Standard_Real coneDir = 1.0;
	if (leftHanded) {
		aDir.SetCoord(-2. * M_PI, pitch);
		coneDir = -1.0;
	}
	gp_Ax2d aAx2d(aPnt, aDir);
	Handle(Geom2d_Line) line = new Geom2d_Line(aAx2d);
	gp_Pnt2d beg = line->Value(0);
	gp_Pnt2d end;
	Standard_Real u,v;
	BRepBuilderAPI_MakeWire mkWire;
	Handle(Geom2d_TrimmedCurve) segm;
	TopoDS_Edge edgeOnSurf;

	for (unsigned long i = 0; i < wholeTurns; i++) {
		if (isCylinder) {
			end = line->Value(sqrt(4.0*M_PI*M_PI+pitch*pitch)*(i+1));
		}
		else {
			u = coneDir * (i+1) * 2.0 * M_PI;
			v = ((i+1) * pitch) / cos(angle);
			end = gp_Pnt2d(u, v);
		}
		segm = GCE2d_MakeSegment(beg , end);
		edgeOnSurf = BRepBuilderAPI_MakeEdge(segm , surf);
		mkWire.Add(edgeOnSurf);
		beg = end;
	}

	if (partTurn > Precision::Confusion()) {
		if (isCylinder) {
			end = line->Value(sqrt(4.0*M_PI*M_PI+pitch*pitch)*turns);
		}
		else {
			u = coneDir * turns * 2.0 * M_PI;
			v = height / cos(angle);
			end = gp_Pnt2d(u, v);
		}
		segm = GCE2d_MakeSegment(beg , end);
		edgeOnSurf = BRepBuilderAPI_MakeEdge(segm , surf);
		mkWire.Add(edgeOnSurf);
	}

	TopoDS_Wire wire = mkWire.Wire();
	BRepLib::BuildCurves3d(wire);
	return wire;
}

servoce::wire servoce::curve::make_interpolate(const std::vector<servoce::point3>& pnts, const std::vector<servoce::vector3>& tang, bool closed) {
	Handle(TColgp_HArray1OfPnt) _pnts = new TColgp_HArray1OfPnt(1, pnts.size());
	for (int i = 0; i < pnts.size(); ++i) _pnts->SetValue(i + 1, pnts[i].Pnt());

	/*Handle(TColStd_HArray1OfReal) _params = new TColStd_HArray1OfReal(1, pnts.size());
	for (int i = 0; i < pnts.size(); ++i) _params->SetValue(i + 1, params[i]);*/

	GeomAPI_Interpolate algo(_pnts, /*_params,*/ closed, 0.0000001);
	
	if (tang.size()) {
		TColgp_Array1OfVec _tang(1, tang.size());
		Handle(TColStd_HArray1OfBoolean) _bools = new TColStd_HArray1OfBoolean(1, tang.size());
		for (int i = 0; i < pnts.size(); ++i) _tang.SetValue(i + 1, tang[i].Vec());
		for (int i = 0; i < pnts.size(); ++i) _bools->SetValue(i + 1, tang[i] != servoce::vector3(0,0,0));
		algo.Load(_tang, _bools);
	}
	
	algo.Perform();
	return BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(algo.Curve())).Wire();
}

servoce::wire servoce::curve::make_interpolate(const std::vector<servoce::point3>& pnts, bool closed) {
	Handle(TColgp_HArray1OfPnt) _pnts = new TColgp_HArray1OfPnt(1, pnts.size());
	for (int i = 0; i < pnts.size(); ++i) _pnts->SetValue(i + 1, pnts[i].Pnt());

	GeomAPI_Interpolate algo(_pnts, /*_params,*/ closed, 0.0000001);
	
	algo.Perform();
	return BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(algo.Curve())).Wire();
}

servoce::wire servoce::curve::make_complex_wire(const std::vector<const servoce::wire*>& arr) {
	BRepBuilderAPI_MakeWire mk;
	for (auto* ptr : arr) {
		mk.Add(ptr->Wire());
	}
	return mk.Wire();
}

servoce::wire servoce::curve::make_circle(double r, double a, double b) { 
	gp_Circ EL ( gp::XOY(), r );
	Handle(Geom_Circle) anCircle = GC_MakeCircle(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle, a, b );
	TopoDS_Wire aCircle = BRepBuilderAPI_MakeWire( aEdge );
	return aCircle;
}

servoce::wire servoce::curve::make_circle(double r) { 
	gp_Circ EL ( gp::XOY(), r );
	Handle(Geom_Circle) anCircle = GC_MakeCircle(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle);
	TopoDS_Wire aCircle = BRepBuilderAPI_MakeWire( aEdge );
	return aCircle;
}


servoce::wire servoce::curve::simplify_with_bspline(const servoce::wire& wr) {
	TopExp_Explorer explorer(wr.Shape(), TopAbs_EDGE);
	TopoDS_Edge edg = TopoDS::Edge(explorer.Current());


	return BRepBuilderAPI_MakeWire(edg).Shape();
}