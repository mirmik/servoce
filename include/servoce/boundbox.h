#ifndef SERVOCE_BOUNDBOX_H
#define SERVOCE_BOUNDBOX_H

#include <Bnd_Box.hxx>

namespace servoce 
{
	class boundbox 
	{
		Bnd_Box _Box;

	public:
		boundbox(const Bnd_Box& Box) : _Box(Box) {}
		boundbox(const boundbox& box) = default;
	};
}

#endif