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
		//sweep3d

	shape make_linear_extrude(const shape& base, const servoce::vector3& vec, bool center = false);
	shape make_linear_extrude(const shape& base, double z, bool center = false);
	shape make_pipe_0(const shape& profile, const shape& spine);
	shape make_pipe(const shape& profile, const shape& spine, const std::string mode, bool force_approx_c1=false);
	//shape make_pipe_shell(const std::vector<const shape*>& profile, const shape& spine, bool isFrenet = false, bool approx_c1=false);
	shape make_pipe_shell(
		const std::vector<const shape*>& wires, 
		const shape& spine, 
		bool frenet=false, 
		bool force_approx_c1=false, 
		const vector3& binormal = vector3(0,0,0),
		const vector3& parallel= vector3(0,0,0),
		bool discrete=false,
		bool solid=true,
		int transition=0);

	/*shape make_pipe_shell(
		const std::vector<const shape*>& profiles, 
		const shape& spine, 
		bool frenet=false,
		bool solid=true,
		int transition=0);*/


	std::tuple<face_shape, edge_shape, edge_shape> make_tube(
	const edge_shape& shp, double radius, double tol, int cont, int maxdegree, int maxsegm);//, 
	
	std::tuple<shell_shape, edge_shape, edge_shape> make_tube(
	const wire_shape& shp, double radius, double tol, int cont, int maxdegree, int maxsegm);//, 
	//double tol, int cont, int maxdegree, int maxsegm);
}

#endif