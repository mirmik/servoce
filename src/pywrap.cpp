#include <servoce/servoce.h>
//#include <servoce/display.h>
#include <servoce/util/b64.h>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <exception>

#include <Standard_Failure.hxx>

//#include <nos/trace.h>

namespace py = pybind11;
using namespace servoce;

#define DEF_TRANSFORM_OPERATIONS(TYPE) 					\
.def("transform", &TYPE::transform, ungil())			\
.def("translate", &TYPE::translate, ungil())			\
.def("up", &TYPE::up, ungil())							\
.def("down", &TYPE::down, ungil())						\
.def("right", &TYPE::right, ungil())					\
.def("left", &TYPE::left, ungil())						\
.def("forw", &TYPE::forw, ungil())						\
.def("back", &TYPE::back, ungil())						\
.def("rotate", &TYPE::rotate, ungil())					\
.def("rotateX", &TYPE::rotateX, ungil())				\
.def("rotateY", &TYPE::rotateY, ungil())				\
.def("rotateZ", &TYPE::rotateZ, ungil())				\
.def("mirrorX", &TYPE::mirrorX, ungil())				\
.def("mirrorY", &TYPE::mirrorY, ungil())				\
.def("mirrorZ", &TYPE::mirrorZ, ungil())				\
.def("mirrorXY", &TYPE::mirrorXY, ungil())				\
.def("mirrorYZ", &TYPE::mirrorYZ, ungil())				\
.def("mirrorXZ", &TYPE::mirrorXZ, ungil())				\
.def("scale", (shape(TYPE::*)(double,point3))&TYPE::scale, ungil(), py::arg("factor"), py::arg("center") = point3())

using ungil = py::call_guard<py::gil_scoped_release>;

