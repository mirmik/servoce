#ifndef SERVOCE_AXIS_H
#define SERVOCE_AXIS_H

//#include <servoce/transformable.h>
//#include <servoce/displayable.h>
//#include <gp_Ax1.hxx>

namespace servoce 
{
	/*class axis : public displayable, public transformable<axis>
	{
		gp_Ax1 Ax;

	public:
		axis(gp_Ax1 ax) : Ax(ax) {}
		axis(point3 pnt, vector3 vec) : Ax(pnt.Pnt(), vec.Dir()) {}

		std::shared_ptr<servoce::interactive_object> produce_interactive() override;
		axis transform(const transformation& trans) const ;
		axis transform(const general_transformation& trans) const { (void)trans; throw std::runtime_error(""); }
	};*/
}

//#include <servoce/transformable_impl.h>

#endif