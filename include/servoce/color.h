#ifndef SERVOCE_COLOR_H
#define SERVOCE_COLOR_H

namespace servoce
{
	struct color
	{
		float r, g, b, a;
	};

	static constexpr color white = 	color { 1, 1, 1 };
	static constexpr color black = 	color { 0, 0, 0 };
	static constexpr color red = 	color { 1, 0, 0 };
	static constexpr color green = 	color { 0, 1, 0 };
	static constexpr color blue = 	color { 0, 0, 1 };
	static constexpr color gray = 	color { 0.5, 0.5, 0.5 };
	static constexpr color mech = 	color { 0.6, 0.6, 0.8 };

}

#endif