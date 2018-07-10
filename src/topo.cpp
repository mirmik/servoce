#include <servoce/topo.h>

#include <TopoDS_Shape.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS.hxx>

#include <BinTools_ShapeSet.hxx>
#include <BinTools.hxx>

#include <BRepTools_WireExplorer.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepFilletAPI_MakeFillet2d.hxx>

#include <TopAbs_ShapeEnum.hxx>

#include <TopExp_Explorer.hxx>

#include <cassert>

/*const char* topotype_to_cstr(TopAbs_ShapeEnum e) {
	switch(e) {
		case TopAbs_SOLID: return "TopAbs_SOLID";
		case TopAbs_WIRE: return "TopAbs_WIRE";
		case TopAbs_FACE: return "TopAbs_FACE";
		case TopAbs_COMPOUND: return "TopAbs_COMPOUND";
		default: return "Another_TopAbs";
	}
}


servoce::shape::shape() {}
servoce::solid::solid() {}
servoce::face::face() {}
servoce::wire::wire() {}
*/
servoce::shape::shape(const TopoDS_Shape& shp) : m_shp(new TopoDS_Shape(shp)) {}
servoce::shape::shape(const shape& oth) : m_shp(new TopoDS_Shape(*oth.m_shp)) {}
servoce::shape::shape(shape&& oth) : m_shp(oth.m_shp) { oth.m_shp = nullptr; }
servoce::shape::~shape() { delete m_shp; }

servoce::shape& servoce::shape::operator= (const shape& oth) {
	if (m_shp != oth.m_shp) {
		delete m_shp;
		m_shp = new TopoDS_Shape(*oth.m_shp);
	}
	return *this;
}

servoce::shape& servoce::shape::operator= (shape&& oth) {
	delete m_shp;
	m_shp = oth.m_shp;
	m_shp = nullptr;
	return *this;
}

TopoDS_Shape& servoce::shape::Shape() { return *m_shp; }
const TopoDS_Shape& servoce::shape::Shape() const { return *m_shp; }
TopoDS_Wire& servoce::shape::Wire() { return TopoDS::Wire(*m_shp); }
const TopoDS_Wire& servoce::shape::Wire() const { return TopoDS::Wire(*m_shp); }
TopoDS_Face& servoce::shape::Face() { return TopoDS::Face(*m_shp); }
const TopoDS_Face& servoce::shape::Face() const { return TopoDS::Face(*m_shp); }
TopoDS_Solid& servoce::shape::Solid() { return TopoDS::Solid(*m_shp); }
const TopoDS_Solid& servoce::shape::Solid() const { return TopoDS::Solid(*m_shp); }
TopoDS_Compound& servoce::shape::Compound() { return TopoDS::Compound(*m_shp); }
const TopoDS_Compound& servoce::shape::Compound() const { return TopoDS::Compound(*m_shp); }

/*
servoce::solid::solid(const TopoDS_Shape& shp) : shape(shp) {
	//assert(m_shp->ShapeType() == TopAbs_SOLID || m_shp->ShapeType() == TopAbs_COMPOUND);
}

servoce::face::face(const TopoDS_Shape& shp) : shape(shp) {
	//assert(m_shp->ShapeType() == TopAbs_FACE || m_shp->ShapeType() == TopAbs_COMPOUND);
}

servoce::wire::wire(const TopoDS_Shape& shp) : shape(shp) {
	//assert(m_shp->ShapeType() == TopAbs_WIRE);
}

TopoDS_Shape& servoce::shape::Shape() { return *m_shp; }
const TopoDS_Shape& servoce::shape::Shape() const { return *m_shp; }

TopoDS_Wire& servoce::wire::Wire() { return TopoDS::Wire(*m_shp); }
const TopoDS_Wire& servoce::wire::Wire() const { return TopoDS::Wire(*m_shp); }

TopoDS_Face& servoce::face::Face() { return TopoDS::Face(*m_shp); }
const TopoDS_Face& servoce::face::Face() const { return TopoDS::Face(*m_shp); }

TopoDS_Solid& servoce::solid::Solid() { return TopoDS::Solid(*m_shp); }
const TopoDS_Solid& servoce::solid::Solid() const { return TopoDS::Solid(*m_shp); }

servoce::solid servoce::shape::to_solid() { return servoce::solid(*m_shp); }
servoce::wire servoce::shape::to_wire() { return servoce::wire(*m_shp); }
servoce::face servoce::shape::to_face() { return servoce::face(*m_shp); }

*/


