#ifndef SERVOCE_FACE_H
#define SERVOCE_FACE_H

#include <vector>
#include <servoce/shape.h>
#include <servoce/surface_algo.h>
#include <servoce/surface.h>

#include <BRepAdaptor_Surface.hxx>
#include <BRep_Tool.hxx>

class BRepPrimAPI_MakeSweep;

namespace servoce
{
	class face_shape :
		public shape_typed<face_shape>,
		public surface_algo<face_shape>
	{
	public:
		using surfalgo = surface_algo<face_shape>;

		Handle(Geom_Surface) surf_saver;

		//edge_shape(TopoDS_Edge& arg) : shape(arg) {}
	public:
		face_shape() {}
		face_shape(const face_shape& oth) : shape_typed(oth), surf_saver(oth.surf_saver) {}
		face_shape(servoce::shape&& oth) : face_shape(oth.Face()) {}
		face_shape(const TopoDS_Face& arg) : shape_typed((const TopoDS_Face&)arg) { surf_saver = Surface(); }
		virtual ~face_shape() {}

		BRepAdaptor_Surface AdaptorSurface() const;
		Handle(Geom_Surface) Surface() { return BRep_Tool::Surface(Face()); }

		servoce::surface surface() const;

		//	face_shape transform(const transformation& trans) const { return shape::transform(trans).as_face(); }
		//	face_shape transform(const general_transformation& trans) const { return shape::transform(trans).as_face(); }
	};

	face_shape make_face(const std::vector<const servoce::shape*>& vec);

	face_shape make_face(const servoce::surface& surf);
	face_shape make_face(const servoce::surface& surf, double umin, double umax, double vmin, double vmax);
	face_shape make_face(const servoce::surface& surf, std::pair<double, double> urange, std::pair<double, double> vrange);

	face_shape fix_face(const face_shape& face);

	//prim2d
	face_shape circle(double r);
	face_shape circle(double r, double angle);
	face_shape circle(double r, double a1, double a2);

	face_shape ellipse(double r1, double r2);
	face_shape ellipse(double r1, double r2, double a1, double a2);

	face_shape ngon(double r, int n);
	face_shape square(double a, bool center = false);
	face_shape rectangle(double a, double b, bool center = false);

	face_shape polygon(const servoce::point3* pnts, size_t size);
	face_shape polygon(const std::vector<servoce::point3>& pnts);

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

	face_shape interpolate2(const std::vector<std::vector<point3>>& refs);
}

#endif