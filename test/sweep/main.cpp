#include <servoce/face.h>
#include <servoce/solid.h>
#include <servoce/wire.h>
#include <servoce/display.h>
#include <cmath>

int main() {
	auto path = servoce::make_interpolate(
		/*pnts*/{
			{-5,-5},
			{0,0},
			{27,40},
			{25,50},
			{5,60},
			{-5,60},
		},
		/*tang*/{
			{1,1},
			{1,1},
			{0,0},
			{0,0},
			{0,0},
			{0,0},
		}
	);

	auto prof = servoce::make_circle_arc(10).rotateY(M_PI / 2).rotateZ(M_PI / 4).translate(-5, -5, 0);
	auto pipe = servoce::make_pipe(prof.infill_face(), path);
	auto pipe_shell = servoce::make_pipe_shell(prof, path);

	servoce::scene scn;
	//scn.add(linext + pipe.right(30));
	
	scn.add(path.right(30));
	scn.add(prof.right(30));
	scn.add(pipe);
	scn.add(pipe_shell.left(30));

	servoce::display(scn);
}