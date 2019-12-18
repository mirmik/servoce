#include <servoce/wire.h>
#include <servoce/curve3.h>
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
#include <GC_MakeArcOfCircle.hxx>

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
#include <Geom_BezierCurve.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <BRep_Tool.hxx>
#include <BRepAdaptor_Curve.hxx>

servoce::shape servoce::shape::infill_face()
{
	return BRepBuilderAPI_MakeFace(Wire()).Face();
}

servoce::edge_shape servoce::make_segment(const servoce::point3& a, const servoce::point3& b)
{
	return BRepBuilderAPI_MakeEdge(a.Pnt(), b.Pnt()).Edge();
}

servoce::wire_shape servoce::make_polysegment(const std::vector<servoce::point3>& pnts, bool closed)
{
	if (pnts.size() <= 1)
		throw std::logic_error("Need at least two points for polysegment");

	BRepBuilderAPI_MakeWire mkWire;

	for (unsigned int i = 0; i < pnts.size() - 1; ++i)
	{
		mkWire.Add(BRepBuilderAPI_MakeEdge(pnts[i].Pnt(), pnts[i + 1].Pnt()));
	}

	if (closed) mkWire.Add(BRepBuilderAPI_MakeEdge(pnts[pnts.size() - 1].Pnt(), pnts[0].Pnt()));

	return mkWire.Wire();
}

//Взято в коде FreeCad.
servoce::shape servoce::make_helix(
    double pitch, double height, double radius,
    double angle, bool leftHanded, bool newStyle
)
{
	if (fabs(pitch) < Precision::Confusion())
		Standard_Failure::Raise("Pitch of helix too small");

	if (fabs(height) < Precision::Confusion())
		Standard_Failure::Raise("Height of helix too small");

	if ((height > 0 && pitch < 0) || (height < 0 && pitch > 0))
		Standard_Failure::Raise("Pitch and height of helix not compatible");

	gp_Ax2 cylAx2(gp_Pnt(0.0, 0.0, 0.0) , gp::DZ());
	Handle(Geom_Surface) surf;

	if (angle < Precision::Confusion())
	{
		if (radius < Precision::Confusion())
			Standard_Failure::Raise("Radius of helix too small");

		surf = new Geom_CylindricalSurface(cylAx2, radius);
	}
	else
	{
		angle = to_radian(angle);

		if (angle < Precision::Confusion())
			Standard_Failure::Raise("Angle of helix too small");

		surf = new Geom_ConicalSurface(gp_Ax3(cylAx2), angle, radius);
	}

	gp_Pnt2d aPnt(0, 0);
	gp_Dir2d aDir(2. * M_PI, pitch);
	Standard_Real coneDir = 1.0;

	if (leftHanded)
	{
		aDir.SetCoord(-2. * M_PI, pitch);
		coneDir = -1.0;
	}

	gp_Ax2d aAx2d(aPnt, aDir);

	Handle(Geom2d_Line) line = new Geom2d_Line(aAx2d);
	gp_Pnt2d beg = line->Value(0);
	gp_Pnt2d end = line->Value(sqrt(4.0 * M_PI * M_PI + pitch * pitch) * (height / pitch));

	if (newStyle)
	{
		// See discussion at 0001247: Part Conical Helix Height/Pitch Incorrect
		if (angle >= Precision::Confusion())
		{
			// calculate end point for conical helix
			Standard_Real v = height / cos(angle);
			Standard_Real u = coneDir * (height / pitch) * 2.0 * M_PI;
			gp_Pnt2d cend(u, v);
			end = cend;
		}
	}

	Handle(Geom2d_TrimmedCurve) segm = GCE2d_MakeSegment(beg , end);

	TopoDS_Edge edgeOnSurf = BRepBuilderAPI_MakeEdge(segm , surf);
	TopoDS_Wire shape = BRepBuilderAPI_MakeWire(edgeOnSurf);
	BRepLib::BuildCurves3d(shape);
	return shape;
}

