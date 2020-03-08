#include <servoce/servoce.h>
#include <mutex>

#include <AIS_Shape.hxx>
#include <local/OccViewContext.h>
#include <BRepBuilderAPI_Copy.hxx>

extern std::recursive_mutex viewrecursive_mutex;

servoce::scene::scene() : vwer(new servoce::viewer()) {}

std::shared_ptr<servoce::interactive_object> servoce::scene::add(std::shared_ptr<servoce::interactive_object> iobj)
{
	iobjs.push_back(iobj);
	vwer->display(*iobj);
	iobj->scn=this;
	return iobj;
}

std::shared_ptr<servoce::interactive_object> servoce::scene::add(const servoce::shape& shp, servoce::color color)
{
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	auto iobj = std::make_shared<servoce::interactive_object>(shp, color);
	iobj->scn=this;
	return add(iobj);
}

std::shared_ptr<servoce::interactive_object> servoce::scene::add(const servoce::point3& pnt, servoce::color color)
{
	std::lock_guard<std::recursive_mutex> lock(viewrecursive_mutex);
	TopoDS_Vertex vtx = pnt.Vtx();
	auto iobj = std::make_shared<servoce::interactive_object>(servoce::shape(vtx), color);
	iobj->scn=this;
	return add(iobj);
}

AIS_InteractiveContext* servoce::scene::InteractiveContext()
{
	return this->vwer->occ->m_context.get();
}

servoce::boundbox servoce::scene::bbox() const 
{
	boundbox bbox = (*iobjs.begin())->bounding_box();

	for (auto& i: iobjs) 
	{
		bbox = bbox.add(i->bounding_box());
	}

	return bbox;
}