PYBIND11_MODULE(libservoce, m)
{
//EXCEPTONS
	//py::register_exception<std::exception>(m, "std::exception");
	//py::register_exception<std::runtime_error>(m, "std::runtime_error");
	//py::register_exception<Standard_Failure>(m, "Standard_Failure");

	static py::exception<Standard_Failure> exc(m, "OpenCascade_Standard_Failure");
	py::register_exception_translator([](std::exception_ptr p)
	{
		try
		{
			if (p) std::rethrow_exception(p);
		}
		catch (const Standard_Failure &e)
		{
			exc(e.GetMessageString());
		}
	});

//OBJECTS
	py::class_<point3>(m, "point3")
	//DEF_TRANSFORM_OPERATIONS(point3)
	.def(py::init<double, double, double>())
	.def(py::init<double, double>())
	.def("distance", &point3::distance)
	.def("lerp", &point3::lerp)
	.def(py::init<const servoce::point3&>())
	.def(py::init<py::list>())
	.def(py::init<py::tuple>())
	.def_readwrite("x", &point3::x)
	.def_readwrite("y", &point3::y)
	.def_readwrite("z", &point3::z)
	.def("__sub__", (vector3(*)(const point3&, const point3&)) &servoce::operator- )
	.def("__add__", (point3(*)(const point3&, const vector3&)) &servoce::operator+ )
	.def("__sub__", (point3(*)(const point3&, const vector3&)) &servoce::operator- )
	.def("__setitem__", [](point3 & self, int key, double value) { self[key] = value; })
	.def("__getitem__", [](const point3 & self, int key) { return self[key]; })
	.def("__eq__", [](const point3 & a, const point3 & b)
	{
		return point3::early(a, b);
	})
	.def("__repr__", [](const point3 & pnt)
	{
		char buf[128];
		sprintf(buf, "point3(%f,%f,%f)", pnt.x, pnt.y, pnt.z);
		return std::string(buf);
	})
	.def(py::pickle(
	         [](const point3 & self)
	{
		double arr[3] = {self.x, self.y, self.z};
		return b64::base64_encode((uint8_t*)&arr, 3 * sizeof(double));
	},
	[](const std::string & in)
	{
		double arr[3];
		std::string decoded = b64::base64_decode(in);
		memcpy(&arr, decoded.data(), 3 * sizeof(double));
		return point3(arr);
	}))
	;

	py::class_<point2>(m, "point2")
	//DEF_TRANSFORM_OPERATIONS(point3)
	.def(py::init<double, double>())
	.def(py::init<const servoce::point2&>())
	.def(py::init<py::list>())
	.def(py::init<py::tuple>())
	.def_readwrite("x", &point2::x)
	.def_readwrite("y", &point2::y)
	.def("__setitem__", [](point2 & self, int key, double value) { self[key] = value; })
	.def("__getitem__", [](const point2 & self, int key) { return self[key]; })
	.def("__eq__", [](const point2 & a, const point2 & b)
	{
		return point2::early(a, b);
	})
	.def("__repr__", [](const point3 & pnt)
	{
		char buf[128];
		sprintf(buf, "point2(%f,%f)", pnt.x, pnt.y);
		return std::string(buf);
	})
	.def(py::pickle(
	         [](const point2 & self)
	{
		double arr[2] = {self.x, self.y};
		return b64::base64_encode((uint8_t*)&arr, 2 * sizeof(double));
	},
	[](const std::string & in)
	{
		double arr[2];
		std::string decoded = b64::base64_decode(in);
		memcpy(&arr, decoded.data(), 2 * sizeof(double));
		return point2(arr);
	}))
	;

	py::class_<vector3>(m, "vector3")
	//DEF_TRANSFORM_OPERATIONS(vector3)
	.def(py::init<double, double, double>())
	.def(py::init<double, double>())
	.def(py::init<py::list>())
	.def(py::init<py::tuple>())
	.def_readwrite("x", &vector3::x)
	.def_readwrite("y", &vector3::y)
	.def_readwrite("z", &vector3::z)
	.def("__mul__", (vector3(*)(const vector3&, double)) &servoce::operator* )
	.def("__truediv__", (vector3(*)(const vector3&, double)) &servoce::operator/ )
	.def("__add__", (vector3(*)(const vector3&, const vector3&)) &servoce::operator+ )
	.def("__sub__", (vector3(*)(const vector3&, const vector3&)) &servoce::operator- )
	.def("__setitem__", [](vector3 & self, int key, double value) { self[key] = value; })
	.def("__getitem__", [](const vector3 & self, int key) { return self[key]; })
	.def("__repr__", [](const vector3 & pnt)
	{
		char buf[128];
		sprintf(buf, "vector3(%f,%f,%f)", pnt.x, pnt.y, pnt.z);
		return std::string(buf);
	})
	;

	py::class_<shape>(m, "Shape")
	DEF_TRANSFORM_OPERATIONS(shape)
	.def("__add__", (shape(shape::*)(const shape&))&shape::operator+, ungil())
	.def("__sub__", &shape::operator-, ungil())
	.def("__xor__", &shape::operator^, ungil())
	.def(py::pickle(
	[](const shape & self) { return b64::base64_encode(string_dump(self)); },
	[](const std::string & in) { return restore_string_dump<shape>(b64::base64_decode(in)); }), ungil())
	.def("fill", &shape::fill)
	.def("center", &shape::center, ungil())
	.def("extrude", (shape(shape::*)(const vector3&, bool)) &shape::extrude, ungil(), py::arg("vec"), py::arg("center") = false)
	.def("extrude", (shape(shape::*)(double, double, double, bool)) &shape::extrude, ungil(), py::arg("x"), py::arg("y"), py::arg("z"), py::arg("center") = false)
	.def("extrude", (shape(shape::*)(double, bool)) &shape::extrude, ungil(), py::arg("z"), py::arg("center") = false)
	.def("is_closed", &shape::is_closed, ungil())
	.def("sfvertex", &shape::sfvertex, ungil())
	.def("endpoints", &shape::sfvertex, ungil())

	.def("vertices", &shape::vertices, ungil())
	.def("solids", &shape::faces, ungil())
	.def("faces", &shape::faces, ungil())
	.def("edges", &shape::edges, ungil())
	.def("wires", &shape::wires, ungil())
	;

	m.def("fillet", (shape(*)(const shape&, double, const std::vector<point3>&))&servoce::fillet, ungil(), py::arg("shp"), py::arg("r"), py::arg("refs"));
	m.def("fillet", (shape(*)(const shape&, double))&servoce::fillet, ungil(), py::arg("shp"), py::arg("r"));
	m.def("chamfer", (shape(*)(const shape&, double, const std::vector<point3>&))&servoce::chamfer, ungil(), py::arg("shp"), py::arg("r"), py::arg("refs"));
	m.def("chamfer", (shape(*)(const shape&, double))&servoce::chamfer, ungil(), py::arg("shp"), py::arg("r"));
	

//PRIM3D
	m.def("box", 		box, ungil(), py::arg("x"), py::arg("y"), py::arg("z"), py::arg("center") = false);

	m.def("sphere", 	(shape(*)(double))&sphere, ungil(), py::arg("r"));
	m.def("sphere", 	(shape(*)(double,double))&sphere, ungil(), py::arg("r"), py::arg("an1"));
	m.def("sphere", 	(shape(*)(double,double,double))&sphere, ungil(), py::arg("r"), py::arg("an1"), py::arg("an2"));
	m.def("sphere", 	(shape(*)(double,double,double,double))&sphere, ungil(), py::arg("r"), py::arg("an1"), py::arg("an2"), py::arg("an3"));

	m.def("cylinder", 	(shape(*)(double, double, bool)) &cylinder, ungil(), py::arg("r"), py::arg("h"), py::arg("center") = false);
	m.def("cylinder", 	(shape(*)(double, double, double, bool)) &cylinder, ungil(), py::arg("r"), py::arg("h"), py::arg("angle"), py::arg("center") = false);
	m.def("cylinder", 	(shape(*)(double, double, double, double, bool)) &cylinder, ungil(), py::arg("r"), py::arg("h"), py::arg("a1"), py::arg("a2"), py::arg("center") = false);

	m.def("cone", 		(shape(*)(double, double, double, bool)) &cone, ungil(), py::arg("r1"), py::arg("r2"), py::arg("h"), py::arg("center") = false);
	m.def("cone", 		(shape(*)(double, double, double, double, bool)) &cone, ungil(), py::arg("r1"), py::arg("r2"), py::arg("h"), py::arg("angle"), py::arg("center") = false);
	m.def("cone", 		(shape(*)(double, double, double, double, double, bool)) &cone, ungil(), py::arg("r1"), py::arg("r2"), py::arg("h"), py::arg("a1"), py::arg("a2"), py::arg("center") = false);

	m.def("torus", 		(shape(*)(double, double)) &torus, ungil(), py::arg("r1"), py::arg("r2"));
	m.def("torus", 		(shape(*)(double, double, double)) &torus, ungil(), py::arg("r1"), py::arg("r2"), py::arg("ua"));
	m.def("torus", 		(shape(*)(double, double, double, double)) &torus, ungil(), py::arg("r1"), py::arg("r2"), py::arg("va1"), py::arg("va2"));
	m.def("torus", 		(shape(*)(double, double, double, double, double)) &torus, ungil(), py::arg("r1"), py::arg("r2"), py::arg("va1"), py::arg("va2"), py::arg("ua"));
	m.def("halfspace", &halfspace, ungil());

	m.def("thicksolid", &thicksolid, ungil());
	m.def("unify", &unify, ungil());

//OPS3D
	m.def("make_linear_extrude", (shape(*)(const shape&, const vector3&, bool)) &make_linear_extrude, ungil(), py::arg("shp"), py::arg("vec"), py::arg("center") = false);
	m.def("make_linear_extrude", (shape(*)(const shape&, double, bool)) &make_linear_extrude, ungil(), py::arg("shp"), py::arg("z"), py::arg("center") = false);
	m.def("make_linear_extrude", [](const shape & shp, const py::list & lst, bool center) { return servoce::make_linear_extrude(shp, vector3(lst[0].cast<double>(), lst[1].cast<double>(), lst[2].cast<double>()), center); }, ungil(), py::arg("shp"), py::arg("vec"), py::arg("center") = false);
	m.def("make_pipe", 			make_pipe, ungil(), py::arg("prof"), py::arg("path"));
	m.def("make_pipe_shell", 	make_pipe_shell, ungil(), py::arg("prof"), py::arg("path"), py::arg("isFrenet") = false);
	m.def("loft", 				loft, ungil(), py::arg("arr"), py::arg("smooth")=false);
	m.def("revol", 				revol, ungil());

//PRIM2D
	m.def("square", 	square, ungil(), py::arg("a"), py::arg("center") = false, py::arg("wire")=false);
	m.def("rectangle", 	rectangle, ungil(), py::arg("a"), py::arg("b"), py::arg("center") = false, py::arg("wire")=false);
	
	m.def("circle", 	(shape(*)(double, bool)) &circle, ungil(), py::arg("r"), py::arg("wire")=false);
	m.def("circle", 	(shape(*)(double, double, bool)) &circle, ungil(), py::arg("r"), py::arg("angle"), py::arg("wire")=false);
	m.def("circle", 	(shape(*)(double, double, double, bool)) &circle, ungil(), py::arg("r"), py::arg("a1"), py::arg("a2"), py::arg("wire")=false);
	
	m.def("ellipse", 	(shape(*)(double, double, bool)) &ellipse, ungil(), py::arg("r1"), py::arg("r2"), py::arg("wire")=false);
	m.def("ellipse", 	(shape(*)(double, double, double, double, bool)) &ellipse, ungil(), py::arg("r1"), py::arg("r2"), py::arg("a1"), py::arg("a2"), py::arg("wire")=false);
	
	m.def("ngon", 		ngon, ungil(), py::arg("r"), py::arg("n"), py::arg("wire")=false);
	m.def("polygon", 	(shape(*)(const std::vector<point3>&))&polygon, ungil(), py::arg("pnts"));
	m.def("textshape", 	textshape, ungil(), py::arg("text"), py::arg("fontpath"), py::arg("size"));

	m.def("fill", &fill, ungil());

//PRIM1D
	m.def("segment", make_segment, ungil());
	m.def("polysegment", (shape(*)(const std::vector<point3>&, const bool))&make_polysegment, ungil(), py::arg("pnts"), py::arg("closed") = false);
	m.def("interpolate", (shape(*)(const std::vector<point3>&, const std::vector<vector3>&, bool))&make_interpolate, ungil(), py::arg("pnts"), py::arg("tang"), py::arg("closed") = false);
	m.def("interpolate", (shape(*)(const std::vector<point3>&, const bool))&make_interpolate, ungil(), py::arg("pnts"), py::arg("closed") = false);
	m.def("helix", make_helix, ungil(), py::arg("step"), py::arg("height"), py::arg("radius"), py::arg("angle") = 0, py::arg("leftHanded") = false, py::arg("newStyle") = true);
	m.def("long_helix", make_long_helix, ungil(), py::arg("step"), py::arg("height"), py::arg("radius"), py::arg("angle") = 0, py::arg("leftHanded") = false);

	m.def("circle_arc", &circle_arc, ungil());

	m.def("sew", &sew, ungil());

//SURFACE
	py::class_<surface::surface>(m, "surface")
		.def("map", &surface::surface::map, ungil());
	m.def("surface_cylinder", surface::cylinder, ungil());
	
//CURVE2
	py::class_<curve2::curve2>(m, "curve2")
		.def("value", &curve2::curve2::value)
		.def(py::pickle(
		[](const curve2::curve2 & self) { return b64::base64_encode(string_dump(self)); },
		[](const std::string & in) { return restore_string_dump<curve2::curve2>(b64::base64_decode(in)); }), ungil())
		.def("rotate", &curve2::curve2::rotate)
	;
	py::class_<curve2::trimmed_curve2, curve2::curve2>(m, "trimmed_curve2")
		.def(py::init<const curve2::curve2&, double, double>(), ungil())
	;
	m.def("curve2_ellipse", curve2::ellipse, ungil());
	m.def("curve2_segment", curve2::segment, ungil());

//BOOLEAN
	m.def("union", (shape(*)(const std::vector<const shape*>&))&make_union, ungil());
	m.def("difference", (shape(*)(const std::vector<const shape*>&))&make_difference, ungil());
	m.def("intersect", (shape(*)(const std::vector<const shape*>&))&make_intersect, ungil());

//TRANS
	py::class_<transformation>(m, "transformation")
	.def("__call__", (shape(transformation::*)(const shape&)const)&transformation::operator(), ungil())
	.def("__call__", (point3(transformation::*)(const point3&)const)&transformation::operator(), ungil())
	.def("__call__", (vector3(transformation::*)(const vector3&)const)&transformation::operator(), ungil())
	.def("__call__", (transformation(transformation::*)(const transformation&)const)&transformation::operator(), ungil())
	.def("__mul__", &transformation::operator*, ungil())
	.def("invert", &transformation::invert)
	.def(py::pickle(
	[](const transformation & self) { return b64::base64_encode(self.string_dump()); },
	[](const std::string & in) { return transformation::restore_string_dump(b64::base64_decode(in)); }), ungil())
	;

	py::class_<general_transformation>(m, "general_transformation")
	.def("__call__", (shape(general_transformation::*)(const shape&)const)&general_transformation::operator(), ungil())
	.def("__call__", (general_transformation(general_transformation::*)(const general_transformation&)const)&general_transformation::operator(), ungil())
	//.def("__mul__", &general_transformation::operator* )
	.def(py::pickle(
	[](const general_transformation & self) { return b64::base64_encode(self.string_dump()); },
	[](const std::string & in) { return general_transformation::restore_string_dump(b64::base64_decode(in)); }), ungil())
	;

	m.def("translate", (transformation(*)(double, double, double)) &translate, ungil());
	m.def("translate", (transformation(*)(double, double)) &translate, ungil());
	m.def("translate", (transformation(*)(const vector3&)) &translate, ungil());
	m.def("axrotation", axrotation, ungil());
	m.def("axis_mirror", axis_mirror, ungil());
	m.def("plane_mirror", plane_mirror, ungil());

	m.def("rotate", rotate, ungil());
	m.def("rotateX", rotateX, ungil());
	m.def("rotateY", rotateY, ungil());
	m.def("rotateZ", rotateZ, ungil());
	m.def("mirrorX", mirrorX, ungil());
	m.def("mirrorY", mirrorY, ungil());
	m.def("mirrorZ", mirrorZ, ungil());
	m.def("mirrorXY", mirrorXY, ungil());
	m.def("mirrorXZ", mirrorXZ, ungil());
	m.def("mirrorYZ", mirrorYZ, ungil());
	m.def("up", up, ungil());
	m.def("down", down, ungil());
	m.def("left", left, ungil());
	m.def("right", right, ungil());
	m.def("forw", forw, ungil());
	m.def("back", back, ungil());
	m.def("scale", scale, ungil(), py::arg("factor"), py::arg("center") = servoce::point3());
	m.def("scaleX", scaleX, ungil(), py::arg("factor"));
	m.def("scaleY", scaleY, ungil(), py::arg("factor"));
	m.def("scaleZ", scaleZ, ungil(), py::arg("factor"));

	//m.def("scaleX", scale, py::arg("factor"), py::arg("center") = servoce::point3());
	//m.def("scaleY", scale, py::arg("factor"), py::arg("center") = servoce::point3());
	//m.def("scaleZ", scale, py::arg("factor"), py::arg("center") = servoce::point3());

	//m.def("simplify_with_bspline", &simplify_with_bspline);

//GRAPHIC
	py::class_<color>(m, "Color")
	.def(py::init<float, float, float>(), ungil())
	.def(py::init<float, float, float,float>(), ungil())
	.def(py::pickle(
	[](const color & self)
	{
		float arr[4] = {self.r, self.g, self.b, self.a};
		return b64::base64_encode((uint8_t*)&arr, 4 * sizeof(float));
	},
	[](const std::string & in)
	{
		float arr[4];
		std::string decoded = b64::base64_decode(in);
		memcpy(&arr, decoded.data(), 4 * sizeof(float));
		return color{arr[0],arr[1],arr[2],arr[3]};
	}), ungil())
	;

	py::class_<shape_view>(m, "ShapeView")
	.def("shape", &shape_view::shape, ungil())
	.def("color", &shape_view::color, ungil())
	;

	py::class_<shape_view_controller>(m, "ShapeViewController")
	.def("set_location", &shape_view_controller::set_location, ungil())
	.def("hide", &shape_view_controller::hide, ungil())
	;

	py::class_<scene>(m, "Scene")
	.def(py::init<>(), ungil())
	.def("add", (shape_view_controller(scene::*)(const shape&, color))&scene::add, py::arg("shape"), py::arg("color") = color{0.6, 0.6, 0.8}, ungil())
	.def("add", (void(scene::*)(const point3&, color))&scene::add, py::arg("shape"), py::arg("color") = color{0.6, 0.6, 0.8}, ungil())
	.def("append", (void(scene::*)(const scene&))&scene::append, py::arg("scene"), ungil())
	.def("shapes_array", (std::vector<shape>(scene::*)())&scene::shapes_array, ungil())
	.def("color_array", (std::vector<color>(scene::*)())&scene::color_array, ungil())
	.def("__getitem__", [](const scene & s, size_t i) { return s[i]; }, ungil())
	;

	py::class_<viewer>(m, "Viewer")
	//.def(py::init<>())
	.def(py::init<scene&>(), ungil())
	.def("create_view", &viewer::create_view, ungil())
	.def("redraw", &viewer::redraw, ungil())
	.def("close", &viewer::close, ungil())
	.def("add_scene", &viewer::add_scene, ungil())
	.def("clean_context", &viewer::clean_context, ungil())
	.def("set_triedron_axes", &viewer::set_triedron_axes, ungil())
	;

	py::class_<view>(m, "View")
	.def("set_window", &view::set_window, ungil())
	.def("set_virtual_window", &view::set_virtual_window, ungil())
	.def("set_triedron", &view::set_triedron, ungil())
	.def("see", &view::see, ungil())
	.def("redraw", &view::redraw, ungil())
	.def("must_be_resized", &view::must_be_resized, ungil())
	.def("fit_all", &view::fit_all, py::arg("scale")=0.1, ungil())
	.def("set_direction", &view::set_direction, ungil())
	.def("direction", &view::direction, ungil())
	.def("pan", &view::pan, ungil())
	.def("zoom", &view::zoom, ungil())
	.def("set_eye", &view::set_eye, ungil())
	.def("eye", &view::eye, ungil())
	.def("set_center", &view::set_center, ungil())
	.def("center", &view::center, ungil())
	.def("set_orthogonal", &view::set_orthogonal, ungil())

	.def("set_gradient", &view::set_gradient, ungil())
	.def("reset_orientation", &view::reset_orientation, ungil())
	.def("autoscale", &view::autoscale, ungil())
	.def("centering", &view::centering, ungil())
	.def("start_rotation", &view::start_rotation, ungil())
	.def("rotation", &view::rotation, ungil())

	.def("rawarray", (std::vector<unsigned char>(view::*)())&view::rawarray, ungil())
	.def("rawarray", (std::vector<unsigned char>(view::*)(int,int))&view::rawarray, ungil())
	//.def("screen", &view::screen)
	.def("see", &view::see, ungil())

	.def("intersect_point", &view::intersect_point, ungil())
	;

//CONVERT
	m.def("make_stl", &make_stl, ungil());
	m.def("brep_write", &brep_write, ungil());
	m.def("brep_read", &brep_read, ungil());

//REFLECTION
	m.def("near_edge", &near_edge, ungil());	
	m.def("near_face", &near_face, ungil());
	m.def("near_vertex", &near_vertex, ungil());
}