//***********
// makeLongHelix is a workaround for an OCC problem found in helices with more than
// some magic number of turns.  See Mantis #0954. (FreeCad)
//***********
servoce::shape servoce::make_long_helix(double pitch, double height,
                                        double radius, double angle,
                                        bool leftHanded)
{
	if (pitch < Precision::Confusion())
		Standard_Failure::Raise("Pitch of helix too small");

	if (height < Precision::Confusion())
		Standard_Failure::Raise("Height of helix too small");

	gp_Ax2 cylAx2(gp_Pnt(0.0, 0.0, 0.0) , gp::DZ());
	Handle(Geom_Surface) surf;
	Standard_Boolean isCylinder;

	if (abs(angle) < Precision::Confusion())     // Cylindrical helix
	{
		if (radius < Precision::Confusion())
			Standard_Failure::Raise("Radius of helix too small");

		surf = new Geom_CylindricalSurface(cylAx2, radius);
		isCylinder = true;
	}
	else                                    // Conical helix
	{
		//angle = to_radian(angle);
		if (abs(angle) < Precision::Confusion())
			Standard_Failure::Raise("Angle of helix too small");

		surf = new Geom_ConicalSurface(gp_Ax3(cylAx2), angle, radius);
		isCylinder = false;
	}

	Standard_Real turns = height / pitch;
	unsigned long wholeTurns = floor(turns);
	Standard_Real partTurn = turns - wholeTurns;

	gp_Pnt2d aPnt(0, 0);
	gp_Dir2d aDir(2. * M_PI, pitch);
	Standard_Real coneDir = 1.0;

	if (leftHanded)
	{
		aDir.SetCoord(-2. * M_PI, pitch);
		coneDir = -1.0;
	}

	gp_Ax2d aAx2d(aPnt, aDir);
	Handle(Geom2d_Line) line = new Geom2d_Line(aAx2d);
	gp_Pnt2d beg = line->Value(0);
	gp_Pnt2d end;
	Standard_Real u, v;
	BRepBuilderAPI_MakeWire mkWire;
	Handle(Geom2d_TrimmedCurve) segm;
	TopoDS_Edge edgeOnSurf;

	for (unsigned long i = 0; i < wholeTurns; i++)
	{
		if (isCylinder)
		{
			end = line->Value(sqrt(4.0 * M_PI * M_PI + pitch * pitch) * (i + 1));
		}
		else
		{
			u = coneDir * (i + 1) * 2.0 * M_PI;
			v = ((i + 1) * pitch) / cos(angle);
			end = gp_Pnt2d(u, v);
		}

		segm = GCE2d_MakeSegment(beg , end);
		edgeOnSurf = BRepBuilderAPI_MakeEdge(segm , surf);
		mkWire.Add(edgeOnSurf);
		beg = end;
	}

	if (partTurn > Precision::Confusion())
	{
		if (isCylinder)
		{
			end = line->Value(sqrt(4.0 * M_PI * M_PI + pitch * pitch) * turns);
		}
		else
		{
			u = coneDir * turns * 2.0 * M_PI;
			v = height / cos(angle);
			end = gp_Pnt2d(u, v);
		}

		segm = GCE2d_MakeSegment(beg , end);
		edgeOnSurf = BRepBuilderAPI_MakeEdge(segm , surf);
		mkWire.Add(edgeOnSurf);
	}

	TopoDS_Wire shape = mkWire.Wire();
	BRepLib::BuildCurves3d(shape);
	return shape;
}

servoce::edge_shape servoce::make_interpolate(const std::vector<servoce::point3>& pnts, const std::vector<servoce::vector3>& tang, bool closed)
{
	Handle(TColgp_HArray1OfPnt) _pnts = new TColgp_HArray1OfPnt(1, pnts.size());

	for (unsigned int i = 0; i < pnts.size(); ++i) _pnts->SetValue(i + 1, pnts[i].Pnt());

	/*Handle(TColStd_HArray1OfReal) _params = new TColStd_HArray1OfReal(1, pnts.size());
	for (int i = 0; i < pnts.size(); ++i) _params->SetValue(i + 1, params[i]);*/

	GeomAPI_Interpolate algo(_pnts, /*_params,*/ closed, 0.0000001);

	if (tang.size())
	{
		TColgp_Array1OfVec _tang(1, tang.size());
		Handle(TColStd_HArray1OfBoolean) _bools = new TColStd_HArray1OfBoolean(1, tang.size());

		for (unsigned int i = 0; i < pnts.size(); ++i) _tang.SetValue(i + 1, tang[i].Vec());

		for (unsigned int i = 0; i < pnts.size(); ++i) _bools->SetValue(i + 1, tang[i] != servoce::vector3(0, 0, 0));

		algo.Load(_tang, _bools);
	}

	algo.Perform();
	return BRepBuilderAPI_MakeEdge(algo.Curve()).Edge();
}

