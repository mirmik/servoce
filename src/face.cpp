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

servoce::shape servoce::circle(double r) { 
	gp_Circ EL ( gp::XOY(), r );
	Handle(Geom_Circle) anCircle = GC_MakeCircle(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle );
	TopoDS_Wire aCircle = BRepBuilderAPI_MakeWire( aEdge );
	return BRepBuilderAPI_MakeFace(aCircle).Shape();
}

servoce::shape servoce::circle(double r, double angle) { 
	gp_Circ EL ( gp::XOY(), r );
	Handle(Geom_Circle) anCircle = GC_MakeCircle(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle, 0, angle );
	TopoDS_Edge aEdge1 = BRepBuilderAPI_MakeEdge( gp_Pnt(0,0,0), gp_Pnt(r,0,0) );
	TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge( gp_Pnt(0,0,0), gp_Pnt(r*cos(angle),r*sin(angle),0)  );
	TopoDS_Wire aCircle = BRepBuilderAPI_MakeWire( aEdge, aEdge1, aEdge2 );
	return BRepBuilderAPI_MakeFace(aCircle).Shape();
}

servoce::shape servoce::circle(double r, double a1, double a2) { 
	gp_Circ EL ( gp::XOY(), r );
	Handle(Geom_Circle) anCircle = GC_MakeCircle(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle, a1, a2 );
	TopoDS_Edge aEdge1 = BRepBuilderAPI_MakeEdge( gp_Pnt(0,0,0), gp_Pnt(r*cos(a1),r*sin(a1),0) );
	TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge( gp_Pnt(0,0,0), gp_Pnt(r*cos(a2),r*sin(a2),0)  );
	TopoDS_Wire aCircle = BRepBuilderAPI_MakeWire( aEdge, aEdge1, aEdge2 );
	return BRepBuilderAPI_MakeFace(aCircle).Shape();
}

servoce::shape servoce::circle_wire(double r) { 
	gp_Circ EL ( gp::XOY(), r );
	Handle(Geom_Circle) anCircle = GC_MakeCircle(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle );
	TopoDS_Wire aCircle = BRepBuilderAPI_MakeWire( aEdge );
	return aCircle;
}

servoce::shape servoce::circle_wire(double r, double angle) { 
	gp_Circ EL ( gp::XOY(), r );
	Handle(Geom_Circle) anCircle = GC_MakeCircle(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle, 0, angle );
	TopoDS_Wire aCircle = BRepBuilderAPI_MakeWire( aEdge );
	return aCircle;
}

servoce::shape servoce::circle_wire(double r, double a1, double a2) { 
	gp_Circ EL ( gp::XOY(), r );
	Handle(Geom_Circle) anCircle = GC_MakeCircle(EL).Value();
	TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge( anCircle, a1, a2 );
	TopoDS_Wire aCircle = BRepBuilderAPI_MakeWire( aEdge );
	return aCircle;
}

servoce::shape servoce::polygon(const servoce::point3* pnts, size_t size) {
	BRepBuilderAPI_MakePolygon mk;
	for (uint i = 0; i < size; ++i) mk.Add(pnts[i].Pnt());
	mk.Close();
	return BRepBuilderAPI_MakeFace(mk).Shape();
} 

servoce::shape servoce::polygon(const std::vector<servoce::point3>& pnts) {
	return polygon(pnts.data(), pnts.size());
} 

servoce::shape servoce::ngon(double r, int n) { 
	double angle;
	servoce::point3* pnts = (servoce::point3*) alloca(sizeof(servoce::point3) * n);
	for (int i = 0; i < n; ++i) {
		angle = 2 * M_PI / n * i;
		pnts[i] = servoce::point3(r*cos(angle), r*sin(angle), 0);
	}
	return polygon(pnts, n);
}

servoce::shape servoce::rectangle(double a, double b, bool center) { 
	if (center) {
		double x = a/2;
		double y = b/2;
		return polygon({{-x,-y},{x,-y},{x,y},{-x,y}});
	}
	else {
		return polygon({{0,0},{0,b},{a,b},{a,0}});
	}
}

servoce::shape servoce::square(double a, bool center) { 
	return rectangle(a,a,center);
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