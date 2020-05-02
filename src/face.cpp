#include <servoce/face.h>
#include <servoce/wire.h>
#include <servoce/surface.h>
#include <servoce/edge.h>

#include <gp_Circ.hxx>
#include <gp_Elips.hxx>
#include <GC_MakeCircle.hxx>
#include <GC_MakeEllipse.hxx>

#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepFilletAPI_MakeFillet2d.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <TopExp_Explorer.hxx>
#include <BRep_Tool.hxx>

#include <gp_Pln.hxx>

#include <BRepAdaptor_Curve.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <BRepAdaptor_Surface.hxx>

#include <BRepOffsetAPI_MakePipe.hxx>
#include <Font_BRepTextBuilder.hxx>
#include <ShapeFix_Face.hxx>

#include <BRepFill.hxx>

BRepAdaptor_Surface servoce::face_shape::AdaptorSurface() const
{
	return BRepAdaptor_Surface(Face());
}

servoce::edge_shape servoce::circle_edge(double r)
{
	gp_Circ EL ( gp::XOY(), r );
	Handle(Geom_Circle) anCircle = GC_MakeCircle(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle );
	return aEdge;
}

servoce::edge_shape servoce::circle_edge(double r, double angle)
{
	gp_Circ EL ( gp::XOY(), r );
	Handle(Geom_Circle) anCircle = GC_MakeCircle(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle, 0, angle );
	return aEdge;
}

servoce::edge_shape servoce::circle_edge(double r, double a1, double a2)
{
	gp_Circ EL ( gp::XOY(), r );
	Handle(Geom_Circle) anCircle = GC_MakeCircle(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle, a1, a2 );
	return aEdge;
}


servoce::face_shape servoce::circle(double r)
{
	return circle_edge(r).fill();
}

servoce::face_shape servoce::circle(double r, double angle)
{
	auto aEdge = circle_edge(r, angle).Edge();
	TopoDS_Edge aEdge1 = BRepBuilderAPI_MakeEdge( gp_Pnt(0, 0, 0), gp_Pnt(r, 0, 0) );
	TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge( gp_Pnt(0, 0, 0), gp_Pnt(r * cos(angle), r * sin(angle), 0)  );
	TopoDS_Wire aCircle = BRepBuilderAPI_MakeWire( aEdge, aEdge1, aEdge2 );
	return BRepBuilderAPI_MakeFace(aCircle).Face();
}

servoce::face_shape servoce::circle(double r, double a1, double a2)
{
	auto aEdge = circle_edge(r, a1, a2).Edge();
	TopoDS_Edge aEdge1 = BRepBuilderAPI_MakeEdge( gp_Pnt(0, 0, 0), gp_Pnt(r * cos(a1), r * sin(a1), 0) );
	TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge( gp_Pnt(0, 0, 0), gp_Pnt(r * cos(a2), r * sin(a2), 0)  );
	TopoDS_Wire aCircle = BRepBuilderAPI_MakeWire( aEdge, aEdge1, aEdge2 );
	return BRepBuilderAPI_MakeFace(aCircle).Face();
}

servoce::edge_shape servoce::ellipse_edge(double r1, double r2)
{
	gp_Elips EL ( gp::XOY(), r1, r2 );
	Handle(Geom_Ellipse) anCircle = GC_MakeEllipse(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle );
	return aEdge;
}

servoce::edge_shape servoce::ellipse_edge(double r1, double r2, double a1, double a2)
{
	gp_Elips EL ( gp::XOY(), r1, r2 );
	Handle(Geom_Ellipse) anCircle = GC_MakeEllipse(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle, a1, a2 );
	return aEdge;
}

servoce::face_shape servoce::ellipse(double r1, double r2)
{
	return ellipse_edge(r1, r2).fill();
}

