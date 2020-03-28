#ifndef SERVOCE_WIRE_H
#define SERVOCE_WIRE_H

#include <servoce/shape.h>
#include <vector>

namespace servoce
{
	class curve3;

	class wire_shape : 
		public shape_typed<wire_shape> 
	{
	public:
		//wire_shape(TopoDS_Wire& arg) : shape(arg) {}
		wire_shape() {}
		wire_shape(const TopoDS_Wire& arg) : shape_typed((const TopoDS_Shape&)arg) {}
		wire_shape(servoce::shape&& oth) : wire_shape(oth.Wire()) {}

		face_shape fill();
	};

	wire_shape make_polysegment(const point3* data, size_t size, bool closed = false);
	wire_shape make_polysegment(const std::vector<point3>& vec, bool closed = false);
	
	shape make_helix(double pitch, double height, double radius, double angle = 0, bool leftHanded = false, bool newStyle = true);
	shape make_long_helix(double pitch, double height, double radius, double angle = 0, bool leftHanded = false);

	/// Сшить wire или edge между собой.
	wire_shape sew(const std::vector<const shape*>& arr);
	wire_shape make_wire(const std::vector<const shape*>& arr);

	curve3 extract_curve(const shape& wire);
	curve3 curve_adaptor(const shape& wire);

	edge_shape circle_edge(double r);
	edge_shape circle_edge(double r, double angle);
	edge_shape circle_edge(double r, double a1, double a2);

	edge_shape ellipse_edge(double r1, double r2);
	edge_shape ellipse_edge(double r1, double r2, double a1, double a2);
	
	wire_shape ngon_wire(double r, int n);
	wire_shape square_wire(double a, bool center = false);
	wire_shape rectangle_wire(double a, double b, bool center = false);
}

#endif