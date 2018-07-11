#ifndef SERVOCE_TOPO_H
#define SERVOCE_TOPO_H

//#include <TopoDS_Shape.hxx>

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
class TopoDS_Compound;

class gp_Vec;
class gp_Pnt;

namespace servoce {
	struct vector3 {
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

	struct point3 {
		double x, y, z;
		point3() {}
		point3(const gp_Pnt& pnt) {}
		point3(double x, double y) : x(x), y(y), z(0) {}
		point3(double x, double y, double z) : x(x), y(y), z(z) {}
		gp_Pnt Pnt() const;
		TopoDS_Vertex Vtx() const;
	};

	struct shape {
		TopoDS_Shape* m_shp;
		shape(){};
		shape(TopoDS_Shape* shp);
		shape(const TopoDS_Shape& shp);
		shape(const shape& oth);
		shape(shape&& oth);
		~shape();

		shape& operator= (const shape& oth);
		shape& operator= (shape&& oth);

		shape fillet(double r, const std::vector<int>& nums);

		//solid to_solid();
		//wire to_wire();
		//face to_face();

		void dump(std::ostream& out) const;
		void load(std::istream& in);

		std::string string_dump() const;
		static shape restore_string_dump(const std::string& in);

		TopoDS_Shape& Shape();
		const TopoDS_Shape& Shape() const;

		TopoDS_Face& Face();
		const TopoDS_Face& Face() const;

		TopoDS_Wire& Wire();
		const TopoDS_Wire& Wire() const;

		TopoDS_Solid& Solid();
		const TopoDS_Solid& Solid() const;

		TopoDS_Compound& Compound();
		const TopoDS_Compound& Compound() const;

		shape transform(const transformation& trans) { return trans(*this); }
		shape translate(double x, double y, double z) { return transform(servoce::translate(x,y,z)); }
		shape rotate(double ax, double ay, double az, double angle) { return transform(servoce::axrotation(ax,ay,az,angle)); }

		shape up(double z) { return translate(0,0,z); }
		shape down(double z) { return translate(0,0,-z); }
		shape forw(double y) { return translate(0,y,0); }
		shape back(double y) { return translate(0,-y,0); }
		shape right(double x) { return translate(x,0,0); }
		shape left(double x) { return translate(-x,0,0); }

		shape rotateX(double a) { return transform(servoce::rotateX(a)); }
		shape rotateY(double a) { return transform(servoce::rotateY(a)); }
		shape rotateZ(double a) { return transform(servoce::rotateZ(a)); }

		shape mirrorX() { return transform(servoce::mirrorX()); }
		shape mirrorY() { return transform(servoce::mirrorY()); }
		shape mirrorZ() { return transform(servoce::mirrorZ()); }

		shape mirrorXY() { return transform(servoce::mirrorXY()); }
		shape mirrorYZ() { return transform(servoce::mirrorYZ()); }
		shape mirrorXZ() { return transform(servoce::mirrorXZ()); }

		servoce::shape infill_face(); ///< Превращает замкнутый двумерный контур в 2d объект

		servoce::shape operator+(const shape& oth) const { return servoce::make_union(*this, oth); }
		servoce::shape operator-(const shape& oth) const { return servoce::make_difference(*this, oth); }
		servoce::shape operator^(const shape& oth) const { return servoce::make_intersect(*this, oth); }
	
		servoce::shape extrude(double z, bool center = false);
		servoce::shape extrude(const vector3& vec, bool center = false);
		servoce::shape extrude(double x, double y, double z, bool center = false);
	};

	/*template<typename Self>
	struct can_trans {
		Self transform(const transformation& trans) { 
			Self& self = static_cast<Self&>(*this); 
			return trans(self); 
		}
		Self translate(double x, double y, double z) { 
			return transform(translate(x,y,z)); 
		}
		//Self translate(double x, double y) { 
		//	return transform(translate{x,y,0}); }
		Self rotate(double ax, double ay, double az, double angle) { return transform(axrotation(ax,ay,az,angle)); }
		Self up(double z) { return translate(0,0,z); }
		Self down(double z) { return translate(0,0,-z); }
		Self forw(double y) { return translate(0,y,0); }
		Self back(double y) { return translate(0,-y,0); }
		Self right(double x) { return translate(x,0,0); }
		Self left(double x) { return translate(-x,0,0); }

		Self rotateX(double a) { 
			return transform(rotateX(a)); 
		}
		Self rotateY(double a) { return transform(rotateY(a)); }
		Self rotateZ(double a) { return transform(rotateZ(a)); }

		Self mirrorX() { return transform(mirrorX()); }
		Self mirrorY() { return transform(mirrorY()); }
		Self mirrorZ() { return transform(mirrorZ()); }

		Self mirrorXY() { return transform(mirrorXY()); }
		Self mirrorYZ() { return transform(mirrorYZ()); }
		Self mirrorXZ() { return transform(mirrorXZ()); }
	};

	template<typename Self>
	struct can_boolops {
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
	};*/

}

#endif