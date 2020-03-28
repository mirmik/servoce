#ifndef SERVOCE_WIDGET_H
#define SERVOCE_WIDGET_H

#include <servoce/scene.h>

namespace servoce
{
	struct widget
	{
		virtual void exec(servoce::scene* scn) = 0;
		virtual void asyncexec(servoce::scene* scn) = 0;
	};
}

#endif