#ifndef SERVOCE_CAMERA_H
#define SERVOCE_CAMERA_H

#include <servoce/linalg/linalg.h>

using namespace linalg::aliases;

namespace servoce {
	class viewer;

	class camera {
		//float4 _orient;
		//float3 _center;
		//float _zoom;

		//camera(float4 orient={1,0,0,0}, float3 center = {0,0,0}, float zoom = 1) : _orient(orient), _center(center), _zoom(zoom) {}

		//void pan(float x, float y);
		//void rot(float x, float y);
		//void zoom(float x, float y);

		virtual void set_orient(viewer* v) = 0;
		virtual void set_pan(viewer* v) = 0;
		virtual void set_zoom(viewer* v) = 0;
	};

	class drone_camera : public camera {
		float phi;
		float psi;
		float3 _center;
		float _zoom;

		void set_orient(viewer* v) override {};
		void set_pan(viewer* v) override {};
		void set_zoom(viewer* v) override {};
	};
}

#endif