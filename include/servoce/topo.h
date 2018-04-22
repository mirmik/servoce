#ifndef ZENGEOM_TOPO_H
#define ZENGEOM_TOPO_H

#include <memory>
#include <servoce/boolops.h>
#include <servoce/trans.h>

class TopoDS_Shape;
class TopoDS_Solid;
class TopoDS_Wire;
class TopoDS_Face;

namespace servoce {
	struct shape {
		TopoDS_Shape* m_shp;
		shape(const TopoDS_Shape& shp);
		shape(const shape& oth);
		virtual ~shape();

		TopoDS_Shape& Shape();
		const TopoDS_Shape& Shape() const;
	};

	template<typename Self>
	struct can_trans {
		Self transform(const trans::transformation& trans) { Self& self = static_cast<Self&>(*this); return trans::create_transformed(self, trans); }
		Self translate(double x, double y, double z) { return transform(trans::translate{x,y,z}); }
		Self rotate(double ax, double ay, double az, double angle) { return transform(trans::axrotation{ax,ay,az,angle}); }
		Self up(double z) { return translate(0,0,z); }
		Self down(double z) { return translate(0,0,-z); }
		Self forw(double y) { return translate(0,y,0); }
		Self back(double y) { return translate(0,-y,0); }
		Self right(double x) { return translate(x,0,0); }
		Self left(double x) { return translate(-x,0,0); }

		Self rotateX(double a) { return transform(trans::rotateX(a)); }
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
		Self operator+(const Self& oth) const { const Self& self = static_cast<const Self&>(*this); return boolops::make_union(self, oth); }
		Self operator-(const Self& oth) const { const Self& self = static_cast<const Self&>(*this); return boolops::make_difference(self, oth); }
		Self operator^(const Self& oth) const { const Self& self = static_cast<const Self&>(*this); return boolops::make_intersect(self, oth); }
	};

	struct solid : public shape, public can_trans<solid>, public can_boolops<solid> {
		solid(const TopoDS_Shape& shp);
		const TopoDS_Solid& Solid() const;
		TopoDS_Solid& Solid();
	};

	struct face : public shape, public can_trans<wire>, public can_boolops<face> {
		face(const TopoDS_Shape& shp);
		const TopoDS_Face& Face() const;
		TopoDS_Face& Face();
	};

	struct wire : public shape, public can_trans<wire> {
		wire(const TopoDS_Shape& shp);
		const TopoDS_Wire& Wire() const;
		TopoDS_Wire& Wire();
	};
}

#endif