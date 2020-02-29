#ifndef SERVOCE_DISPLAYABLE_H
#define SERVOCE_DISPLAYABLE_H

#include <servoce/interactive_object.h>

namespace servoce 
{
	class displayable 
	{
		virtual std::shared_ptr<servoce::interactive_object> produce_interactive() = 0;
	};
}

#endif