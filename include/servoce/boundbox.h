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
			
			try 
			{
				Box.Get(xmin, ymin, zmin, xmax, ymax, zmax);
			}
			catch (...) 
			{
				xmin= ymin= zmin= xmax= ymax= zmax= 0;
			}
		}

		boundbox(){}
		boundbox(const boundbox& box) = default;

		boundbox(double xmin, double ymin, double zmin, double xmax, double ymax, double zmax) :
			xmin(xmin), ymin(ymin), zmin(zmin), xmax(xmax), ymax(ymax), zmax(zmax)
		{
			_Box.Update(xmin, ymin, zmin, xmax, ymax, zmax);
		}

		boundbox add(boundbox oth) 
		{
			Bnd_Box Box;
			try 
			{
				Box.Add(_Box);
			}
			catch (...) 
			{
				throw std::runtime_error("fafsdfasdf");
			}
			//Box.Add(_Box);
			try 
			{
				Box.Add(oth._Box);
			}
			catch (...) 
			{
				throw std::runtime_error("fasdf");
			}
			
			return Box;
		}

		double max0() { 
			auto a = xmax - xmin;
			auto b = ymax - ymin;
			auto c = zmax - zmin;
			return a > b ? (a > c ? a : c) : (b > c ? b : c);   
		}

		servoce::point3 corner_max();
		servoce::point3 corner_min();

		std::pair<double, double> xrange() { return {xmin, xmax}; }
		std::pair<double, double> yrange() { return {ymin, ymax}; }
		std::pair<double, double> zrange() { return {zmin, zmax}; }
	};
}

#endif