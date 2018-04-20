#ifndef ZENGEOM_LOCAL_UTIL_H
#define ZENGEOM_LOCAL_UTIL_H

#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <servoce/math3.h>

static inline const TopoDS_Shape& OCC_Shape(const servoce::shape& shp) { return *shp.m_shp; }
static inline const gp_Pnt OCC_Point3(const servoce::point3& pnt) { return gp_Pnt(pnt.x, pnt.y, pnt.z); }
static inline double to_radian(double g) { return g * M_PI / 180; }

#endif