void servoce::shape::dump(std::ostream& out) const {
	BinTools_ShapeSet theShapeSet;
	if (m_shp->IsNull()) {
	    theShapeSet.Add(*m_shp);
	    theShapeSet.Write(out);
	    BinTools::PutInteger(out, -1);
	    BinTools::PutInteger(out, -1);
	    BinTools::PutInteger(out, -1);
	}
	else {
	    Standard_Integer shapeId = theShapeSet.Add(*m_shp);
	    Standard_Integer locId = theShapeSet.Locations().Index(m_shp->Location());
	    Standard_Integer orient = static_cast<int>(m_shp->Orientation());

	    theShapeSet.Write(out);
	    BinTools::PutInteger(out, shapeId);
	    BinTools::PutInteger(out, locId);
	    BinTools::PutInteger(out, orient);
	}
}

void servoce::shape::load(std::istream& in) {
    BinTools_ShapeSet theShapeSet;
    theShapeSet.Read(in);
    Standard_Integer shapeId=0, locId=0, orient=0;
    BinTools::GetInteger(in, shapeId);
    if (shapeId <= 0 || shapeId > theShapeSet.NbShapes())
        return;

    BinTools::GetInteger(in, locId);
    BinTools::GetInteger(in, orient);
    TopAbs_Orientation anOrient = static_cast<TopAbs_Orientation>(orient);

    //try {
        *m_shp = theShapeSet.Shape(shapeId);
        m_shp->Location(theShapeSet.Locations().Location (locId));
        m_shp->Orientation (anOrient);
    /*}
    catch (Standard_Failure) {
        gxx::println("Failed to read shape from binary stream");
        exit(-1);	
    }*/
}


std::string servoce::shape::string_dump() const {
	std::stringstream sstrm;
	dump(sstrm);
	return sstrm.str();
}

servoce::shape servoce::shape::restore_string_dump(const std::string& in) {
	std::stringstream sstrm(in);
	servoce::shape shp;
	shp.m_shp = new TopoDS_Solid;
	shp.load(sstrm);
	return shp;
}




servoce::shape servoce::shape::fillet(double r, const std::vector<int>& nums) {
    if (TopAbs_FACE != m_shp->ShapeType()) {
    	std::set<int>snums(nums.begin(), nums.end());
    	BRepFilletAPI_MakeFillet mk(*m_shp);//
    	int idx = 0;
    	for (TopExp_Explorer ex(*m_shp,TopAbs_EDGE); ex.More(); ex.Next()) {
    	    TopoDS_Edge Edge =TopoDS::Edge(ex.Current());
    	    if (snums.count(idx)) mk.Add(r, Edge);
    	    ++idx;
    	}
	
    	return mk.Shape();
	}
	else {
		std::set<int>snums(nums.begin(), nums.end());
		BRepFilletAPI_MakeFillet2d mk(Face());

		int idx = 0;

		for(TopExp_Explorer expWire(Shape(), TopAbs_WIRE); expWire.More(); expWire.Next()) {
			BRepTools_WireExplorer explorer(TopoDS::Wire(expWire.Current()));
 			while (explorer.More()) {
				if (nums.size() == 0 || snums.count(idx))mk.AddFillet(explorer.CurrentVertex(), r);
				explorer.Next();
				++idx;
			}
		}
		return mk.Shape();	
	}
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