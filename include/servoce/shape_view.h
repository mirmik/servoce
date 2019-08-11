#ifndef SERVOCE_SHAPE_VIEW
#define SERVOCE_SHAPE_VIEW

#include <servoce/topo.h>
#include <servoce/color.h>
#include <nos/trace.h>

#include <AIS_InteractiveObject.hxx>
#include <AIS_InteractiveContext.hxx>


class AIS_Shape;

namespace servoce
{
	class scene;

	class interactive_object 
	{
		Handle(AIS_InteractiveObject) m_ais = nullptr;
		Handle(AIS_InteractiveContext) m_context = nullptr;

	public:
		interactive_object(Handle(AIS_InteractiveObject) ais) : m_ais(ais) {}
		interactive_object(const shape& shp);

		servoce::color color() const;
		void set_color(const servoce::color&);
		void set_color(float r, float g, float b, float a=0);

		Handle(AIS_InteractiveObject) native() { return m_ais; }
		Handle(AIS_InteractiveObject) const native() const { return m_ais; }

		void set_location(const servoce::transformation& trans);
		void relocate(const servoce::transformation& trans) { set_location(trans); }
		
		void hide(bool en);

		void set_context(Handle(AIS_InteractiveContext) cntxt) { m_context = cntxt; }
	};

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
		void relocate(const servoce::transformation& trans) { set_location(trans); }
		void hide(bool en);

	private:
		servoce::shape shp;
		servoce::scene* scn = nullptr;
		AIS_Shape* m_ashp = nullptr;
		servoce::color m_color;
	};
}

#endif