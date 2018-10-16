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
#include <BRepFilletAPI_MakeFillet2d.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <TopExp_Explorer.hxx>

#include <BRepOffsetAPI_MakePipe.hxx>

servoce::shape servoce::make_circle(double r) { 
	gp_Circ EL ( gp::XOY(), r );
	Handle(Geom_Circle) anCircle = GC_MakeCircle(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle );
	TopoDS_Wire aCircle = BRepBuilderAPI_MakeWire( aEdge );
	return BRepBuilderAPI_MakeFace(aCircle).Shape();
}

servoce::shape servoce::make_polygon(const servoce::point3* pnts, size_t size) {
	BRepBuilderAPI_MakePolygon mk;
	for (uint i = 0; i < size; ++i) mk.Add(pnts[i].Pnt());
	mk.Close();
	return BRepBuilderAPI_MakeFace(mk).Shape();
} 

servoce::shape servoce::make_polygon(const std::vector<servoce::point3>& pnts) {
	return make_polygon(pnts.data(), pnts.size());
} 

servoce::shape servoce::make_ngon(double r, int n) { 
	double angle;
	servoce::point3 pnts[n];
	for (int i = 0; i < n; ++i) {
		angle = 2 * M_PI / n * i;
		pnts[i] = servoce::point3(r*cos(angle), r*sin(angle), 0);
	}
	return make_polygon(pnts, n);
}

servoce::shape servoce::make_rectangle(double a, double b, bool center) { 
	if (center) {
		double x = a/2;
		double y = b/2;
		return make_polygon({{-x,-y},{x,-y},{x,y},{-x,y}});
	}
	else {
		return make_polygon({{0,0},{0,b},{a,b},{a,0}});
	}
}

servoce::shape servoce::make_square(double a, bool center) { 
	return make_rectangle(a,a,center);
}
/*
servoce::shape servoce::shape::fillet(double r, const std::vector<int>& nums) {
	std::set<int>snums(nums.begin(), nums.end());
	BRepFilletAPI_MakeFillet2d mk(shape());

	int idx = 0;

	for(TopExp_Explorer expWire(TopoDS::shape(shape()), TopAbs_WIRE); expWire.More(); expWire.Next()) {
		BRepTools_WireExplorer explorer(TopoDS::Wire(expWire.Current()));
    	while (explorer.More()) {
			if (nums.size() == 0 || snums.count(idx))mk.AddFillet(explorer.CurrentVertex(), r);
			explorer.Next();
			++idx;
		}
	}
	return mk.Shape();
}*/


/*servoce::sweep_shape::~sweep_shape() {}

servoce::sweep_shape::sweep_shape(BRepPrimAPI_MakeSweep&& builder) : shape(builder.Shape()) {
	m_first = new TopoDS_Shape(builder.FirstShape());
	m_last = new TopoDS_Shape(builder.LastShape());
}

servoce::sweep_shape servoce::sweep2d::make_sweep(const servoce::shape& profile, const servoce::wire& path) {
    if (path.Shape().IsNull())
        Standard_Failure::Raise("Cannot sweep along empty spine");
    if (profile.Shape().IsNull())
        Standard_Failure::Raise("Cannot sweep empty profile");
    return BRepOffsetAPI_MakePipe(path.Wire(), profile.Shape());
}

std::vector<servoce::wire> servoce::shape::wires() {
	TopExp_Explorer explorer(Shape(), TopAbs_WIRE);
	std::vector<servoce::wire> ret;

	while(explorer.More()) {
		ret.emplace_back(explorer.Current());
		explorer.Next();
	}

	return ret;
}*/