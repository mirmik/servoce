#include <servoce/convert.h>
#include <servoce/topo.h>

#include <StlAPI_Writer.hxx>
#include <BRepMesh_IncrementalMesh.hxx>

#include <BRepTools.hxx>
#include <BRep_Builder.hxx>

#include <fstream>

bool servoce::make_stl(const servoce::shape& shp, const std::string& path, double deflection)
{
	BRepMesh_IncrementalMesh mesh(shp.Shape(), deflection);

	if (mesh.IsDone() == false) { return false; }

	StlAPI_Writer stl_writer;
	stl_writer.Write(shp.Shape(), path.c_str());
	return true;
}

void servoce::brep_write(const servoce::shape& shp, const std::string& path) 
{
	std::ofstream file(path);
	BRepTools::Write(shp.Shape(), file);
}

servoce::shape servoce::brep_read(const std::string& path) 
{
	TopoDS_Shape shp;
	BRep_Builder builder;
	std::ifstream file(path);

	BRepTools::Read (shp, file, builder);
	return servoce::shape(shp);
}