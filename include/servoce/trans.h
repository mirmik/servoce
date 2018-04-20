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

		solid create_transformed(const solid& shp, const transformation& trans);
		face create_transformed(const face& shp, const transformation& trans);
		wire create_transformed(const wire& shp, const transformation& trans);
	}
}

#endif