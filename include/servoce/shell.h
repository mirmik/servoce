#ifndef SERVOCE_SHELL_H
#define SERVOCE_SHELL_H

#include <vector>
#include <servoce/shape.h>

namespace servoce 
{
	class solid_shape;

	class shell_shape : public shape
	{
	public:
		shell_shape(){}
		shell_shape(const TopoDS_Shell& arg) : shape((const TopoDS_Shape&)arg) {}

		servoce::solid_shape fill();
	};

	shell_shape make_shell(const std::vector<const servoce::shape*>& vec);
	shell_shape make_shell(const std::vector<servoce::face_shape>& vec);
	shell_shape polyhedron_shell(const std::vector<servoce::point3>& pnts, const std::vector<std::vector<int>>& faces);
} 

#endif