#include <servoce/servoce.h>
#include <mutex>

#include <nos/trace.h>

#include <AIS_Shape.hxx>
#include <local/OccViewContext.h>
#include <BRepBuilderAPI_Copy.hxx>

extern std::recursive_mutex viewrecursive_mutex;

servoce::scene::scene() : vwer(new servoce::viewer()) {}

//#define uassert(e) if (!(e)) { printf("assert: %s\n", #e); exit(-1); }

std::vector<servoce::shape> servoce::scene::shapes_array()
{
	TRACE();
	std::vector<servoce::shape> arr;
	arr.reserve(shape_views.size());
	for (auto& v : shape_views) arr.emplace_back(v->shape());
	return arr;
}

std::vector<servoce::color> servoce::scene::color_array()
{
	TRACE();
	std::vector<servoce::color> arr;
	arr.reserve(shape_views.size());
	for (auto& v : shape_views) arr.emplace_back(v->color());
	return arr;
}

std::shared_ptr<servoce::shape_view> servoce::scene::add(const servoce::shape& shp, servoce::color color)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	shape_views.emplace_back(
	    std::make_shared<servoce::shape_view>(shp, color, this));
	vwer->display(*shape_views.back());
	return shape_views.back();
}

std::shared_ptr<servoce::shape_view> servoce::scene::add(const servoce::point3& pnt, servoce::color color)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	TopoDS_Vertex vtx = pnt.Vtx();
	shape_views.emplace_back(
	    std::make_shared<servoce::shape_view>(servoce::shape(vtx), color, this));
	vwer->display(*shape_views.back());
	return shape_views.back();
}

void servoce::scene::append(const servoce::scene& scn)
{
	TRACE();
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	for (const auto& shpview : scn.shape_views)
		add(shpview->shape(), shpview->color());
}

AIS_InteractiveContext* servoce::scene::InteractiveContext() 
{
	return this->vwer->occ->m_context.get();
}