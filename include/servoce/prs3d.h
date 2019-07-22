#ifndef SERVOCE_PRS3D_H
#define SERVOCE_PRS3D_H

#include <servoce/geombase.h>
#include <servoce/scene.h>

namespace servoce
{
	enum class line_style 
	{
		solid_line,
		dash_line,
		dot_line,
		dotdash_line,
	};

	constexpr line_style solid_line = line_style::solid_line;
	constexpr line_style dash_line = line_style::dash_line;
	constexpr line_style dot_line = line_style::dot_line;
	constexpr line_style dotdash_line = line_style::dotdash_line;

	namespace draw {
		servoce::interactive_object arrow(
		    const servoce::point3& pnt,
		    const servoce::vector3& vec,
			const servoce::color& clr = servoce::black, 
		    double arrlen = 1,
			double width = 1);

		servoce::interactive_object line(
		    const servoce::point3& pnt,
		    const servoce::point3& vec,
			const servoce::color& clr = servoce::black, 
			line_style style = line_style::solid_line,
			double width = 1
		    );
	}
}

#endif