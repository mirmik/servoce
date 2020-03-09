#include <servoce/project.h>
#include <servoce/edge.h>

#include <GeomAPI_ProjectPointOnCurve.hxx>

servoce::point3 servoce::project(const servoce::point3& pnt, const servoce::edge_shape& tgt) 
{
 	GeomAPI_ProjectPointOnCurve algo(pnt.Pnt(), tgt.Curve());
 	return algo.NearestPoint();
}