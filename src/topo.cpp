#include <servoce/topo.h>

#include <TopoDS_Shape.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS.hxx>

#include <cassert>
#include <gxx/print.h>

const char* topotype_to_cstr(TopAbs_ShapeEnum e) {
	switch(e) {
		case TopAbs_SOLID: return "TopAbs_SOLID";
		case TopAbs_WIRE: return "TopAbs_WIRE";
		case TopAbs_FACE: return "TopAbs_FACE";
		case TopAbs_COMPOUND: return "TopAbs_COMPOUND";
		default: return "Another_TopAbs";
	}
}

servoce::shape::shape(const TopoDS_Shape& shp) : m_shp(new TopoDS_Shape(shp)) {}
servoce::shape::shape(const shape& oth) : m_shp(new TopoDS_Shape(*oth.m_shp)) {}
servoce::shape::~shape() { 
	delete m_shp; 
}

servoce::solid::solid(const TopoDS_Shape& shp) : shape(shp) {
	assert(m_shp->ShapeType() == TopAbs_SOLID || m_shp->ShapeType() == TopAbs_COMPOUND);
}

servoce::face::face(const TopoDS_Shape& shp) : shape(shp) {
	assert(m_shp->ShapeType() == TopAbs_FACE);
}

servoce::wire::wire(const TopoDS_Shape& shp) : shape(shp) {
	gxx::println(topotype_to_cstr(m_shp->ShapeType()));
	assert(m_shp->ShapeType() == TopAbs_WIRE);
}

TopoDS_Shape& servoce::shape::Shape() { return *m_shp; }
const TopoDS_Shape& servoce::shape::Shape() const { return *m_shp; }

TopoDS_Wire& servoce::wire::Wire() { return TopoDS::Wire(*m_shp); }
const TopoDS_Wire& servoce::wire::Wire() const { return TopoDS::Wire(*m_shp); }

TopoDS_Face& servoce::face::Face() { return TopoDS::Face(*m_shp); }
const TopoDS_Face& servoce::face::Face() const { return TopoDS::Face(*m_shp); }

TopoDS_Solid& servoce::solid::Solid() { return TopoDS::Solid(*m_shp); }
const TopoDS_Solid& servoce::solid::Solid() const { return TopoDS::Solid(*m_shp); }