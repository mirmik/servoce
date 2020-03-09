#include <servoce/sweep.h>

using namespace servoce;

std::tuple<face_shape, edge_shape, edge_shape> servoce::make_tube(
    const servoce::edge_shape& shp, double radius, double tol, int cont, int maxdegree, int maxsegm
    )
{
	auto crv = servoce::circle_curve3(radius).rotZ(M_PI/2);
	auto slaw = servoce::law_evolved_section(crv, servoce::law_constant_function(1, crv.range()));
	auto llaw = servoce::law_spine_and_trihedron(shp, law_corrected_frenet_trihedron());

	auto surf = servoce::sweep_surface(slaw, llaw, tol, cont, maxdegree, maxsegm);
	auto strt_crv = surf.v_iso_curve(surf.vrange().first);
	auto fini_crv = surf.v_iso_curve(surf.vrange().second);

	//throw std::runtime_error("HERE2");
	auto sedge = make_edge(strt_crv);
	auto fedge = make_edge(fini_crv);
	auto face = make_face(surf);

	return std::make_tuple(face, sedge, fedge);
}

std::tuple<shell_shape, edge_shape, edge_shape> servoce::make_tube(
    const servoce::wire_shape& shp, double radius, double tol, int cont, int maxdegree, int maxsegm
    )
{
	std::vector<face_shape> faces;
	std::vector<edge_shape> strt;
	std::vector<edge_shape> fini;

	for ( auto& e : shp.edges() ) 
	{
		auto tpl = make_tube(e, radius, tol, cont, maxdegree, maxsegm);

		faces.push_back(std::get<0>(tpl));
		strt.push_back(std::get<1>(tpl));
		fini.push_back(std::get<2>(tpl));
	}

	return std::make_tuple(make_shell(faces), strt[0], fini[fini.size()-1]);
}