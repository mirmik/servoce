#ifndef SERVOCE_SURFACE_ALGO_H
#define SERVOCE_SURFACE_ALGO_H

#include <BRepLProp_SLProps.hxx>

namespace servoce 
{
	template<class Self>
	class surface_algo
	{
		Self& self() { return (Self&)*this; }
		const Self& self() const { return (const Self&) *this; }	

		auto SLProps(double U, double V) 
		{
			BRepLProp_SLProps prop(self().AdaptorSurface(), U, V, 1, 1e-5);
			return prop;
		}

	public:
		servoce::vector3 normal(double u, double v) 
		{
			return servoce::vector3(SLProps(u,v).Normal());
		}
	};
}

#endif