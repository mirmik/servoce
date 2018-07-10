#include <servoce/servoce.h>
#include <servoce/display.h>
#include <servoce/util/b64.h>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
namespace py = pybind11;

#define DEF_TRANSFORM_OPERATIONS(TYPE) 				\
.def("transform", &TYPE::transform)				\
.def("translate", &TYPE::translate)							\
.def("up", &TYPE::up)							\
.def("down", &TYPE::down)						\
.def("right", &TYPE::right)						\
.def("left", &TYPE::left)						\
.def("forw", &TYPE::forw)						\
.def("back", &TYPE::back)						\
.def("rotateX", &TYPE::rotateX)					\
.def("rotateY", &TYPE::rotateY)					\
.def("rotateZ", &TYPE::rotateZ)					\
.def("mirrorX", &TYPE::mirrorX)					\
.def("mirrorY", &TYPE::mirrorY)					\
.def("mirrorZ", &TYPE::mirrorZ)					\
.def("mirrorXY", &TYPE::mirrorXY)				\
.def("mirrorYZ", &TYPE::mirrorYZ)				\
.def("mirrorXZ", &TYPE::mirrorXZ)			

PYBIND11_MODULE(libservoce, m) {
	//py::register_exception<servoce::RuntimeException>(m, "ServoceRuntimeException");

	py::class_<servoce::point3>(m, "point3")
		//DEF_TRANSFORM_OPERATIONS(servoce::point3)
		.def(py::init<double,double,double>())
		.def(py::init<double,double>())
		.def_readwrite("x", &servoce::point3::x)
		.def_readwrite("y", &servoce::point3::y)
		.def_readwrite("z", &servoce::point3::z)
	;
	
	py::class_<servoce::vector3>(m, "vector3")
		//DEF_TRANSFORM_OPERATIONS(servoce::vector3)
		.def(py::init<double,double,double>())
		.def(py::init<double,double>())
		.def_readwrite("x", &servoce::vector3::x)
		.def_readwrite("y", &servoce::vector3::y)
		.def_readwrite("z", &servoce::vector3::z)
	;

	py::class_<servoce::shape>(m, "Shape")
		DEF_TRANSFORM_OPERATIONS(servoce::shape)
		.def("__add__", &servoce::shape::operator+)
		.def("__sub__", &servoce::shape::operator-)
		.def("__xor__", &servoce::shape::operator^)
	
		.def(py::pickle(
        	[](const servoce::shape &self) { return b64::base64_encode(self.string_dump()); },
        	[](const std::string& in) { return servoce::shape::restore_string_dump(b64::base64_decode(in)); }
    	))
		.def("fillet", &servoce::shape::fillet, py::arg("r"), py::arg("nums"))
    ;

	/*py::class_<servoce::shape, servoce::shape>(m, "Solid")
		DEF_TRANSFORM_OPERATIONS(servoce::shape)
		.def("__add__", &servoce::shape::operator+)
		.def("__sub__", &servoce::shape::operator-)
		.def("__xor__", &servoce::shape::operator^)
		//.def(py::self - servoce::shape)
		//.def(py::self ^ servoce::shape)
		.def("fillet", &servoce::shape::fillet, py::arg("r"), py::arg("nums"))

		.def(py::pickle(
        	[](const servoce::shape &self) { return gxx::base64_encode(self.string_dump()); },
        	[](const std::string& in) { return servoce::shape::restore_string_dump(gxx::base64_decode(in)).to_shape(); }
    	))
    ;*/
	
/**/
	m.def("make_box", 		servoce::make_box, py::arg("x"), py::arg("y"), py::arg("z"), py::arg("center") = false);
	m.def("make_sphere", 	servoce::make_sphere, py::arg("r"));
	m.def("make_cylinder", 	servoce::make_cylinder, py::arg("r"), py::arg("h"), py::arg("center") = false);
	m.def("make_cone", 		servoce::make_cone, py::arg("r1"), py::arg("r2"), py::arg("h"), py::arg("center") = false);
	m.def("make_torus", 	servoce::make_torus, py::arg("r1"), py::arg("r2"));

	m.def("make_linear_extrude", (servoce::shape(*)(const servoce::shape&,const servoce::vector3&,bool)) &servoce::make_linear_extrude, py::arg("shp"), py::arg("vec"), py::arg("center")=false);
	m.def("make_linear_extrude", (servoce::shape(*)(const servoce::shape&,double,bool)) &servoce::make_linear_extrude, py::arg("shp"), py::arg("z"), py::arg("center")=false);
	m.def("make_pipe", 			servoce::make_pipe, py::arg("prof"), py::arg("path"));
	m.def("make_pipe_shell", 	servoce::make_pipe_shell, py::arg("prof"), py::arg("path"), py::arg("isFrenet") = false);
/*
	py::class_<servoce::shape, servoce::shape>(m, "Face")
		DEF_TRANSFORM_OPERATIONS(servoce::shape)
		.def("__add__", &servoce::shape::operator+)
		.def("__sub__", &servoce::shape::operator-)
		.def("__xor__", &servoce::shape::operator^)
		.def("fillet", &servoce::shape::fillet, py::arg("r"), py::arg("nums"))
		.def("shapes", &servoce::shape::shapes)
	;*/
	m.def("make_circle", 	servoce::make_circle, py::arg("r"));
	m.def("make_ngon", 		servoce::make_ngon, py::arg("r"), py::arg("n"));
	m.def("make_square", 	servoce::make_square, py::arg("a"), py::arg("center") = false);
	m.def("make_rectangle", servoce::make_rectangle, py::arg("a"), py::arg("b"), py::arg("center") = false);
	m.def("make_polygon", 	(servoce::shape(*)(const std::vector<servoce::point3>&))&servoce::make_polygon, py::arg("pnts"));
	//m.def("make_sweep", 	servoce::make_sweep, py::arg("prof"), py::arg("path"));
/*
	py::class_<servoce::shape, servoce::shape>(m, "Wire")
		DEF_TRANSFORM_OPERATIONS(servoce::shape)
		.def("__add__", &servoce::operator+)
		.def("__sub__", &servoce::operator-)
		.def("__xor__", &servoce::operator^)
		.def("shape", &servoce::to_shape)
	;
	*/
	m.def("make_segment", servoce::make_segment);
	m.def("make_polysegment", (servoce::shape(*)(const std::vector<servoce::point3>&, const bool))&servoce::make_polysegment, py::arg("pnts"), py::arg("closed") = false);
	m.def("make_interpolate", (servoce::shape(*)(const std::vector<servoce::point3>&, const std::vector<servoce::vector3>&, bool))&servoce::make_interpolate, py::arg("pnts"), py::arg("tang"), py::arg("closed") = false);
	m.def("make_interpolate", (servoce::shape(*)(const std::vector<servoce::point3>&, const bool))&servoce::make_interpolate, py::arg("pnts"), py::arg("closed") = false);
	m.def("make_helix", servoce::make_helix, py::arg("step"), py::arg("height"), py::arg("radius"), py::arg("angle") = 0, py::arg("leftHanded") = false, py::arg("newStyle") = true);
	m.def("make_long_helix", servoce::make_long_helix, py::arg("step"), py::arg("height"), py::arg("radius"), py::arg("angle") = 0, py::arg("leftHanded") = false);
	//m.def("make_complex_shape", servoce::make_complex_shape, py::arg("shapes"));
	m.def("make_wcircle", (servoce::shape(*)(double))&servoce::make_circle);
	m.def("make_wcircle", (servoce::shape(*)(double,double,double))&servoce::make_circle);
/*
	py::class_<servoce::sweep_shape, servoce::shape>(m, "SolidSweep");
	py::class_<servoce::sweep_shape, servoce::shape>(m, "FaceSweep");
	*/
	py::class_<servoce::color>(m, "Color")
		.def(py::init<float, float, float>());
	py::class_<servoce::scene>(m, "Scene")
		.def(py::init<>())
		.def("add", (void(servoce::scene::*)(const servoce::shape&, servoce::color))&servoce::scene::add, py::arg("shape"), py::arg("color") = servoce::color{0.6,0.6,0.8})
		.def("add", (void(servoce::scene::*)(const servoce::point3&, servoce::color))&servoce::scene::add, py::arg("shape"), py::arg("color") = servoce::color{0.6,0.6,0.8})
		.def("append", (void(servoce::scene::*)(const servoce::scene&))&servoce::scene::append, py::arg("scene"))
	;

	m.def("make_union", (servoce::shape(*)(const std::vector<const servoce::shape*>&))&servoce::make_union);
	m.def("make_difference", (servoce::shape(*)(const std::vector<const servoce::shape*>&))&servoce::make_difference);
	m.def("make_intersect", (servoce::shape(*)(const std::vector<const servoce::shape*>&))&servoce::make_intersect);

	m.def("make_union", (servoce::shape(*)(const std::vector<const servoce::shape*>&))&servoce::make_union);
	m.def("make_difference", (servoce::shape(*)(const std::vector<const servoce::shape*>&))&servoce::make_difference);
	m.def("make_intersect", (servoce::shape(*)(const std::vector<const servoce::shape*>&))&servoce::make_intersect);

	m.def("display_scene", 	servoce::display);

	py::class_<servoce::transformation>(m, "transformation")
		//.def(py::init<>())
		.def("__call__", (servoce::shape(servoce::transformation::*)(const servoce::shape&)const)&servoce::transformation::operator())
		.def("__call__", (servoce::transformation(servoce::transformation::*)(const servoce::transformation&)const)&servoce::transformation::operator())
		.def("__mul__", &servoce::transformation::operator* )

		.def(py::pickle(
        	[](const servoce::transformation &self) { return b64::base64_encode(self.string_dump()); },
        	[](const std::string& in) { return servoce::transformation::restore_string_dump(b64::base64_decode(in)); }
    	))
	;

	//py::class_<servoce::translate, servoce::transformation>(m, "translate")
	//	.def(py::init<double,double,double>());
	//py::class_<servoce::axrotation, servoce::transformation>(m, "axrotation")
	//	.def(py::init<double,double,double,double>());
	//py::class_<servoce::axis_mirror, servoce::transformation>(m, "axis_mirror")
	//	.def(py::init<double,double,double>());
	//py::class_<servoce::plane_mirror, servoce::transformation>(m, "plane_mirror")
	//	.def(py::init<double,double,double>());
	m.def("translate", (servoce::transformation(*)(double,double,double)) &servoce::translate);
	m.def("translate", (servoce::transformation(*)(double,double)) &servoce::translate);
	m.def("translate", (servoce::transformation(*)(const servoce::vector3&)) &servoce::translate);
	m.def("axrotation", servoce::axrotation);
	m.def("axis_mirror", servoce::axis_mirror);
	m.def("plane_mirror", servoce::plane_mirror);

	m.def("rotateX", servoce::rotateX);
	m.def("rotateY", servoce::rotateY);
	m.def("rotateZ", servoce::rotateZ);
	m.def("mirrorX", servoce::mirrorX);
	m.def("mirrorY", servoce::mirrorY);
	m.def("mirrorZ", servoce::mirrorZ);
	m.def("mirrorXY", servoce::mirrorXY);
	m.def("mirrorXZ", servoce::mirrorXZ);
	m.def("mirrorYZ", servoce::mirrorYZ);
	m.def("up", servoce::up);
	m.def("down", servoce::down);
	m.def("left", servoce::left);
	m.def("right", servoce::right);
	m.def("forw", servoce::forw);
	m.def("back", servoce::back);









	//m.def("simplify_with_bspline", &servoce::simplify_with_bspline);
	m.def("make_stl", &servoce::make_stl);


}
