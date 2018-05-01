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
		class complex_transformation;

		struct transformation { 
			gp_Trsf* trsf;
			transformation(transformation&& oth) : trsf(oth.trsf) { oth.trsf = nullptr; }
			//virtual void init_native(gp_Trsf*) const; 
			shape operator()(const servoce::shape& sld) const;
			solid operator()(const servoce::solid& sld) const;
			face operator()(const servoce::face& sld) const;
			wire operator()(const servoce::wire& sld) const;
			point3 operator()(const servoce::point3& sld) const;
			vector3 operator()(const servoce::vector3& sld) const;
			trans::complex_transformation operator()(const servoce::trans::transformation& sld) const;
			trans::complex_transformation operator*(const servoce::trans::transformation& oth) const;
		
			transformation(){}
			~transformation();

		};

		struct complex_transformation : public transformation {
			complex_transformation(gp_Trsf* l, gp_Trsf* r);
		};
		
		struct translate : public transformation { 
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
		};

		/*shape create_transformed(const shape& shp, const transformation& trans);
		solid create_transformed(const solid& shp, const transformation& trans);
		face create_transformed(const face& shp, const transformation& trans);
		wire create_transformed(const wire& shp, const transformation& trans);
		point3 create_transformed(const point3& shp, const transformation& trans);
		vector3 create_transformed(const vector3& shp, const transformation& trans);*/
		
		axrotation rotateX(double a);		
		axrotation rotateY(double a);
		axrotation rotateZ(double a);
		axis_mirror mirrorX();
		axis_mirror mirrorY();
		axis_mirror mirrorZ();
		plane_mirror mirrorXY();
		plane_mirror mirrorYZ();
		plane_mirror mirrorXZ();

		translate up(double);
		translate down(double);
		translate forw(double);
		translate back(double);
		translate left(double);
		translate right(double);
	}
}

#endif