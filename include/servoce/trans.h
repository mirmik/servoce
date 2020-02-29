#ifndef SERVOCE_TRANS_H
#define SERVOCE_TRANS_H

#include <gp_Trsf.hxx>
#include <servoce/geombase.h>
#include <vector>

class gp_Trsf;
class gp_GTrsf;

namespace servoce
{
	class shape;
	class point3;
	class vector3;
	class quaternion;

	struct transformation
	{
		gp_Trsf* trsf;
		transformation(gp_Trsf* trsf) : trsf(trsf) {};
		transformation(gp_Trsf trsf) : trsf(new gp_Trsf(trsf)) {};
		transformation(const transformation& oth); 
		transformation(transformation&& oth) : trsf(oth.trsf) { oth.trsf = nullptr; }
		shape operator()(const servoce::shape& sld) const;
		point3 operator()(const servoce::point3& sld) const;
		vector3 operator()(const servoce::vector3& sld) const;
		transformation operator()(const servoce::transformation& sld) const;
		transformation operator*(const servoce::transformation& oth) const;

		transformation invert();	
		transformation inverse() { return invert(); }

		transformation() : trsf(nullptr) {}
		~transformation();

		void dump(std::ostream& out) const;
		void load(std::istream& in);

		std::vector<double> translation_part() const;
		std::vector<double> rotation_part() const;
		servoce::vector3 translation() const;
		servoce::quaternion rotation() const;

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

	transformation nulltrans();

	//Aphine Transforms (translate and move is same)
	transformation translate(double x, double y, double z);
	transformation translate(const vector3& vec);
	transformation move(double x, double y, double z);
	transformation move(const vector3& vec);
	transformation moveX(double);
	transformation moveY(double);
	transformation moveZ(double);

	transformation up(double);
	transformation down(double);
	transformation forw(double);
	transformation back(double);
	transformation left(double);
	transformation right(double);

	transformation axrotation(double ax, double ay, double az, double angle);
	transformation rotate(double a, const vector3& ax);
	transformation rotate(double x, double y, double z);
	transformation rotateX(double a);
	transformation rotateY(double a);
	transformation rotateZ(double a);

	transformation mirror_axis(double ax, double ay, double az);
	transformation mirror_axis(vector3 vec);
	transformation mirror_plane(double ax, double ay, double az);
	transformation mirror_plane(vector3 vec);
	transformation mirrorO(double ax, double ay, double az);
	transformation mirrorO(const point3& pnt);
	transformation mirrorO();
	transformation mirrorX();
	transformation mirrorY();
	transformation mirrorZ();
	transformation mirrorXY();
	transformation mirrorYZ();
	transformation mirrorXZ();

	transformation scale(double, point3 center);
	transformation scale(double);

	//Non Aphine Transforms
	general_transformation scaleX(double);
	general_transformation scaleY(double);
	general_transformation scaleZ(double);

	general_transformation scaleXY(double,double);
	general_transformation scaleYZ(double,double);
	general_transformation scaleXZ(double,double);

	general_transformation scaleXYZ(double,double,double);

//Advanced:
	transformation short_rotate(const vector3& t, const vector3& f);
}

#endif