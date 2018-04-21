#include <servoce/boolops.h>
#include <local/util.h>

#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>

servoce::solid servoce::boolops::make_union(const solid& a, const solid& b) {
	return BRepAlgoAPI_Fuse(a.Shape(), b.Shape()).Shape();
}

servoce::solid servoce::boolops::make_difference(const solid& a, const solid& b) {
	return BRepAlgoAPI_Cut(a.Shape(), b.Shape()).Shape();
}

servoce::solid servoce::boolops::make_intersect(const solid& a, const solid& b) {
	return BRepAlgoAPI_Common(a.Shape(), b.Shape()).Shape();
}