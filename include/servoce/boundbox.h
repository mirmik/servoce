#ifndef SERVOCE_BOUNDBOX_H
#define SERVOCE_BOUNDBOX_H

#include <servoce/geombase.h>

#include <Bnd_Box.hxx>

namespace servoce
{
	class boundbox
	{
		Bnd_Box _Box;
	public:
		double xmin, ymin, zmin, xmax, ymax, zmax;

	public:
		boundbox(const Bnd_Box& Box) : _Box(Box)
		{
			Box.Get(xmin, ymin, zmin, xmax, ymax, zmax);
		}

		boundbox(const boundbox& box) = default;

		boundbox(double xmin, double ymin, double zmin, double xmax, double ymax, double zmax) :
			xmin(xmin), ymin(ymin), zmin(zmin), xmax(xmax), ymax(ymax), zmax(zmax)
		{
			_Box.Update(xmin, ymin, zmin, xmax, ymax, zmax);
		}

		servoce::point3 corner_max();
		servoce::point3 corner_min();

		std::pair<double, double> xrange() { return {xmin, xmax}; }
		std::pair<double, double> yrange() { return {ymin, ymax}; }
		std::pair<double, double> zrange() { return {zmin, zmax}; }
	};
}

#endif