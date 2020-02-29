#ifndef SERVOCE_TRANSFORMABLE_IMPL_H
#define SERVOCE_TRANSFORMABLE_IMPL_H


#include <servoce/geombase.h>
#include <servoce/trans.h>

template<class T> T servoce::transformable<T>::transform(const general_transformation & trans) const
{
	(void) trans;
	throw std::runtime_error("general transformation not supported for that type");
}


/*template<class T> T servoce::transformable<T>::transform(const transformation & trans) const
{
	(void) trans;
	throw std::runtime_error("copy transformation not supported for that type");
}*/

template<class T> T servoce::transformable<T>::self_transform(const transformation & trans)
{
	(void) trans;
	throw std::runtime_error("self transformation not supported for that type");
}

// Translation API: (translate and move is same)
template<class T> T servoce::transformable<T>::translate(double x, double y, double z) { return transform(servoce::translate(x, y, z)); }
template<class T> T servoce::transformable<T>::translate(vector3 v) { return transform(servoce::translate(v.x, v.y, v.z)); }
template<class T> T servoce::transformable<T>::translateX(double x) { return translate(x, 0, 0); }
template<class T> T servoce::transformable<T>::translateY(double y) { return translate(0, y, 0); }
template<class T> T servoce::transformable<T>::translateZ(double z) { return translate(0, 0, z); }

template<class T> T servoce::transformable<T>::move(double x, double y, double z) { return translate(x, y, z); }
template<class T> T servoce::transformable<T>::move(vector3 v) { return translate(v.x, v.y, v.z); }
template<class T> T servoce::transformable<T>::moveX(double x) { return translate(x, 0, 0); }
template<class T> T servoce::transformable<T>::moveY(double y) { return translate(0, y, 0); }
template<class T> T servoce::transformable<T>::moveZ(double z) { return translate(0, 0, z); }

// mnemonics for translate operations:
template<class T> T servoce::transformable<T>::up(double z) 		{ return translate( 0, 0, z); }
template<class T> T servoce::transformable<T>::down(double z) 	{ return translate( 0, 0, -z); }
template<class T> T servoce::transformable<T>::forw(double y) 	{ return translate( 0, y, 0); }
template<class T> T servoce::transformable<T>::back(double y) 	{ return translate( 0, -y, 0); }
template<class T> T servoce::transformable<T>::right(double x) 	{ return translate( x, 0, 0); }
template<class T> T servoce::transformable<T>::left(double x) 	{ return translate(-x, 0, 0); }

// restricted translation api:
template<class T> T servoce::transformable<T>::movX(double x) { return translate(x, 0, 0); }
template<class T> T servoce::transformable<T>::movY(double y) { return translate(0, y, 0); }
template<class T> T servoce::transformable<T>::movZ(double z) { return translate(0, 0, z); }

// Rotation API:
template<class T> T servoce::transformable<T>::rotate(double a, vector3 vec) { return transform(servoce::rotate(a, vec)); }
template<class T> T servoce::transformable<T>::rotate(double x, double y, double z) { return transform(servoce::rotate(x, y, z)); }
template<class T> T servoce::transformable<T>::rotateX(double a) { return transform(servoce::rotateX(a)); }
template<class T> T servoce::transformable<T>::rotateY(double a) { return transform(servoce::rotateY(a)); }
template<class T> T servoce::transformable<T>::rotateZ(double a) { return transform(servoce::rotateZ(a)); }

// restricted rotation api:
template<class T> T servoce::transformable<T>::rot(vector3 vec, double a) { return transform(servoce::rotate(a, vec)); }
template<class T> T servoce::transformable<T>::rot(double x, double y, double z) { return transform(servoce::rotate(x, y, z)); }
template<class T> T servoce::transformable<T>::rotX(double a) { return transform(servoce::rotateX(a)); }
template<class T> T servoce::transformable<T>::rotY(double a) { return transform(servoce::rotateY(a)); }
template<class T> T servoce::transformable<T>::rotZ(double a) { return transform(servoce::rotateZ(a)); }

// Mirror API:
template<class T> T servoce::transformable<T>::mirrorX() { return transform(servoce::mirrorX()); }
template<class T> T servoce::transformable<T>::mirrorY() { return transform(servoce::mirrorY()); }
template<class T> T servoce::transformable<T>::mirrorZ() { return transform(servoce::mirrorZ()); }
template<class T> T servoce::transformable<T>::mirrorXY() { return transform(servoce::mirrorXY()); }
template<class T> T servoce::transformable<T>::mirrorYZ() { return transform(servoce::mirrorYZ()); }
template<class T> T servoce::transformable<T>::mirrorXZ() { return transform(servoce::mirrorXZ()); }

// Scale API:
template<class T> T servoce::transformable<T>::scale(double s, point3 center) { return transform(servoce::scale(s, center)); }
template<class T> T servoce::transformable<T>::scaleX(double s) { return transform(servoce::scaleX(s)); }
template<class T> T servoce::transformable<T>::scaleY(double s) { return transform(servoce::scaleY(s)); }
template<class T> T servoce::transformable<T>::scaleZ(double s) { return transform(servoce::scaleZ(s)); }
template<class T> T servoce::transformable<T>::scaleXY(double x, double y) { return transform(servoce::scaleXY(x, y)); }
template<class T> T servoce::transformable<T>::scaleYZ(double y, double z) { return transform(servoce::scaleYZ(y, z)); }
template<class T> T servoce::transformable<T>::scaleXZ(double x, double z) { return transform(servoce::scaleXZ(x, z)); }
template<class T> T servoce::transformable<T>::scaleXYZ(double x, double y, double z) { return transform(servoce::scaleXYZ(x, y, z)); }


#endif