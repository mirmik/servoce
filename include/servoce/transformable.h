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
	template <class T>
	class transformable
	{
	public:
		//T transform(const transformation& trans) { return trans((const T&)*this); }
		//T transform(const general_transformation& trans) { return trans((const T&)*this); }

		virtual T self_transform(const transformation& trans);
		virtual T transform(const transformation& trans) const = 0;
		virtual T transform(const general_transformation& trans) const;

		// Translation API: (translate and move is same)
		T translate(double x, double y, double z);
		T translate(vector3 v);
		T translateX(double x);
		T translateY(double y);
		T translateZ(double z);

		T move(double x, double y, double z);
		T move(vector3 v);
		T moveX(double x);
		T moveY(double y);
		T moveZ(double z);

		// mnemonics for translate operations:
		T up(double z);
		T down(double z);
		T forw(double y);
		T back(double y);
		T right(double x);
		T left(double x);

		// restricted translation api:
		T movX(double x);
		T movY(double y);
		T movZ(double z);

		// Rotation API:
		T rotate(double a, vector3 vec);
		T rotate(double x, double y, double z);
		T rotateX(double a);
		T rotateY(double a);
		T rotateZ(double a);

		// restricted rotation api:
		T rot(vector3 vec, double a);
		T rot(double x, double y, double z);
		T rotX(double a);
		T rotY(double a);
		T rotZ(double a);

		// Mirror API;
		T mirrorX();
		T mirrorY();
		T mirrorZ();
		T mirrorXY();
		T mirrorYZ();
		T mirrorXZ();

		// Scale API:
		T scale(double s, point3 center = point3());
		T scaleX(double s);
		T scaleY(double s);
		T scaleZ(double s);
		T scaleXY(double x, double y);
		T scaleYZ(double y, double z);
		T scaleXZ(double x, double z);
		T scaleXYZ(double x, double y, double z);
	};
}

#endif