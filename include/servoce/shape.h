#ifndef SERVOCE_TOPO_H
#define SERVOCE_TOPO_H

//#include <TopoDS_Shape.hxx>

#include <iostream>
#include <memory>
#include <set>

#include <servoce/geombase.h>
#include <servoce/boolops.h>
#include <servoce/trans.h>
#include <servoce/transformable.h>
#include <servoce/boundbox.h>

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
	class boundbox;

	enum topoenum
	{
		vertex,
		edge,
		wire,
		solid,
		face,
		compound
	};

	class shape : public servoce::transformable<shape>
	{
	public:
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
		TopoDS_Edge Edge_OrOneEdgedWireToEdge() const;

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

		point3 center() const;
		vector3 cmradius() const;
		double mass() const;
		matrix33 matrix_of_inertia() const;
		std::tuple<double, double, double> static_moments () const;
		double moment_of_inertia(const servoce::vector3& axis) const;
		double radius_of_gyration(const servoce::vector3& axis) const;

		servoce::shape infill_face(); ///< Превращает замкнутый двумерный контур в 2d объект

		servoce::shape operator+(const shape& oth) const { return servoce::make_union(*this, oth); }
		servoce::shape operator-(const shape& oth) const { return servoce::make_difference(*this, oth); }
		servoce::shape operator^(const shape& oth) const { return servoce::make_intersect(*this, oth); }

		servoce::shape extrude(double z, bool center = false);
		servoce::shape extrude(const vector3& vec, bool center = false);
		servoce::shape extrude(double x, double y, double z, bool center = false);

		std::vector<servoce::point3> vertices() const;
		std::vector<servoce::shape> solids() const;
		std::vector<servoce::shape> shells() const;
		std::vector<servoce::shape> compounds() const;
		std::vector<servoce::shape> compsolids() const;
		std::vector<servoce::shape> faces() const;
		std::vector<servoce::shape> wires() const;
		std::vector<servoce::shape> edges() const;

		std::vector<TopoDS_Edge> Edges() const;

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
		std::string shapetype_as_string() const;

		void print_topo_dump();

		boundbox bounding_box();
	};

	class wire_shape : public shape
	{
	public:
		//wire_shape(TopoDS_Wire& arg) : shape(arg) {}
		wire_shape() {}
		wire_shape(const TopoDS_Wire& arg) : shape((const TopoDS_Shape&)arg) {}
	};

	shape	near_face		(const shape& shp, const point3& pnt);
	shape	near_edge		(const shape& shp, const point3& pnt);
	shape 	near_vertex		(const shape& shp, const point3& pnt);
}

#endif