#ifndef SERVOCE_SWEEP_H
#define SERVOCE_SWEEP_H

#include <servoce/topo.h>
#include <tuple>

class BRepPrimAPI_MakeSweep;

namespace servoce 
{
	/*class sweep_solid_shape : public shape
	{
		solid_shape first;
		solid_shape last;

	public:
		sweep_solid_shape() {}
		sweep_solid_shape(const BRepPrimAPI_MakeSweep& arg);
	};*/
	
	std::tuple<face_shape, edge_shape, edge_shape> make_tube(
	const edge_shape& shp, double radius, double tol, int cont, int maxdegree, int maxsegm);//, 
	
	std::tuple<shell_shape, edge_shape, edge_shape> make_tube(
	const wire_shape& shp, double radius, double tol, int cont, int maxdegree, int maxsegm);//, 
	//double tol, int cont, int maxdegree, int maxsegm);
}

#endif