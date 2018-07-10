#include <servoce/convert.h>
#include <servoce/topo.h>

#include <StlAPI_Writer.hxx>
#include <BRepMesh_IncrementalMesh.hxx>

bool servoce::make_stl(const std::string& path, const servoce::shape& shp, double deflection) {
	BRepMesh_IncrementalMesh mesh(shp.Shape(), deflection);

    if (mesh.IsDone() == false) { return false; }

    StlAPI_Writer stl_writer;
    stl_writer.Write(shp.Shape(), path.c_str());
    return true;
}