servoce::point3::point3(const py::list& lst)
{
	if (lst.size() >= 1) x = lst[0].cast<double>();

	if (lst.size() >= 2) y = lst[1].cast<double>();

	if (lst.size() >= 3) z = lst[2].cast<double>();
}

servoce::point3::point3(const py::tuple& lst)
{
	if (lst.size() >= 1) x = lst[0].cast<double>();

	if (lst.size() >= 2) y = lst[1].cast<double>();

	if (lst.size() >= 3) z = lst[2].cast<double>();
}

servoce::vector3::vector3(const py::list& lst)
{
	if (lst.size() >= 1) x = lst[0].cast<double>();

	if (lst.size() >= 2) y = lst[1].cast<double>();

	if (lst.size() >= 3) z = lst[2].cast<double>();
}

servoce::vector3::vector3(const py::tuple& lst)
{
	if (lst.size() >= 1) x = lst[0].cast<double>();

	if (lst.size() >= 2) y = lst[1].cast<double>();

	if (lst.size() >= 3) z = lst[2].cast<double>();
}


servoce::point2::point2(const py::list& lst)
{
	if (lst.size() >= 1) x = lst[0].cast<double>();

	if (lst.size() >= 2) y = lst[1].cast<double>();
}

servoce::point2::point2(const py::tuple& lst)
{
	if (lst.size() >= 1) x = lst[0].cast<double>();

	if (lst.size() >= 2) y = lst[1].cast<double>();
}
