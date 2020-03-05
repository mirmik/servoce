#ifndef SERVOCE_SELF_TRANSFORMABLE_H
#define SERVOCE_SELF_TRANSFORMABLE_H

#include <servoce/trans.h>

namespace servoce 
{
	class self_transformable 
	{
	public:
		virtual void self_transform(const transformation& trans) = 0;
		virtual void self_transform(const general_transformation& trans);

		// Translation API: (translate and move is same)
		void self_translate(double x, double y, double z);
		void self_translate(vector3 v);
		void self_translateX(double x);
		void self_translateY(double y);
		void self_translateZ(double z);

		void self_move(double x, double y, double z);
		void self_move(vector3 v);
		void self_moveX(double x);
		void self_moveY(double y);
		void self_moveZ(double z);

		// mnemonics for translate operations:
		void self_up(double z);
		void self_down(double z);
		void self_forw(double y);
		void self_back(double y);
		void self_right(double x);
		void self_left(double x);

		// restricted translation api:
		void self_movX(double x);
		void self_movY(double y);
		void self_movZ(double z);

		// Rotation API:
		void self_rotate(double a, vector3 vec);
		void self_rotate(double x, double y, double z);
		void self_rotateX(double a);
		void self_rotateY(double a);
		void self_rotateZ(double a);

		// restricted rotation api:
		void self_rot(vector3 vec, double a);
		void self_rot(double x, double y, double z);
		void self_rotX(double a);
		void self_rotY(double a);
		void self_rotZ(double a);

		// Mirror API;
		void self_mirrorX();
		void self_mirrorY();
		void self_mirrorZ();
		void self_mirrorXY();
		void self_mirrorYZ();
		void self_mirrorXZ();

		// Scale API:
		void self_scale(double s, point3 center = point3());
		void self_scaleX(double s);
		void self_scaleY(double s);
		void self_scaleZ(double s);
		void self_scaleXY(double x, double y);
		void self_scaleYZ(double y, double z);
		void self_scaleXZ(double x, double z);
		void self_scaleXYZ(double x, double y, double z);
	};
}

#endif