servoce::face_shape servoce::ellipse(double r1, double r2, double a1, double a2)
{
	TopoDS_Edge aEdge = ellipse_edge(r1, r2, a1, a2).Edge();

	BRepAdaptor_Curve curve(aEdge);
	gp_Pnt p1, p2;
	curve.D0(a1, p1);
	curve.D0(a2, p2);

	TopoDS_Edge aEdge1 = BRepBuilderAPI_MakeEdge( gp_Pnt(0, 0, 0), p1 );
	TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge( gp_Pnt(0, 0, 0), p2 );
	TopoDS_Wire aCircle = BRepBuilderAPI_MakeWire( aEdge, aEdge1, aEdge2 );
	return BRepBuilderAPI_MakeFace(aCircle).Face();
}





servoce::face_shape servoce::polygon(const servoce::point3* pnts, size_t size)
{
	BRepBuilderAPI_MakePolygon mk;

	for (unsigned int i = 0; i < size; ++i) mk.Add(pnts[i].Pnt());

	mk.Close();
	return BRepBuilderAPI_MakeFace(mk).Face();
}

servoce::face_shape servoce::polygon(const std::vector<servoce::point3>& pnts)
{
	return polygon(pnts.data(), pnts.size());
}


servoce::wire_shape servoce::ngon_wire(double r, int n)
{
	double angle;
	std::vector<servoce::point3> pnts;
	pnts.resize(n);

	for (int i = 0; i < n; ++i)
	{
		angle = 2 * M_PI / n * i;
		pnts[i] = servoce::point3(r * cos(angle), r * sin(angle), 0);
	}

	std::vector<servoce::point3> pntsvec;

	for (int i = 0; i < n; ++i) pntsvec.push_back(pnts[i]);

	return servoce::make_polysegment(pntsvec, true);
}

servoce::face_shape servoce::ngon(double r, int n)
{
	double angle;
	std::vector<servoce::point3> pnts;
	pnts.resize(n);

	for (int i = 0; i < n; ++i)
	{
		angle = 2 * M_PI / n * i;
		pnts[i] = servoce::point3(r * cos(angle), r * sin(angle), 0);
	}

	return polygon(pnts.data(), n);
}

servoce::wire_shape servoce::rectangle_wire(double a, double b, bool center)
{
	if (center)
	{
		double x = a / 2;
		double y = b / 2;

		return make_polysegment({{ -x, -y}, { x, -y}, {x, y}, { -x, y}}, true);
	}

	else
	{
		return make_polysegment({{0, 0}, {a, 0}, {a, b}, {0, b}}, true);
	}
}

servoce::face_shape servoce::rectangle(double a, double b, bool center)
{
	return rectangle_wire(a,b,center).fill();
}

servoce::wire_shape servoce::square_wire(double a, bool center)
{
	return rectangle_wire(a, a, center);
}

servoce::face_shape servoce::square(double a, bool center)
{
	return rectangle(a, a, center);
}

servoce::shape servoce::textshape(const std::string& text, const std::string fontpath, size_t size)
{
	Font_BRepTextBuilder builder;
	Font_BRepFont font;

	bool okfont = font.Init(fontpath.c_str(), size);

	if (!okfont)
	{
		throw std::runtime_error("Wrong font path.");
	}

	NCollection_String collection(text.c_str());
	TopoDS_Shape textshp = builder.Perform (font, collection);
	return textshp;
}

/*servoce::face_shape servoce::fill(const servoce::shape& obj)
{
	BRepBuilderAPI_MakeFace mk(obj.Wire_orEdgeToWire());
	return mk.Face();
}*/

servoce::shape servoce::fillet2d(const servoce::shape& shp, double r, const std::vector<servoce::point3>& refs)
{
	BRepFilletAPI_MakeFillet2d mk(shp.Face());

	for (auto& p : refs)
	{
		mk.AddFillet(near_vertex(shp, p).Vertex(), r);
	}

	return mk.Shape();
}


servoce::shape servoce::fillet2d(const servoce::shape& shp, double r)
{
	BRepFilletAPI_MakeFillet2d mk(shp.Face());

	for (TopExp_Explorer expWire(shp.Shape(), TopAbs_WIRE); expWire.More(); expWire.Next())
	{
		BRepTools_WireExplorer explorer(TopoDS::Wire(expWire.Current()));

		while (explorer.More())
		{
			const TopoDS_Vertex& vtx = explorer.CurrentVertex();
			mk.AddFillet(vtx, r);

			explorer.Next();
		}
	}

	return mk.Shape();
}

