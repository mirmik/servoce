#ifndef SERVOCE_CAMERA_H
#define SERVOCE_CAMERA_H

/*#include <servoce/linalg/linalg.h>
#include <servoce/util/setget.h>

using namespace linalg::aliases;

class gp_Dir;
class gp_Pnt;

namespace servoce
{
	class viewer;

	class camera
	{
	public:
		virtual void set_eye(viewer* v) = 0;
		virtual void set_scale(viewer* v) = 0;
		virtual void set_orient(viewer* v) = 0;

		virtual gp_Dir native_up() = 0;
		virtual gp_Dir native_dir() = 0;
		virtual gp_Pnt native_eye() = 0;
		virtual float native_scale() = 0;
	};

	class drone_camera : public camera
	{
		float _yaw = 0;
		float _pitch = 70;
		float3 _center = {50, 60, 70};
		float _scale = 200;

	public:
		FLOW_ACCESSOR(yaw, _yaw);
		FLOW_ACCESSOR(pitch, _pitch);
		FLOW_ACCESSOR(center, _center);
		FLOW_ACCESSOR(scale, _scale);

		void set_eye(viewer* v) override {};
		void set_scale(viewer* v) override {};
		void set_orient(viewer* v) override {};

		gp_Dir native_up() override;
		gp_Dir native_dir() override;
		gp_Pnt native_eye() override;
		float native_scale() override;
	};
}*/

#endif