#include <servoce/convert.h>
#include <servoce/topo.h>

#include <StlAPI_Writer.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <gxx/print.h>

void servoce::make_stl(const std::string& path, const servoce::shape& shp) {
	StlAPI_Writer stl_writer;
    //stl_writer.SetDeflection(0.1);


	//BRepMesh_IncrementalMesh Mesh( shp.Shape(), 0.1 );
	BRepMesh_IncrementalMesh Mesh( shp.Shape(), 0.01, false );
	//Mesh.Perform();
	gxx::println(Mesh.GetStatusFlags());

    gxx::println("HERE");
    //stl_writer.RelativeMode() = false;
    stl_writer.Write(shp.Shape(), path.c_str());

    gxx::println("HERE");
}