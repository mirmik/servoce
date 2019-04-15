#ifndef SERVOCE_TOPO_H
#define SERVOCE_TOPO_H

//#include <TopoDS_Shape.hxx>

#include <iostream>
#include <memory>
#include <set>
#include <servoce/boolops.h>
#include <servoce/trans.h>
#include <servoce/geombase.h>

class TopoDS_Shape;
class TopoDS_Shell;
class TopoDS_Solid;
class TopoDS_Vertex;
class TopoDS_Edge;
class TopoDS_Wire;
class TopoDS_Face;
class TopoDS_Compound;

namespace servoce
{
	enum topoenum
	{
		vertex,
		edge,
		wire,
		solid,
		face,
		compound
	};

	struct shape
	{
		TopoDS_Shape* m_shp = nullptr;
		shape() {};
		shape(TopoDS_Shape* shp);
		shape(const TopoDS_Shape& shp);
		shape(const shape& oth);
		shape(shape&& oth);
		~shape();

		shape& operator= (const shape& oth);
		shape& operator= (const TopoDS_Shape& shp);
		shape& operator= (shape&& oth);

		shape fill();

		//solid to_solid();
		//wire to_wire();
		//face to_face();

		void dump(std::ostream& out) const;
		void load(std::istream& in);

		TopoDS_Shape& Shape();
		const TopoDS_Shape& Shape() const;

		TopoDS_Face& Face();
		const TopoDS_Face& Face() const;

		TopoDS_Edge& Edge();
		const TopoDS_Edge& Edge() const;

		TopoDS_Vertex& Vertex();
		const TopoDS_Vertex& Vertex() const;

		TopoDS_Wire& Wire();
		const TopoDS_Wire& Wire() const;
		TopoDS_Wire Wire_orEdgeToWire() const;

		TopoDS_Shell& Shell();
		const TopoDS_Shell& Shell() const;

		TopoDS_Solid& Solid();
		const TopoDS_Solid& Solid() const;

		TopoDS_Compound& Compound();
		const TopoDS_Compound& Compound() const;

		shape transform(const transformation& trans) { return trans(*this); }
		
		shape translate(double x, double y, double z) { return transform(servoce::translate(x, y, z)); }
		shape up(double z) { return translate(0, 0, z); }
		shape down(double z) { return translate(0, 0, -z); }
		shape forw(double y) { return translate(0, y, 0); }
		shape back(double y) { return translate(0, -y, 0); }
		shape right(double x) { return translate(x, 0, 0); }
		shape left(double x) { return translate(-x, 0, 0); }

		shape rotate(vector3 vec, double a) { return transform(servoce::rotate(vec, a)); }
		shape rotateX(double a) { return transform(servoce::rotateX(a)); }
		shape rotateY(double a) { return transform(servoce::rotateY(a)); }
		shape rotateZ(double a) { return transform(servoce::rotateZ(a)); }

		shape mirrorX() { return transform(servoce::mirrorX()); }
		shape mirrorY() { return transform(servoce::mirrorY()); }
		shape mirrorZ() { return transform(servoce::mirrorZ()); }

		shape mirrorXY() { return transform(servoce::mirrorXY()); }
		shape mirrorYZ() { return transform(servoce::mirrorYZ()); }
		shape mirrorXZ() { return transform(servoce::mirrorXZ()); }

		shape scale(double s, point3 center = point3()) { return transform(servoce::scale(s, center)); }
		point3 center();

		servoce::shape infill_face(); ///< Превращает замкнутый двумерный контур в 2d объект

		servoce::shape operator+(const shape& oth) const { return servoce::make_union(*this, oth); }
		servoce::shape operator-(const shape& oth) const { return servoce::make_difference(*this, oth); }
		servoce::shape operator^(const shape& oth) const { return servoce::make_intersect(*this, oth); }

		servoce::shape extrude(double z, bool center = false);
		servoce::shape extrude(const vector3& vec, bool center = false);
		servoce::shape extrude(double x, double y, double z, bool center = false);

		std::vector<servoce::point3> vertices() const;
		std::vector<servoce::shape> solids() const;
		std::vector<servoce::shape> faces() const;
		std::vector<servoce::shape> wires() const;
		std::vector<servoce::shape> edges() const;

		shape fillet(double r, const std::vector<point3>& refs);
		shape fillet(double r);
		shape chamfer(double r, const std::vector<point3>& refs);
		shape chamfer(double r);
		shape fillet2d(double r, const std::vector<point3>& refs);
		shape fillet2d(double r);
		shape chamfer2d(double r, const std::vector<point3>& refs);
		shape chamfer2d(double r);

		std::pair<servoce::point3, servoce::point3> sfvertex();
		bool is_closed(); // for wire

		topoenum type();
		std::string shapetype_as_string();
	};

	class BoundBox 
	{
		double xmin, xmax, xdim;
		double ymin, ymax, ydim;
		double zmin, zmax, zdim;

		BoundBox(const servoce::shape& shp);
	};

	shape	near_face		(const shape& shp, const point3& pnt);
	shape	near_edge		(const shape& shp, const point3& pnt);
	shape 	near_vertex		(const shape& shp, const point3& pnt);
}

#endif