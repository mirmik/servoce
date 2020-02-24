#ifndef SERVOCE_TRANSFORMABLE_H
#define SERVOCE_TRANSFORMABLE_H

#include <servoce/trans.h>
#include <servoce/geombase.h>

namespace servoce 
{
	// Interface for transformation support.
	template <class T>
	class transformable 
	{
	public:
		T transform(const transformation& trans) { return trans((const T&)*this); }
		T transform(const general_transformation& trans) { return trans((const T&)*this); }

		// Translation API: (translate and move is same)
		T translate(double x, double y, double z) { return transform(servoce::translate(x, y, z)); }
		T translate(vector3 v) { return transform(servoce::translate(v.x, v.y, v.z)); }
		T translateX(double x) { return translate(x, 0, 0); }
		T translateY(double y) { return translate(0, y, 0); }
		T translateZ(double z) { return translate(0, 0, z); }

		T move(double x, double y, double z) { return translate(x, y, z); }
		T move(vector3 v) { return translate(v.x, v.y, v.z); }
		T moveX(double x) { return translate(x, 0, 0); }
		T moveY(double y) { return translate(0, y, 0); }
		T moveZ(double z) { return translate(0, 0, z); }

		// mnemonics for translate operations:
		T up(double z) 		{ return translate( 0, 0, z); }
		T down(double z) 	{ return translate( 0, 0,-z); }
		T forw(double y) 	{ return translate( 0, y, 0); }
		T back(double y) 	{ return translate( 0,-y, 0); }
		T right(double x) 	{ return translate( x, 0, 0); }
		T left(double x) 	{ return translate(-x, 0, 0); }

		// restricted translation api:
		T movX(double x) { return translate(x, 0, 0); }
		T movY(double y) { return translate(0, y, 0); }
		T movZ(double z) { return translate(0, 0, z); }

		// Rotation API:
		T rotate(double a, vector3 vec) { return transform(servoce::rotate(a, vec)); }
		T rotate(double x, double y, double z) { return transform(servoce::rotate(x,y,z)); }
		T rotateX(double a) { return transform(servoce::rotateX(a)); }
		T rotateY(double a) { return transform(servoce::rotateY(a)); }
		T rotateZ(double a) { return transform(servoce::rotateZ(a)); }

		// restricted rotation api:
		T rot(vector3 vec, double a) { return transform(servoce::rotate(a, vec)); }
		T rot(double x, double y, double z) { return transform(servoce::rotate(x,y,z)); }
		T rotX(double a) { return transform(servoce::rotateX(a)); }
		T rotY(double a) { return transform(servoce::rotateY(a)); }
		T rotZ(double a) { return transform(servoce::rotateZ(a)); }

		// Mirror API:
		T mirrorX() { return transform(servoce::mirrorX()); }
		T mirrorY() { return transform(servoce::mirrorY()); }
		T mirrorZ() { return transform(servoce::mirrorZ()); }
		T mirrorXY() { return transform(servoce::mirrorXY()); }
		T mirrorYZ() { return transform(servoce::mirrorYZ()); }
		T mirrorXZ() { return transform(servoce::mirrorXZ()); }

		// Scale API:
		T scale(double s, point3 center = point3()) { return transform(servoce::scale(s, center)); }
		T scaleX(double s) { return transform(servoce::scaleX(s)); }
		T scaleY(double s) { return transform(servoce::scaleY(s)); }
		T scaleZ(double s) { return transform(servoce::scaleZ(s)); }
		T scaleXY(double x, double y) { return transform(servoce::scaleXY(x, y)); }
		T scaleYZ(double y, double z) { return transform(servoce::scaleYZ(y, z)); }
		T scaleXZ(double x, double z) { return transform(servoce::scaleXZ(x, z)); }
		T scaleXYZ(double x, double y, double z) { return transform(servoce::scaleXYZ(x, y, z)); }
	};
}

#endif