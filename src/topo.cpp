#include <servoce/topo.h>

#include <TopoDS_Shape.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS.hxx>

#include <cassert>

servoce::shape::shape(const TopoDS_Shape& shp) : m_shp(new TopoDS_Shape(shp)) {}
servoce::shape::shape(const shape& oth) : m_shp(new TopoDS_Shape(*oth.m_shp)) {}
servoce::shape::~shape() { delete m_shp; }

servoce::solid::solid(const TopoDS_Shape& shp) : shape(shp) {
	assert(m_shp->ShapeType() == TopAbs_SOLID || m_shp->ShapeType() == TopAbs_COMPOUND);
}

servoce::face::face(const TopoDS_Shape& shp) : shape(shp) {
	assert(m_shp->ShapeType() == TopAbs_FACE);
}

servoce::wire::wire(const TopoDS_Shape& shp) : shape(shp) {
	assert(m_shp->ShapeType() == TopAbs_WIRE);
}
