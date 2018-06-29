#ifndef ZENGEOM_TOPO_H
#define ZENGEOM_TOPO_H

#include <iostream>
#include <memory>
#include <set>
#include <servoce/boolops.h>
#include <servoce/trans.h>

class TopoDS_Shape;
class TopoDS_Solid;
class TopoDS_Wire;
class TopoDS_Face;
class TopoDS_Vertex;

class gp_Vec;
class gp_Pnt;

namespace servoce {
	struct shape {
		TopoDS_Shape* m_shp;
		shape();
		shape(const TopoDS_Shape& shp);
		shape(const shape& oth);
		virtual ~shape();

		solid to_solid();
		wire to_wire();
		face to_face();

		void dump(std::ostream& out) const;
		void load(std::istream& in);

		std::string string_dump() const;
		static shape restore_string_dump(const std::string& in);

		TopoDS_Shape& Shape();
		const TopoDS_Shape& Shape() const;
	};

	template<typename Self>
	struct can_trans {
		Self transform(const trans::transformation& trans) { 
			Self& self = static_cast<Self&>(*this); 
			return trans(self); 
		}
		Self translate(double x, double y, double z) { 
			return transform(trans::translate(x,y,z)); 
		}
		//Self translate(double x, double y) { 
		//	return transform(trans::translate{x,y,0}); }
		Self rotate(double ax, double ay, double az, double angle) { return transform(trans::axrotation(ax,ay,az,angle)); }
		Self up(double z) { return translate(0,0,z); }
		Self down(double z) { return translate(0,0,-z); }
		Self forw(double y) { return translate(0,y,0); }
		Self back(double y) { return translate(0,-y,0); }
		Self right(double x) { return translate(x,0,0); }
		Self left(double x) { return translate(-x,0,0); }

		Self rotateX(double a) { 
			return transform(trans::rotateX(a)); 
		}
		Self rotateY(double a) { return transform(trans::rotateY(a)); }
		Self rotateZ(double a) { return transform(trans::rotateZ(a)); }

		Self mirrorX() { return transform(trans::mirrorX()); }
		Self mirrorY() { return transform(trans::mirrorY()); }
		Self mirrorZ() { return transform(trans::mirrorZ()); }

		Self mirrorXY() { return transform(trans::mirrorXY()); }
		Self mirrorYZ() { return transform(trans::mirrorYZ()); }
		Self mirrorXZ() { return transform(trans::mirrorXZ()); }
	};

	template<typename Self>
	struct can_boolops {
		Self operator+(const shape& oth) const { const Self& self = static_cast<const Self&>(*this); return boolops::make_union(self, oth); }
		Self operator-(const shape& oth) const { const Self& self = static_cast<const Self&>(*this); return boolops::make_difference(self, oth); }
		Self operator^(const shape& oth) const { const Self& self = static_cast<const Self&>(*this); return boolops::make_intersect(self, oth); }
	};

	struct solid : public shape, public can_trans<solid>, public can_boolops<solid> {
		solid();
		solid(const TopoDS_Shape& shp);
		const TopoDS_Solid& Solid() const;
		solid fillet(double r, const std::vector<int>& nums);
		TopoDS_Solid& Solid();
	};

	struct face : public shape, public can_trans<face>, public can_boolops<face> {
		face();
		face(const TopoDS_Shape& shp);
		const TopoDS_Face& Face() const;
		TopoDS_Face& Face();
		face fillet(double r, const std::vector<int>& nums);
		std::vector<servoce::wire> wires();
	};

	struct wire : public shape, public can_trans<wire>, public can_boolops<wire> {
		wire();
		wire(const TopoDS_Shape& shp);
		const TopoDS_Wire& Wire() const;
		TopoDS_Wire& Wire();
		face to_face();
	};

	struct vector3 : public can_trans<vector3> {
		double x, y, z;
		vector3() {}
		vector3(const gp_Vec& pnt) {}
		vector3(double x, double y) : x(x), y(y), z(0) {}
		vector3(double x, double y, double z) : x(x), y(y), z(z) {}
		gp_Vec Vec() const;
		bool operator==(const vector3& oth) const { return oth.x == x && oth.y == y && oth.z == z; }
		bool operator!=(const vector3& oth) const { return oth.x != x || oth.y != y || oth.z != z; }
		vector3 operator-() const { return vector3(-x,-y,-z); }
		vector3 operator/(double a) const { return vector3(x/a,y/a,z/a); }
	};

	struct point3 : public can_trans<point3> {
		double x, y, z;
		point3() {}
		point3(const gp_Pnt& pnt) {}
		point3(double x, double y) : x(x), y(y), z(0) {}
		point3(double x, double y, double z) : x(x), y(y), z(z) {}
		gp_Pnt Pnt() const;
		TopoDS_Vertex Vtx() const;
	};
}

#endif