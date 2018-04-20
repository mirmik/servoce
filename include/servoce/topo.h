#ifndef ZENGEOM_TOPO_H
#define ZENGEOM_TOPO_H

#include <memory>

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

	struct solid : public shape {
		solid(const TopoDS_Shape& sld);// : shape(sld) {}
//		const TopoDS_Solid& Solid() const { return TopoDS::Solid(m_shp); }
//		TopoDS_Solid& Solid() { return TopoDS::Solid(m_shp); }
	};

	struct face : public shape {
//		const TopoDS_Face& Face() const { return TopoDS::Face(m_shp); }
//		TopoDS_Face& Face() { return TopoDS::Face(m_shp); }
	};

	struct wire : public shape {
//		const TopoDS_Wire& Wire() const { return TopoDS::Wire(m_shp); }
//		TopoDS_Wire& Wire() { return TopoDS::Wire(m_shp); }
	};
}

#endif