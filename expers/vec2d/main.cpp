#include <servoce/scene.h>
#include <servoce/display.h>
#include <servoce/solid.h>

#include <servoce/face.h>

#include <BRep_Tool.hxx>
#include <TopLoc_Location.hxx>
#include <BRepMesh_IncrementalMesh.hxx>

#include <nos/print.h>

int main() 
{
	auto shp = servoce::sphere(10);	
	auto deflection = 0.1;
	BRepMesh_IncrementalMesh mesh(shp.Shape(), deflection);

	auto L = TopLoc_Location();
	auto triangulation = BRep_Tool::Triangulation(shp.faces()[0].Face(), L);

	nos::println(triangulation.IsNull());
	nos::println(triangulation->NbTriangles());
	nos::println(triangulation->NbNodes());

	auto nodes = triangulation->Nodes();
	auto triangles = triangulation->Triangles();

	PRINT(triangles.Length());

	auto vectri = std::vector<std::tuple<int,int,int>>();

	for (int i = 1; i < triangulation->NbTriangles() + 1; ++i) 
	{
		int a, b, c;
		auto tri = triangles(i);
		tri.Get(a,b,c);
		vectri.push_back(std::make_tuple(a,b,c));
	}	

	nos::println(vectri);

}