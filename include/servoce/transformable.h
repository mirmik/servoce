#ifndef SERVOCE_TRANSFORMABLE_H
#define SERVOCE_TRANSFORMABLE_H

#include <stdexcept>

namespace servoce
{
	class point3;
	class vector3;
	class transformation;
	class general_transformation;

	// Interface for transformation support.
	template <class T, class Ret>
	class transformable
	{
	public:
		T& self() { return (T&)*this; }
		const T& self() const { return (const T&)*this; }

		//Ret transform(const general_transformation& trans) const { (void)trans; throw std::runtime_error("not supported"); }
	

		//T transform(const transformation& trans) { return trans((const T&)*this); }
		//T transform(const general_transformation& trans) { throw std::runtime_error("general_transformation is not supported"); }

		//virtual T self_transform(const transformation& trans);
		//virtual T transform(const transformation& trans) const = 0;
		//virtual T transform(const general_transformation& trans) const;

		// Translation API: (translate and move is same)
		Ret translate(double x, double y, double z);
		Ret translate(vector3 v);
		Ret translateX(double x);
		Ret translateY(double y);
		Ret translateZ(double z);

		Ret move(double x, double y, double z);
		Ret move(vector3 v);
		Ret moveX(double x);
		Ret moveY(double y);
		Ret moveZ(double z);

		// mnemonics for translate operations:
		Ret up(double z);
		Ret down(double z);
		Ret forw(double y);
		Ret back(double y);
		Ret right(double x);
		Ret left(double x);

		// restricted translation api:
		Ret movX(double x);
		Ret movY(double y);
		Ret movZ(double z);

		// Rotation API:
		Ret rotate(double a, vector3 vec);
		Ret rotate(double x, double y, double z);
		Ret rotateX(double a);
		Ret rotateY(double a);
		Ret rotateZ(double a);

		// restricted rotation api:
		Ret rot(vector3 vec, double a);
		Ret rot(double x, double y, double z);
		Ret rotX(double a);
		Ret rotY(double a);
		Ret rotZ(double a);

		// Mirror API;
		Ret mirrorO();
		Ret mirrorX();
		Ret mirrorY();
		Ret mirrorZ();
		Ret mirrorXY();
		Ret mirrorYZ();
		Ret mirrorXZ();

		// Scale API:
		Ret scale(double s, point3 center);
		Ret scaleX(double s);
		Ret scaleY(double s);
		Ret scaleZ(double s);
		Ret scaleXY(double x, double y);
		Ret scaleYZ(double y, double z);
		Ret scaleXZ(double x, double z);
		Ret scaleXYZ(double x, double y, double z);
	};
}

#endif
