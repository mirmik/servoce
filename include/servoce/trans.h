#ifndef SERVOCE_TRANS_H
#define SERVOCE_TRANS_H

class gp_Trsf;

namespace servoce {
	class shape;
	class solid;
	class face;
	class wire;
	class point3;
	class vector3;

	namespace trans {
		struct transformation { 
			gp_Trsf* trsf;
			//transformation(){};
			transformation(gp_Trsf* trsf) : trsf(trsf) {};
			transformation(const transformation& oth);
			transformation(transformation&& oth) : trsf(oth.trsf) { oth.trsf = nullptr; }
			//virtual void init_native(gp_Trsf*) const; 
			shape operator()(const servoce::shape& sld) const;
			solid operator()(const servoce::solid& sld) const;
			face operator()(const servoce::face& sld) const;
			wire operator()(const servoce::wire& sld) const;
			point3 operator()(const servoce::point3& sld) const;
			vector3 operator()(const servoce::vector3& sld) const;
			trans::transformation operator()(const servoce::trans::transformation& sld) const;
			trans::transformation operator*(const servoce::trans::transformation& oth) const;
		
			transformation(){}
			~transformation();


			void dump(std::ostream& out) const;
			void load(std::istream& in);

			std::string string_dump() const;
			static transformation restore_string_dump(const std::string& in);
		};

		//struct complex_transformation : public transformation {
		//	complex_transformation(gp_Trsf* l, gp_Trsf* r);
		//};
		
		/*struct translate : public transformation { 
			//void init_native(gp_Trsf*) const override; 
			double x; double y; double z; 
			translate(double x, double y);// : x(x), y(y), z(z) {} 
			translate(double x, double y, double z);// : x(x), y(y), z(z) {} 
			translate(const vector3& vec); 
		};

		struct axrotation : public transformation { 
			//void init_native(gp_Trsf*) const override; 
			double ax; double ay; double az; double angle; 
			axrotation(double ax, double ay, double az, double angle);// : ax(ax), ay(ay), az(az), angle(angle) {} 
		};

		struct axis_mirror : public transformation { 
			//void init_native(gp_Trsf*) const override; 
			double ax; double ay; double az; 
			axis_mirror(double ax, double ay, double az); //: ax(ax), ay(ay), az(az) {} 
		};

		struct plane_mirror : public transformation { 
			//void init_native(gp_Trsf*) const override; 
			double ax; double ay; double az; 
			plane_mirror(double ax, double ay, double az); //: ax(ax), ay(ay), az(az) {} 
		};*/

		/*shape create_transformed(const shape& shp, const transformation& trans);
		solid create_transformed(const solid& shp, const transformation& trans);
		face create_transformed(const face& shp, const transformation& trans);
		wire create_transformed(const wire& shp, const transformation& trans);
		point3 create_transformed(const point3& shp, const transformation& trans);
		vector3 create_transformed(const vector3& shp, const transformation& trans);*/
		
		transformation translate(double x, double y);
		transformation translate(double x, double y, double z);
		transformation translate(const vector3& vec);
		transformation axrotation(double ax, double ay, double az, double angle);
		transformation axis_mirror(double ax, double ay, double az);
		transformation plane_mirror(double ax, double ay, double az);

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
	}
}

#endif