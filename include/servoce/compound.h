#ifndef SERVOCE_COMPOUND_H
#define SERVOCE_COMPOUND_H

#include <servoce/shape.h>

namespace servoce {
	class compound_shape : public shape 
	{
	public:
		compound_shape(){}
		compound_shape(const TopoDS_Compound& arg) : shape((const TopoDS_Shape&)arg) {}
	};
}

#endif