servoce::edge_shape servoce::make_interpolate(const std::vector<servoce::point3>& pnts, bool closed)
{
	Handle(TColgp_HArray1OfPnt) _pnts = new TColgp_HArray1OfPnt(1, pnts.size());

	for (unsigned int i = 0; i < pnts.size(); ++i) _pnts->SetValue(i + 1, pnts[i].Pnt());

	GeomAPI_Interpolate algo(_pnts, /*_params,*/ closed, 0.0000001);

	algo.Perform();
	return BRepBuilderAPI_MakeEdge(algo.Curve()).Edge();
}

servoce::shape servoce::sew(const std::vector<const servoce::shape*>& arr)
{
	BRepBuilderAPI_MakeWire mk;

	for (auto* ptr : arr)
	{
		if (ptr->Shape().ShapeType() == TopAbs_WIRE)
			mk.Add(ptr->Wire());
		else if (ptr->Shape().ShapeType() == TopAbs_EDGE)
			mk.Add(ptr->Edge());
	}

	/*try {*/
	return mk.Wire();
	/*}
	catch
	{
		std::cout << "fail. maybe unsorted" << std::endl;

		std::vector<const servoce::shape*> sorted;
		sorted.push_back(arr[0]);

	}*/
}

servoce::edge_shape servoce::circle_arc(const point3& p1, const point3& p2, const point3& p3)
{
	Handle(Geom_TrimmedCurve) aArcOfCircle = GC_MakeArcOfCircle(p1.Pnt(), p2.Pnt(), p3.Pnt());
	return BRepBuilderAPI_MakeEdge(aArcOfCircle).Edge();
}

#include <TopExp.hxx>
std::pair<servoce::point3, servoce::point3> servoce::shape::sfvertex()
{
	if (Shape().ShapeType() == TopAbs_WIRE)
	{
		TopoDS_Vertex a, b;
		TopExp::Vertices(Wire(), a, b);
		return std::pair<servoce::point3, servoce::point3>(a, b);
	}

	else if (Shape().ShapeType() == TopAbs_EDGE)
	{
		return std::pair<servoce::point3, servoce::point3>(TopExp::FirstVertex(Edge()), TopExp::LastVertex(Edge()));
	}

	else
	{
		throw "TODO Error";
	}
}

bool servoce::shape::is_closed()
{
	auto pair = sfvertex();
	return servoce::point3::early(pair.first, pair.second, 0.0001);
}

servoce::edge_shape servoce::bezier(
    const std::vector<point3>& pnts)
{
	return make_edge(servoce::curve3::bezier(pnts));
}

servoce::edge_shape servoce::bezier(
    const std::vector<point3>& pnts,
    const std::vector<double>& weights)
{
	return make_edge(servoce::curve3::bezier(pnts, weights));
}

servoce::edge_shape servoce::bspline(
    const std::vector<point3>& poles,
    const std::vector<double>& knots,
    const std::vector<int>& multiplicities,
    int degree,
    bool periodic
)
{
	return make_edge(servoce::curve3::bspline(
		poles, knots, multiplicities, 
		degree, periodic));
}

servoce::edge_shape servoce::bspline(
    const std::vector<point3>& poles,
    const std::vector<double>& weights,
    const std::vector<double>& knots,
    const std::vector<int>& multiplicities,
    int degree,
    bool periodic,
    bool check_rational
) 
{
	return make_edge(servoce::curve3::bspline(
		poles, weights, knots, multiplicities, 
		degree, periodic, check_rational));
}


servoce::edge_shape servoce::make_edge(const servoce::curve3::curve3& crv)
{
	auto curve = crv.Curve();
	return BRepBuilderAPI_MakeEdge(curve).Edge();
}

servoce::edge_shape servoce::make_edge(const servoce::curve3::curve3& crv, double strt, double fini)
{
	auto curve = crv.Curve();
	return BRepBuilderAPI_MakeEdge(curve, strt, fini).Edge();
}

servoce::curve3::curve3 servoce::extract_curve(const servoce::shape& edg) 
{
	double first;
	double last;

	const TopoDS_Edge& Edg = edg.Edge_OrOneEdgedWireToEdge(); 

	BRep_Tool::Range(Edg, first, last);

	auto crv = BRep_Tool::Curve(
		Edg, first, last);	

	return servoce::curve3::curve3(crv);
}