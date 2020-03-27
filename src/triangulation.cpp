#include <servoce/triangulation.h>

#include <BRep_Tool.hxx>
#include <TopLoc_Location.hxx>
#include <BRepMesh_IncrementalMesh.hxx>

#include <servoce/face.h>

std::pair<std::vector<servoce::point3>, std::vector<std::tuple<int, int, int>>>
servoce::triangulation(servoce::face_shape& shp, double deflection)
{
	BRepMesh_IncrementalMesh mesh(shp.Shape(), deflection);

	auto L = TopLoc_Location();
	auto triangulation = BRep_Tool::Triangulation(shp.Face(), L);

	auto Nodes = triangulation->Nodes();
	auto Triangles = triangulation->Triangles();

	std::vector<std::tuple<int,int,int>> triangles;
	triangles.reserve(triangulation->NbTriangles());
	for (int i = 1; i < triangulation->NbTriangles() + 1; ++i) 
	{
		int a, b, c;
		auto tri = Triangles(i);
		tri.Get(a,b,c);
		triangles.emplace_back(a-1,b-1,c-1);
	}	

	std::vector<servoce::point3> nodes;
	nodes.reserve(triangulation->NbNodes());
	for (int i = 1; i < triangulation->NbNodes() + 1; ++i) 
	{
		nodes.emplace_back(Nodes(i));		
	}

	return std::make_pair(nodes, triangles);
}

std::pair<std::vector<servoce::point3>, std::vector<std::tuple<int, int, int>>>
servoce::triangulation(servoce::shape& shp, double deflection)
{
	std::vector<std::pair<std::vector<servoce::point3>, std::vector<std::tuple<int, int, int>>>> results;

	for (auto f : shp.faces()) 
	{
		results.push_back(triangulation(f, deflection));
	}

	std::vector<servoce::point3> nodes;
	std::vector<std::tuple<int,int,int>> triangles;

	int n = 0;
	int t = 0;

	for (auto & r : results) 
	{
		n += r.first.size();
		t += r.second.size();
	}

	nodes.reserve(n);
	triangles.reserve(t);

	for (auto & r : results) 
	{
		int nsize = nodes.size();

		std::copy(r.first.begin(), r.first.end(), std::back_inserter(nodes));
		//std::copy(r.second.begin(), r.second.end(), std::back_inserter(triangles));

		auto it = r.second.begin();
		const auto eit = r.second.end();
		for (;it!=eit;++it) 
		{
			triangles.emplace_back(std::get<0>(*it)+nsize, std::get<1>(*it)+nsize, std::get<2>(*it)+nsize);
		}
	}

	return std::make_pair(nodes, triangles);
}