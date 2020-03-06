#ifndef SERVOCE_COMPSOLID_H
#define SERVOCE_COMPSOLID_H

#include <servoce/shape.h>

namespace servoce {
	class compsolid_shape : public shape 
	{
	public:
		compsolid_shape(){}
		compsolid_shape(const TopoDS_CompSolid& arg) : shape((const TopoDS_Shape&)arg) {}
	};
}

#endif