#ifndef SERVOCE_SHAPE_VIEW
#define SERVOCE_SHAPE_VIEW

#include <servoce/topo.h>
#include <servoce/color.h>
#include <nos/trace.h>

class AIS_Shape;

namespace servoce
{
	class scene;

	class shape_view
	{
	public:
		shape_view() { TRACE(); }
		shape_view(const servoce::shape& a, servoce::color color, scene* scn);
		shape_view(const shape_view& oth);
		shape_view(shape_view&& oth);

		shape_view& operator=(const shape_view& oth);
		shape_view& operator=(shape_view&& oth);

		servoce::shape shape() const;
		servoce::color color() const;
		const servoce::scene& scene() const { return *scn; }

		AIS_Shape* native() { return m_ashp; }
		AIS_Shape* const native() const { return m_ashp; }

		void set_location(const servoce::transformation& trans);
		void hide(bool en);

	private:
		servoce::shape shp;
		servoce::scene* scn = nullptr;
		AIS_Shape* m_ashp = nullptr;
		servoce::color m_color;
	};
}

#endif