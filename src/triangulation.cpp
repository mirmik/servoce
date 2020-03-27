#include <servoce/triangulation.h>

#include <BRep_Tool.hxx>
#include <TopLoc_Location.hxx>
#include <BRepMesh_IncrementalMesh.hxx>

#include <servoce/face.h>

std::pair<std::vector<servoce::point3>, std::vector<std::tuple<int, int, int>>>
servoce::triangulation(servoce::shape& shp, double deflection)
{
	BRepMesh_IncrementalMesh mesh(shp.Shape(), deflection);

	auto L = TopLoc_Location();
	auto triangulation = BRep_Tool::Triangulation(shp.faces()[0].Face(), L);

	auto Nodes = triangulation->Nodes();
	auto Triangles = triangulation->Triangles();

	std::vector<std::tuple<int,int,int>> triangles;
	for (int i = 1; i < triangulation->NbTriangles() + 1; ++i) 
	{
		int a, b, c;
		auto tri = Triangles(i);
		tri.Get(a,b,c);
		triangles.emplace_back(a,b,c);
	}	

	std::vector<servoce::point3> nodes;
	for (int i = 1; i < triangulation->NbNodes() + 1; ++i) 
	{
		nodes.emplace_back(Nodes(i));		
	}

	return std::make_pair(nodes, triangles);
}