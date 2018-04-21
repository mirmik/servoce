#ifndef ZENGEOM_TOPO_H
#define ZENGEOM_TOPO_H

#include <memory>
#include <servoce/trans.h>

class TopoDS_Shape;
class TopoDS_Solid;
class TopoDS_Wire;
class TopoDS_Face;

namespace servoce {
	struct shape {
		TopoDS_Shape* m_shp;
		shape(const TopoDS_Shape& shp);// : m_shp(shp) {}
		shape(const shape& oth);// : shp(*oth.m_shp);// : m_shp(shp) {}
		~shape();
//		const TopoDS_Shape& Shape() const { return m_shp; }
//		TopoDS_Shape& Shape() { return m_shp; }
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


	struct solid : public shape, public can_trans<solid> {
		solid(const TopoDS_Shape& sld);// : shape(sld) {}
		//solid(const TopoDS_Solid& sld);// : shape(sld) {}
//		const TopoDS_Solid& Solid() const { return TopoDS::Solid(m_shp); }
//		TopoDS_Solid& Solid() { return TopoDS::Solid(m_shp); }
	};

	struct face : public shape {
		face(const TopoDS_Face& sld);// : shape(sld) {}
//		const TopoDS_Face& Face() const { return TopoDS::Face(m_shp); }
//		TopoDS_Face& Face() { return TopoDS::Face(m_shp); }
	};

	struct wire : public shape {
		wire(const TopoDS_Wire& sld);// : shape(sld) {}
//		const TopoDS_Wire& Wire() const { return TopoDS::Wire(m_shp); }
//		TopoDS_Wire& Wire() { return TopoDS::Wire(m_shp); }
	};
}

#endif