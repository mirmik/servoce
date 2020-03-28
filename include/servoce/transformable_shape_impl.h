#ifndef SERVOCE_TRANSFORMABLE_SHAPE_IMPL_H
#define SERVOCE_TRANSFORMABLE_SHAPE_IMPL_H

#include <servoce/shape.h>
#include <servoce/trans.h>

template<class Self>
Self servoce::transformable_shape<Self>::transform(
	const transformation& trans) const 
{ 
	return self().as_shape().transform(trans); 
}

template<class Self>
Self servoce::transformable_shape<Self>::transform(
	const general_transformation& trans) const 
{ 
	return self().as_shape().transform(trans);
}

#endif