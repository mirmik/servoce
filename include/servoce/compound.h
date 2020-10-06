#ifndef SERVOCE_COMPOUND_H
#define SERVOCE_COMPOUND_H

#include <servoce/shape.h>

namespace servoce {
	class compound_shape :
		public shape_typed<compound_shape> 
	{
	public:
		compound_shape() {}

		compound_shape(const TopoDS_Compound& arg) 
			: shape_typed<compound_shape>((const TopoDS_Shape&)arg) {}

		compound_shape(servoce::shape&& arg) : compound_shape(arg.Compound()) {}
	};
}

#endif