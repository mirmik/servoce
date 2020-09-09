#include <servoce/vertex.h>
#include <TopoDS_Vertex.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>

servoce::shape servoce::make_vertex(const servoce::point3 & pnt) 
{
	BRepBuilderAPI_MakeVertex builder(pnt.Pnt());
	return builder.Shape();
}