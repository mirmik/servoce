#ifndef SERVOCE_TRANSFORMABLE_IMPL_H
#define SERVOCE_TRANSFORMABLE_IMPL_H

#include <servoce/geombase.h>
#include <servoce/trans.h>

// Translation API: (translate and move is same)
template<class T, class Ret> Ret servoce::transformable<T,Ret>::translate(double x, double y, double z) { return self().transform(servoce::translate(x, y, z)); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::translate(vector3 v) { return self().transform(servoce::translate(v.x, v.y, v.z)); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::translateX(double x) { return translate(x, 0, 0); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::translateY(double y) { return translate(0, y, 0); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::translateZ(double z) { return translate(0, 0, z); }

template<class T, class Ret> Ret servoce::transformable<T,Ret>::move(double x, double y, double z) { return translate(x, y, z); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::move(vector3 v) { return translate(v.x, v.y, v.z); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::move(point3 v) { return translate(v.x, v.y, v.z); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::moveX(double x) { return translate(x, 0, 0); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::moveY(double y) { return translate(0, y, 0); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::moveZ(double z) { return translate(0, 0, z); }

// mnemonics for translate operations:
template<class T, class Ret> Ret servoce::transformable<T,Ret>::up(double z) 		{ return translate( 0, 0, z); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::down(double z) 	{ return translate( 0, 0, -z); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::forw(double y) 	{ return translate( 0, y, 0); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::back(double y) 	{ return translate( 0, -y, 0); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::right(double x) 	{ return translate( x, 0, 0); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::left(double x) 	{ return translate(-x, 0, 0); }

// restricted translation api:
template<class T, class Ret> Ret servoce::transformable<T,Ret>::movX(double x) { return translate(x, 0, 0); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::movY(double y) { return translate(0, y, 0); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::movZ(double z) { return translate(0, 0, z); }

// Rotation API:
template<class T, class Ret> Ret servoce::transformable<T,Ret>::rotate(double a, vector3 vec) { return self().transform(servoce::rotate(a, vec)); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::rotate(double x, double y, double z) { return self().transform(servoce::rotate(x, y, z)); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::rotateX(double a) { return self().transform(servoce::rotateX(a)); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::rotateY(double a) { return self().transform(servoce::rotateY(a)); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::rotateZ(double a) { return self().transform(servoce::rotateZ(a)); }

// restricted rotation api:
template<class T, class Ret> Ret servoce::transformable<T,Ret>::rot(vector3 vec, double a) { return self().transform(servoce::rotate(a, vec)); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::rot(double x, double y, double z) { return self().transform(servoce::rotate(x, y, z)); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::rotX(double a) { return self().transform(servoce::rotateX(a)); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::rotY(double a) { return self().transform(servoce::rotateY(a)); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::rotZ(double a) { return self().transform(servoce::rotateZ(a)); }

// Mirror API:
template<class T, class Ret> Ret servoce::transformable<T,Ret>::mirrorO() { return self().transform(servoce::mirrorO()); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::mirrorX() { return self().transform(servoce::mirrorX()); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::mirrorY() { return self().transform(servoce::mirrorY()); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::mirrorZ() { return self().transform(servoce::mirrorZ()); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::mirrorXY() { return self().transform(servoce::mirrorXY()); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::mirrorYZ() { return self().transform(servoce::mirrorYZ()); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::mirrorXZ() { return self().transform(servoce::mirrorXZ()); }

// Scale API:
template<class T, class Ret> Ret servoce::transformable<T,Ret>::scale(double s, point3 center) { return self().transform(servoce::scale(s, center)); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::scaleX(double s) { return self().transform(servoce::scaleX(s)); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::scaleY(double s) { return self().transform(servoce::scaleY(s)); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::scaleZ(double s) { return self().transform(servoce::scaleZ(s)); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::scaleXY(double x, double y) { return self().transform(servoce::scaleXY(x, y)); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::scaleYZ(double y, double z) { return self().transform(servoce::scaleYZ(y, z)); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::scaleXZ(double x, double z) { return self().transform(servoce::scaleXZ(x, z)); }
template<class T, class Ret> Ret servoce::transformable<T,Ret>::scaleXYZ(double x, double y, double z) { return self().transform(servoce::scaleXYZ(x, y, z)); }

#endif