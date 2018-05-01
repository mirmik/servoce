#include <servoce/topo.h>

#include <gp_Vec.hxx>
#include <gp_Pnt.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <TopoDS_Vertex.hxx>

gp_Vec servoce::vector3::Vec() const { return gp_Vec(x,y,z); }
gp_Pnt servoce::point3::Pnt() const { return gp_Pnt(x,y,z); }
TopoDS_Vertex servoce::point3::Vtx() const { return BRepBuilderAPI_MakeVertex(Pnt()); }