servoce::face_shape servoce::chamfer2d(const servoce::shape& shp, double r, const std::vector<servoce::point3>& refs)
{
	(void) shp, (void) r, (void) refs;
	throw std::runtime_error("chamfer2d. TODO.");
}

servoce::face_shape servoce::chamfer2d(const servoce::shape& shp, double r)
{
	(void) shp, (void) r;
	throw std::runtime_error("chamfer2d. TODO.");
}


servoce::face_shape servoce::infplane()
{
	//Handle(Geom_Plane) plane = new Geom_Plane(gp_Pnt(0,0,0), gp_Vec(0,0,1));
	TopoDS_Face aFace = BRepBuilderAPI_MakeFace(gp_Pln(gp_Pnt(0, 0, 0), gp_Vec(0, 0, 1)));
	return aFace;
}

servoce::face_shape servoce::ruled_face(const servoce::shape& a, const servoce::shape& b)
{
	TopoDS_Face aFace = BRepFill::Face (a.Edge(), b.Edge());
	return aFace;
}

servoce::face_shape servoce::trivial_tube(const servoce::shape& spine, double r)
{
	if (spine.shapetype_as_string() == "wire")
		throw std::runtime_error("only edges support for now");

	auto edg = spine.as_edge();
	auto urange = edg.range();

	servoce::surface surf = servoce::tube_surface(edg.curve(), r);
	auto vrange = surf.urange();

	return make_face(surf, vrange, urange);
}

servoce::face_shape servoce::make_face(
    const servoce::surface& surf, double u1, double u2, double v1, double v2)
{
	BRepBuilderAPI_MakeFace algo(surf.Surface(), u1, u2, v1, v2, 1e-6);
	algo.Build();
	return algo.Face();
}


servoce::face_shape servoce::make_face(const servoce::surface& surf)
{
	//throw std::runtime_error("HERE");
	Standard_Real u1, u2, v1, v2;
	surf.Surface()->Bounds(u1, u2, v1, v2);

	BRepBuilderAPI_MakeFace algo(surf.Surface(), u1, u2, v1, v2, 1e-6);
	algo.Build();
	return algo.Face();
}

servoce::face_shape servoce::make_face(
    const servoce::surface& surf, std::pair<double, double> urange, std::pair<double, double> vrange)
{
	//throw std::runtime_error("HERE");
	return servoce::make_face(surf, urange.first, urange.second, vrange.first, vrange.second);
}

servoce::surface servoce::face_shape::surface() const
{
	return BRep_Tool::Surface(Face());
}


servoce::face_shape servoce::make_face(const std::vector<const servoce::shape*>& vec)
{
	BRepBuilderAPI_MakeFace algo(vec[0]->Wire_orEdgeToWire());

	auto it = ++vec.begin();
	auto eit = vec.end();

	for (;it!=eit;++it)
	{
		algo.Add((*it)->Wire_orEdgeToWire());
	}

	algo.Build();

	//return algo.Face();
	ShapeFix_Face fixer(algo.Face());
	fixer.Perform();
	fixer.FixOrientation();
	return servoce::shape(fixer.Face()).Face();
}

servoce::face_shape servoce::fix_face(const servoce::face_shape& shp)
{
	ShapeFix_Face fixer(shp.Face());
	fixer.Perform();
	fixer.FixOrientation();
	return servoce::shape(fixer.Face()).Face();
}

/*servoce::face_shape servoce::make_face(const std::vector<const servoce::shape*>& shp) 
{
	BRepBuilderAPI_MakeFace algo;

	for (auto& s : shp) 
	{
		algo.Add(s->Wire_orEdgeToWire());
	}

	ShapeFix_Face fixer(algo.Face());
	fixer.Perform();
	return servoce::shape(fixer.Face()).Face();
}*/