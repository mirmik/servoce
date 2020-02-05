#ifndef SERVOCE_INTERACTIVE_OBJECT_H
#define SERVOCE_INTERACTIVE_OBJECT_H

#include <servoce/topo.h>
#include <servoce/color.h>

#include <AIS_InteractiveObject.hxx>
#include <AIS_InteractiveContext.hxx>

namespace servoce 
{
	class interactive_object 
	{
		Handle(AIS_InteractiveObject) m_ais = nullptr;
		Handle(AIS_InteractiveContext) m_context = nullptr;

	public:
		interactive_object(Handle(AIS_InteractiveObject) ais) : m_ais(ais) {}
		interactive_object(const shape& shp);
		interactive_object(const shape& shp, const servoce::color& clr);

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
}

#endif