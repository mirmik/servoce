#ifndef SERVOCE_FACE_H
#define SERVOCE_FACE_H

#include <vector>
#include <servoce/shape.h>
#include <servoce/surface_algo.h>
#include <servoce/surface.h>

#include <BRepAdaptor_Surface.hxx>

class BRepPrimAPI_MakeSweep;

namespace servoce
{
	class face_shape : public shape, public surface_algo<face_shape>
	{
	public:
		using surfalgo = surface_algo<face_shape>;

		//edge_shape(TopoDS_Edge& arg) : shape(arg) {}
		face_shape(){}
		face_shape(const TopoDS_Face& arg) : shape((const TopoDS_Shape&)arg) {}
	
		BRepAdaptor_Surface AdaptorSurface() const;

		servoce::surface::surface surface() const;
	};

	face_shape make_face(const servoce::surface::surface& surf, double umin, double umax, double vmin, double vmax);
	face_shape make_face(const servoce::surface::surface& surf, std::pair<double,double> urange, std::pair<double, double> vrange);

	//prim2d
	shape circle(double r, bool wire = false);
	shape circle(double r, double angle, bool wire = false);
	shape circle(double r, double a1, double a2, bool wire = false);

	shape ellipse(double r1, double r2, bool wire = false);
	shape ellipse(double r1, double r2, double a1, double a2, bool wire = false);
	
	face_shape polygon(const servoce::point3* pnts, size_t size);
	face_shape polygon(const std::vector<servoce::point3>& pnts);
	shape ngon(double r, int n, bool wire = false);
	shape square(double a, bool center = false, bool wire = false);
	shape rectangle(double a, double b, bool center = false, bool wire = false);

	shape textshape(const std::string& text, const std::string fontpath, size_t size);
	face_shape infplane();

	//sweep2d
	//shape make_sweep(const servoce::shape& profile, const servoce::shape& path); //Не нужна.

	shape fillet2d(const shape& shp, double r, const std::vector<point3>& refs);
	shape fillet2d(const shape& shp, double r);
	face_shape chamfer2d(const shape& shp, double r, const std::vector<point3>& refs);
	face_shape chamfer2d(const shape& shp, double r);

	face_shape ruled_face(const shape& a, const shape& b);

	face_shape trivial_tube(const shape& spine, double r);
}

#endif