#include <servoce/wire.h>
#include <local/util.h>

#include <exception>

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>

#include <TopoDS_Wire.hxx>
#include <TopoDS_Shape.hxx>
#include <BRepLib.hxx>

#include <gp_Lin2d.hxx>
#include <GCE2d_MakeSegment.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Geom_ConicalSurface.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>

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
        angle = to_radian(angle);
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


/*servoce::shape servoce::curve::make_thread(double pitch,
                                   double depth,
                                   double height,
                                   double radius)
{
    if (pitch < Precision::Confusion())
        Standard_Failure::Raise("Pitch of thread too small");

    if (depth < Precision::Confusion())
        Standard_Failure::Raise("Depth of thread too small");

    if (height < Precision::Confusion())
        Standard_Failure::Raise("Height of thread too small");

    if (radius < Precision::Confusion())
        Standard_Failure::Raise("Radius of thread too small");

    //Threading : Create Surfaces
    gp_Ax2 cylAx2(gp_Pnt(0.0,0.0,0.0) , gp::DZ());
    Handle(Geom_CylindricalSurface) aCyl1 = new Geom_CylindricalSurface(cylAx2 , radius);
    Handle(Geom_CylindricalSurface) aCyl2 = new Geom_CylindricalSurface(cylAx2 , radius+depth);

    //Threading : Define 2D Curves
    gp_Pnt2d aPnt(2. * M_PI , height / 2.);
    gp_Dir2d aDir(2. * M_PI , height / 4.);
    gp_Ax2d aAx2d(aPnt , aDir);

    Standard_Real aMajor = 2. * M_PI;
    Standard_Real aMinor = pitch;

    Handle(Geom2d_Ellipse) anEllipse1 = new Geom2d_Ellipse(aAx2d , aMajor , aMinor);
    Handle(Geom2d_Ellipse) anEllipse2 = new Geom2d_Ellipse(aAx2d , aMajor , aMinor / 4);

    Handle(Geom2d_TrimmedCurve) aArc1 = new Geom2d_TrimmedCurve(anEllipse1 , 0 , M_PI);
    Handle(Geom2d_TrimmedCurve) aArc2 = new Geom2d_TrimmedCurve(anEllipse2 , 0 , M_PI);

    gp_Pnt2d anEllipsePnt1 = anEllipse1->Value(0);
    gp_Pnt2d anEllipsePnt2 = anEllipse1->Value(M_PI);

    Handle(Geom2d_TrimmedCurve) aSegment = GCE2d_MakeSegment(anEllipsePnt1 , anEllipsePnt2);

    //Threading : Build Edges and Wires
    TopoDS_Edge aEdge1OnSurf1 = BRepBuilderAPI_MakeEdge(aArc1 , aCyl1);
    TopoDS_Edge aEdge2OnSurf1 = BRepBuilderAPI_MakeEdge(aSegment , aCyl1);
    TopoDS_Edge aEdge1OnSurf2 = BRepBuilderAPI_MakeEdge(aArc2 , aCyl2);
    TopoDS_Edge aEdge2OnSurf2 = BRepBuilderAPI_MakeEdge(aSegment , aCyl2);

    TopoDS_Wire threadingWire1 = BRepBuilderAPI_MakeWire(aEdge1OnSurf1 , aEdge2OnSurf1);
    TopoDS_Wire threadingWire2 = BRepBuilderAPI_MakeWire(aEdge1OnSurf2 , aEdge2OnSurf2);

    BRepLib::BuildCurves3d(threadingWire1);
    BRepLib::BuildCurves3d(threadingWire2);

    BRepOffsetAPI_ThruSections aTool(Standard_True);

    aTool.AddWire(threadingWire1);
    aTool.AddWire(threadingWire2);
    aTool.CheckCompatibility(Standard_False);

    return aTool.Shape();
}*/
