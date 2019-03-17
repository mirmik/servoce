#ifndef SERVOCE_TRANS_H
#define SERVOCE_TRANS_H

#include <servoce/geombase.h>

class gp_Trsf;
class gp_GTrsf;

namespace servoce
{
	class shape;
	class point3;
	class vector3;

	struct transformation
	{
		gp_Trsf* trsf;
		transformation(gp_Trsf* trsf) : trsf(trsf) {};
		transformation(const transformation& oth); 
		transformation(transformation&& oth) : trsf(oth.trsf) { oth.trsf = nullptr; }
		shape operator()(const servoce::shape& sld) const;
		point3 operator()(const servoce::point3& sld) const;
		transformation operator()(const servoce::transformation& sld) const;
		transformation operator*(const servoce::transformation& oth) const;

		transformation() : trsf(nullptr) {}
		~transformation();

		void dump(std::ostream& out) const;
		void load(std::istream& in);

		std::string string_dump() const;
		static transformation restore_string_dump(const std::string& in);
	};

	struct general_transformation
	{
		gp_GTrsf* gtrsf;
		general_transformation(gp_GTrsf* gtrsf) : gtrsf(gtrsf) {};
		general_transformation(const general_transformation& oth); 
		general_transformation(general_transformation&& oth) : gtrsf(oth.gtrsf) { oth.gtrsf = nullptr; }
		shape operator()(const servoce::shape& sld) const;

		general_transformation() : gtrsf(nullptr) {}
		~general_transformation();

		void dump(std::ostream& out) const;
		void load(std::istream& in);

		std::string string_dump() const;
		static general_transformation restore_string_dump(const std::string& in);
	};

	//Aphine Transforms
	transformation translate(double x, double y);
	transformation translate(double x, double y, double z);
	transformation translate(const vector3& vec);
	transformation axrotation(double ax, double ay, double az, double angle);
	transformation axis_mirror(double ax, double ay, double az);
	transformation plane_mirror(double ax, double ay, double az);

	transformation rotate(const vector3& ax, double a);
	transformation rotateX(double a);
	transformation rotateY(double a);
	transformation rotateZ(double a);
	transformation mirrorX();
	transformation mirrorY();
	transformation mirrorZ();
	transformation mirrorXY();
	transformation mirrorYZ();
	transformation mirrorXZ();

	transformation up(double);
	transformation down(double);
	transformation forw(double);
	transformation back(double);
	transformation left(double);
	transformation right(double);

	transformation scale(double, point3 center = point3());

	//Non Aphine Transforms
	general_transformation scaleX(double);
	general_transformation scaleY(double);
	general_transformation scaleZ(double);
}

#endif