#include <servoce/topo.h>

#include <TopoDS_Shape.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS.hxx>

servoce::shape::shape(const TopoDS_Shape& shp) : m_shp(new TopoDS_Shape(shp)) {}
servoce::shape::shape(const shape& oth) : m_shp(new TopoDS_Shape(*oth.m_shp)) {}
servoce::shape::~shape() { delete m_shp; }

servoce::solid::solid(const TopoDS_Shape& sld) : shape(sld) {}
servoce::face::face(const TopoDS_Face& sld) : shape(sld) {}
servoce::wire::wire(const TopoDS_Wire& sld) : shape(sld) {}
