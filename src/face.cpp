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

#include <BRepOffsetAPI_MakePipe.hxx>
#include <Font_BRepTextBuilder.hxx>

#include <BRepFill.hxx>

BRepAdaptor_Surface servoce::face_shape::AdaptorSurface() const
{
	return BRepAdaptor_Surface(Face());
}

servoce::shape servoce::circle(double r, bool wire)
{
	gp_Circ EL ( gp::XOY(), r );
	Handle(Geom_Circle) anCircle = GC_MakeCircle(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle );
	TopoDS_Wire aCircle = BRepBuilderAPI_MakeWire( aEdge );

	if (wire)
		return aCircle;

	return BRepBuilderAPI_MakeFace(aCircle).Shape();
}

servoce::shape servoce::circle(double r, double angle, bool wire)
{
	gp_Circ EL ( gp::XOY(), r );
	Handle(Geom_Circle) anCircle = GC_MakeCircle(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle, 0, angle );

	if (wire)
		return BRepBuilderAPI_MakeWire( aEdge ).Shape();

	TopoDS_Edge aEdge1 = BRepBuilderAPI_MakeEdge( gp_Pnt(0, 0, 0), gp_Pnt(r, 0, 0) );
	TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge( gp_Pnt(0, 0, 0), gp_Pnt(r * cos(angle), r * sin(angle), 0)  );
	TopoDS_Wire aCircle = BRepBuilderAPI_MakeWire( aEdge, aEdge1, aEdge2 );
	return BRepBuilderAPI_MakeFace(aCircle).Shape();
}

servoce::shape servoce::circle(double r, double a1, double a2, bool wire)
{
	gp_Circ EL ( gp::XOY(), r );
	Handle(Geom_Circle) anCircle = GC_MakeCircle(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle, a1, a2 );

	if (wire)
		return BRepBuilderAPI_MakeWire( aEdge ).Shape();

	TopoDS_Edge aEdge1 = BRepBuilderAPI_MakeEdge( gp_Pnt(0, 0, 0), gp_Pnt(r * cos(a1), r * sin(a1), 0) );
	TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge( gp_Pnt(0, 0, 0), gp_Pnt(r * cos(a2), r * sin(a2), 0)  );
	TopoDS_Wire aCircle = BRepBuilderAPI_MakeWire( aEdge, aEdge1, aEdge2 );
	return BRepBuilderAPI_MakeFace(aCircle).Shape();
}


servoce::shape servoce::ellipse(double r1, double r2, bool wire)
{
	gp_Elips EL ( gp::XOY(), r1, r2 );
	Handle(Geom_Ellipse) anCircle = GC_MakeEllipse(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle );
	TopoDS_Wire w = BRepBuilderAPI_MakeWire( aEdge );

	if (wire)
		return w;

	return BRepBuilderAPI_MakeFace(w).Shape();
}

servoce::shape servoce::ellipse(double r1, double r2, double a1, double a2, bool wire)
{
	gp_Elips EL ( gp::XOY(), r1, r2 );
	Handle(Geom_Ellipse) anCircle = GC_MakeEllipse(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle, a1, a2 );

	if (wire)
		return BRepBuilderAPI_MakeWire( aEdge ).Shape();

	BRepAdaptor_Curve curve(aEdge);
	gp_Pnt p1, p2;
	curve.D0(a1, p1);
	curve.D0(a2, p2);

	TopoDS_Edge aEdge1 = BRepBuilderAPI_MakeEdge( gp_Pnt(0, 0, 0), p1 );
	TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge( gp_Pnt(0, 0, 0), p2 );
	TopoDS_Wire aCircle = BRepBuilderAPI_MakeWire( aEdge, aEdge1, aEdge2 );
	return BRepBuilderAPI_MakeFace(aCircle).Shape();
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

servoce::shape servoce::ngon(double r, int n, bool wire)
{
	double angle;
	std::vector<servoce::point3> pnts;
	pnts.resize(n);

	//servoce::point3* pnts = (servoce::point3*) alloca(sizeof(servoce::point3) * n);
	for (int i = 0; i < n; ++i)
	{
		angle = 2 * M_PI / n * i;
		pnts[i] = servoce::point3(r * cos(angle), r * sin(angle), 0);
	}

	if (wire)
	{
		std::vector<servoce::point3> pntsvec;

		for (int i = 0; i < n; ++i) pntsvec.push_back(pnts[i]);

		return servoce::make_polysegment(pntsvec, true);
	}

	return polygon(pnts.data(), n);
}

servoce::shape servoce::rectangle(double a, double b, bool center, bool wire)
{
	if (center)
	{
		double x = a / 2;
		double y = b / 2;

		if (wire)
			return make_polysegment({{ -x, -y}, {x, -y}, {x, y}, { -x, y}}, true);
		return polygon({{ -x, -y}, {x, -y}, {x, y}, { -x, y}});
	}
	else
	{
		if (wire)
			return make_polysegment({{0, 0}, {a, 0}, {a, b}, {0, b}}, true);
		return polygon({{0, 0}, {a, 0}, {a, b}, {0, b}});
	}
}

servoce::shape servoce::square(double a, bool center, bool wire)
{
	return rectangle(a, a, center, wire);
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

	servoce::surface::surface surf = servoce::surface::tube(edg.curve(), r);
	auto vrange = surf.urange();

	return make_face(surf, vrange, urange);
}

servoce::face_shape servoce::make_face(
    const servoce::surface::surface& surf, double u1, double u2, double v1, double v2)
{
	BRepBuilderAPI_MakeFace algo(surf.Surface(), u1, u2, v1, v2, 1e-6);
	algo.Build();
	return algo.Face();
}

servoce::face_shape servoce::make_face(
    const servoce::surface::surface& surf, std::pair<double, double> urange, std::pair<double, double> vrange)
{
	return servoce::make_face(surf, urange.first, urange.second, vrange.first, vrange.second);
}

servoce::surface::surface servoce::face_shape::surface() const
{
	return BRep_Tool::Surface(Face());
}