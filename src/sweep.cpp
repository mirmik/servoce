#include <servoce/sweep.h>
#include <map>

#include <GeomFill_Trihedron.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>

using namespace servoce;

// Труба вытягивает круглый профиль по заданному контуру.
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

// Труба по wire состоит из нескольких труб по edge
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


shape servoce::make_linear_extrude(const shape& base, const vector3& vec, bool center)
{
	if (center)
	{
		auto trs = translate(-vec / 2);
		return make_linear_extrude(trs(base), vec);
	}

	//Этот хак необходим из-за тенденции некоторых алгоритмов opencascade создавать SOLID тогда,
	//Когда можно было бы ожидать FACE
	if (base.Shape().ShapeType() == TopAbs_SOLID)
	{
		auto fcs = base.faces();

		if (fcs.size() == 1)
		{
			return BRepPrimAPI_MakePrism(fcs[0].Face(), vec.Vec()).Shape();
		}
		else
		{
			throw std::logic_error("linear_extrude doesn't work with solids");
		}
	}

	return BRepPrimAPI_MakePrism(base.Shape(), vec.Vec()).Shape();
}

shape servoce::make_linear_extrude(const shape& base, double z, bool center)
{
	return make_linear_extrude(base, vector3(0, 0, z), center);
}

servoce::shape servoce::shape::extrude(double z, bool center)
{
	return make_linear_extrude(*this, z, center);
}

servoce::shape servoce::shape::extrude(double x, double y, double z, bool center)
{
	return make_linear_extrude(*this, vector3(x, y, z), center);
}

servoce::shape servoce::shape::extrude(const vector3& vec, bool center)
{
	return make_linear_extrude(*this, vec, center);
}

shape servoce::make_pipe_0(const shape& profile, const shape& path)
{
	if (path.Shape().IsNull())
		Standard_Failure::Raise("Cannot sweep along empty spine");

	if (profile.Shape().IsNull())
		Standard_Failure::Raise("Cannot sweep empty profile");

	return BRepOffsetAPI_MakePipe(path.Wire_orEdgeToWire(), profile.Shape()).Shape();
}

shape servoce::make_pipe(const shape& profile, const shape& path,
                         const std::string mode, bool force_approx_c1)
{
	if (path.Shape().IsNull())
		Standard_Failure::Raise("Cannot sweep along empty spine");

	if (profile.Shape().IsNull())
		Standard_Failure::Raise("Cannot sweep empty profile");

	GeomFill_Trihedron tri;

	std::map<std::string, GeomFill_Trihedron> map =
	{
		{ "corrected_frenet", GeomFill_IsCorrectedFrenet },
		{ "fixed", GeomFill_IsFixed},
		{ "frenet", GeomFill_IsFrenet},
		{ "constant_normal", GeomFill_IsConstantNormal},
		{ "darboux", GeomFill_IsDarboux},
		{ "guide_ac", GeomFill_IsGuideAC},
		{ "guide_plan", GeomFill_IsGuidePlan},
		{ "guide_ac_with_contact", GeomFill_IsGuideACWithContact},
		{ "guide_plan_with_contact", GeomFill_IsGuidePlanWithContact},
		{ "discrete_trihedron", GeomFill_IsDiscreteTrihedron}
	};

	try
	{
		tri = map.at(mode);
	}

	catch (...)
	{
		throw std::runtime_error("servoce::make_pipe: undefined mode");
	}

	return BRepOffsetAPI_MakePipe(path.Wire_orEdgeToWire(), profile.Shape(), tri, force_approx_c1).Shape();
}

shape servoce::make_pipe_shell(
    const std::vector<const shape*>& profile,
    const shape& path,
    bool frenet,
    bool approx_c1,
    const vector3& binormal,
    const vector3& parallel,
    bool discrete,
    bool solid,
    int transition
)
{
	BRepOffsetAPI_MakePipeShell mkPipeShell(path.Wire_orEdgeToWire());

	BRepBuilderAPI_TransitionMode transMode;

	switch (transition)
	{
		case 1: transMode = BRepBuilderAPI_RightCorner;
			break;

		case 2: transMode = BRepBuilderAPI_RoundCorner;
			break;

		default: transMode = BRepBuilderAPI_Transformed;
			break;
	}

	mkPipeShell.SetMode(frenet);
	mkPipeShell.SetTransitionMode(transMode);
	mkPipeShell.SetForceApproxC1(approx_c1);

	if (!binormal.iszero())
		mkPipeShell.SetMode(binormal.Dir());

	if (!parallel.iszero())
		mkPipeShell.SetMode(gp_Ax2(gp_Pnt(0, 0, 0), parallel.Dir()));

	if (discrete)
		mkPipeShell.SetDiscreteMode();

	for (auto a : profile)
		mkPipeShell.Add(a->Wire_orEdgeToWire());

	if (!mkPipeShell.IsReady()) std::logic_error("shape is not ready to build");

	mkPipeShell.Build();

	if (solid)
		mkPipeShell.MakeSolid();

	return mkPipeShell.Shape();
}

