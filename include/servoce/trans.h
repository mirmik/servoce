#ifndef SERVOCE_TRANS_H
#define SERVOCE_TRANS_H

class gp_Trsf;

namespace servoce {
	class solid;
	class face;
	class wire;

	namespace trans {
		struct transformation { virtual void init_native(gp_Trsf*) const = 0; };
		struct translate : public transformation { void init_native(gp_Trsf*) const override; double x; double y; double z; translate(double x, double y, double z) : x(x), y(y), z(z) {} };
		struct axrotation : public transformation { void init_native(gp_Trsf*) const override; double ax; double ay; double az; double angle; axrotation(double ax, double ay, double az, double angle) : ax(ax), ay(ay), az(az), angle(angle) {} };
		struct axis_mirror : public transformation { void init_native(gp_Trsf*) const override; double ax; double ay; double az; axis_mirror(double ax, double ay, double az) : ax(ax), ay(ay), az(az) {} };
		struct plane_mirror : public transformation { void init_native(gp_Trsf*) const override; double ax; double ay; double az; plane_mirror(double ax, double ay, double az) : ax(ax), ay(ay), az(az) {} };

		solid create_transformed(const solid& shp, const transformation& trans);
		face create_transformed(const face& shp, const transformation& trans);
		wire create_transformed(const wire& shp, const transformation& trans);

		axrotation rotateX(double a);		
		axrotation rotateY(double a);
		axrotation rotateZ(double a);
		axis_mirror mirrorX();
		axis_mirror mirrorY();
		axis_mirror mirrorZ();
		plane_mirror mirrorXY();
		plane_mirror mirrorYZ();
		plane_mirror mirrorXZ();
	}
}

#endif