#ifndef ZENGEOM_LOCAL_UTIL_H
#define ZENGEOM_LOCAL_UTIL_H

static inline const TopoDS_Shape& OCC_Shape(const servoce::shape& shp) { return *shp.m_shp; }

#endif