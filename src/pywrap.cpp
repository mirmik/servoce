#include <servoce/servoce.h>
#include <servoce/geomprops.h>
#include <servoce/util/b64.h>
#include <servoce/vertex.h>

#include <local/pywrap_util.h>

#include <exception>
#include <Standard_Failure.hxx>

namespace py = pybind11;
using namespace servoce;

void registry_shape(py::module &);
void registry_wire_shape(py::module &);
void registry_edge_shape(py::module &);
void registry_shell_shape(py::module &);
void registry_solid_shape(py::module & m);
void registry_face_shape(py::module &);
void registry_surface_shape(py::module &);
void registry_trans(py::module &);

void registry_geombase_shape(py::module & m);
void registry_displayable(py::module & m);
void registry_interactive_object(py::module & m);
void registry_coord_system(py::module & m);

void registry_sweep_shape(py::module & m);
void registry_other(py::module & m);

PYBIND11_MODULE(libservoce, m)
{
// EXCEPTIONS
	static py::exception<Standard_Failure> standart_failure(m, 
		"OpenCascade_Standard_Failure");
	
	static py::exception<Standard_ConstructionError> construction_error(m, 
		"OpenCascade_Standard_ConstructionError");

	py::register_exception_translator([](std::exception_ptr p)
	{
		try
		{
			if (p) std::rethrow_exception(p);
		}
		catch (const Standard_ConstructionError &e)
		{
			construction_error(e.GetMessageString());
		}
		catch (const Standard_Failure &e)
		{
			standart_failure(e.GetMessageString());	
		}
	});


	py::class_<boundbox>(m, "boundbox")
	.def_readonly("xmin", &servoce::boundbox::xmin)
	.def_readonly("ymin", &servoce::boundbox::ymin)
	.def_readonly("zmin", &servoce::boundbox::zmin)
	.def_readonly("xmax", &servoce::boundbox::xmax)
	.def_readonly("ymax", &servoce::boundbox::ymax)
	.def_readonly("zmax", &servoce::boundbox::zmax)
	.def("xrange", &servoce::boundbox::xrange)
	.def("yrange", &servoce::boundbox::yrange)
	.def("zrange", &servoce::boundbox::zrange)
	.def("max0", &servoce::boundbox::max0)
	.def("corner_min", &servoce::boundbox::corner_min)
	.def("corner_max", &servoce::boundbox::corner_max)
	.def("shape", &servoce::boundbox::shape)
	.def("__repr__", [](const boundbox & box)
	{
		char buf[128];
		sprintf(buf, "bbox(x:(%f,%f),y:(%f,%f),z:(%f,%f))", 
			(double)box.xmin, (double)box.xmax, 
			(double)box.ymin, (double)box.ymax, 
			(double)box.zmin, (double)box.zmax);
		return std::string(buf);
	})
	.def(py::pickle(
	[](const boundbox & self)
	{
		double arr[6] = {self.xmin, self.ymin, self.zmin, self.xmax, self.ymax, self.zmax};
		return b64::base64_encode((uint8_t*)&arr, 6 * sizeof(double));
	},
	[](const std::string & in)
	{
		double arr[6];
		std::string decoded = b64::base64_decode(in);
		memcpy(&arr, decoded.data(), 6 * sizeof(double));
		return boundbox{arr[0],arr[1],arr[2],arr[3],arr[4],arr[5]};
	}), ungil())
	;

	registry_geombase_shape(m);
	registry_surface_shape(m);

	registry_shape(m);
	registry_edge_shape(m);
	registry_wire_shape(m);
	registry_face_shape(m);
	registry_shell_shape(m);
	registry_solid_shape(m);

	registry_trans(m);
	registry_coord_system(m);

	registry_sweep_shape(m);

	m.def("fillet", (shape(*)(const shape&, double, const std::vector<point3>&))&servoce::fillet, ungil(), py::arg("shp"), py::arg("r"), py::arg("refs"));
	m.def("fillet", (shape(*)(const shape&, double))&servoce::fillet, ungil(), py::arg("shp"), py::arg("r"));
	m.def("chamfer", (shape(*)(const shape&, double, const std::vector<point3>&))&servoce::chamfer, ungil(), py::arg("shp"), py::arg("r"), py::arg("refs"));
	m.def("chamfer", (shape(*)(const shape&, double))&servoce::chamfer, ungil(), py::arg("shp"), py::arg("r"));
	
	m.def("fillet2d", (shape(*)(const shape&, double, const std::vector<point3>&))&servoce::fillet2d, ungil(), py::arg("shp"), py::arg("r"), py::arg("refs"));
	m.def("fillet2d", (shape(*)(const shape&, double))&servoce::fillet2d, ungil(), py::arg("shp"), py::arg("r"));
	m.def("chamfer2d", (face_shape(*)(const shape&, double, const std::vector<point3>&))&servoce::chamfer2d, ungil(), py::arg("shp"), py::arg("r"), py::arg("refs"));
	m.def("chamfer2d", (face_shape(*)(const shape&, double))&servoce::chamfer2d, ungil(), py::arg("shp"), py::arg("r"));


	m.def("unify", 		&unify, ungil());

//OPS3D

//SURFACE
	
//CURVE2
	py::class_<curve2::curve2>(m, "curve2")
		.def("value", &curve2::curve2::value)
		.def(py::pickle(
		[](const curve2::curve2 & self) { return b64::base64_encode(string_dump(self)); },
		[](const std::string & in) { return restore_string_dump<curve2::curve2>(b64::base64_decode(in)); }), ungil())
		.def("rotate", &curve2::curve2::rotate, ungil())
	;
	py::class_<curve2::trimmed_curve2, curve2::curve2>(m, "trimmed_curve2")
		.def(py::init<const curve2::curve2&, double, double>(), ungil())
	;
	m.def("curve2_ellipse", curve2::ellipse, ungil());
	m.def("curve2_segment", curve2::segment, ungil());

//CURVE3
	#include <pywrap/curve3.h>

//BOOLEAN
	m.def("union", (shape(*)(const std::vector<const shape*>&))&make_union, ungil());
	m.def("difference", (shape(*)(const std::vector<const shape*>&))&make_difference, ungil());
	m.def("intersect", (shape(*)(const std::vector<const shape*>&))&make_intersect, ungil());
	m.def("section", (shape(*)(const shape&, const shape&,bool))&make_section, ungil());
	m.def("section", (shape(*)(const shape&,bool))&make_section, ungil());


//GRAPHIC
	py::class_<color>(m, "Color")
	.def(py::init<>(), ungil())
	.def(py::init<py::list>())
	.def(py::init<py::tuple>())
	.def(py::init<const color&>(), ungil())
	.def(py::init<float, float, float>(), ungil())
	.def(py::init<float, float, float,float>(), ungil())
	.def_readwrite("r", &color::r)
	.def_readwrite("g", &color::g)
	.def_readwrite("b", &color::b)
	.def_readwrite("a", &color::a)
	.def(py::pickle(
	[](const color & self)
	{
		double arr[4] = {self.r, self.g, self.b, self.a};
		return b64::base64_encode((uint8_t*)&arr, 4 * sizeof(double));
	},
	[](const std::string & in)
	{
		float arr[4];
		std::string decoded = b64::base64_decode(in);
		memcpy(&arr, decoded.data(), 4 * sizeof(double));
		return color{arr[0],arr[1],arr[2],arr[3]};
	}), ungil())
	.def("__repr__", [](const color & pnt)
	{
		char buf[128];
		sprintf(buf, "Color(%f,%f,%f,%f)", (double)pnt.r, (double)pnt.g, (double)pnt.b, (double)pnt.a);
		return std::string(buf);
	})
	;

	registry_interactive_object(m);

	py::class_<scene>(m, "Scene")
	.def(py::init<>(), ungil())
	.def_readonly("viewer", &scene::vwer, py::return_value_policy::reference)
	.def("add", (std::shared_ptr<interactive_object>(scene::*)(const shape&, color))&scene::add, py::arg("shape"), py::arg("color") = color{0.6, 0.6, 0.8}, ungil())
	.def("add", (std::shared_ptr<interactive_object>(scene::*)(const point3&, color))&scene::add, py::arg("shape"), py::arg("color") = color{0.6, 0.6, 0.8}, ungil())
	.def("add", (std::shared_ptr<interactive_object>(scene::*)(std::shared_ptr<servoce::interactive_object>))&scene::add, py::arg("iobj"), ungil())
	//.def("append", (void(scene::*)(const scene&))&scene::append, py::arg("scene"), ungil())
	//.def("shapes_array", (std::vector<shape>(scene::*)())&scene::shapes_array, ungil())
	//.def("color_array", (std::vector<color>(scene::*)())&scene::color_array, ungil())
	.def("__getitem__", &scene::operator[])
	.def("bbox", &scene::bbox, ungil())
	.def("total", &scene::total, ungil())
	.def("set_chordial_deviation", &scene::set_chordial_deviation, ungil(), py::arg("relative"), py::arg("deviation"))
	//.def("__getitem__", [](const scene & s, size_t i) { return s[i]; }, ungil())
	;

	py::class_<viewer, std::shared_ptr<viewer>>(m, "Viewer")
	.def("create_view", &viewer::create_view, ungil())
	.def("redraw", &viewer::redraw, ungil())
	.def("close", &viewer::close, ungil())
	.def("remove", &viewer::remove, ungil())
//	.def("add_scene", &viewer::add_scene, ungil())
	.def("clean_context", &viewer::clean_context, ungil())
//	.def("display", (void(viewer::*)(shape_view&))&viewer::display, ungil())
	.def("display", (void(viewer::*)(interactive_object&))&viewer::display, ungil())
	.def("set_triedron_axes", &viewer::set_triedron_axes, py::arg("en")=true, ungil())
	;

	py::class_<view, std::shared_ptr<servoce::view>>(m, "View")
	.def("set_window", &view::set_window, ungil())
	.def("set_virtual_window", &view::set_virtual_window, ungil())
	.def("set_triedron", &view::set_triedron, py::arg("en")=true, ungil())
	.def("see", &view::see, ungil())
	.def("destroy", &view::destroy, ungil())
	.def("redraw", &view::redraw, ungil())
	.def("redraw_immediate", &view::redraw_immediate, ungil())
	.def("must_be_resized", &view::must_be_resized, ungil())
	.def("fit_all", &view::fit_all, py::arg("scale")=0.1, ungil())
	.def("set_direction", &view::set_direction, ungil())
	.def("direction", &view::direction, ungil())
	.def("pan", &view::pan, ungil())
	.def("zoom", &view::zoom, ungil())
	.def("remove", &view::remove, ungil())
	.def("scale", &view::scale, ungil())
	.def("set_scale", &view::set_scale, ungil())
	.def("set_eye", &view::set_eye, ungil())
	.def("eye", &view::eye, ungil())
	.def("set_center", &view::set_center, ungil())
	.def("set_perspective", &view::set_perspective, ungil())
	.def("center", &view::center, ungil())
	//.def("resize", &view::resize, ungil())
	.def("size", &view::size, ungil())
	.def("set_orthogonal", &view::set_orthogonal, ungil())

	.def("set_gradient", &view::set_gradient, ungil())
	.def("set_background", &view::set_background, ungil())
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

// CONVERT
	m.def("make_stl", &make_stl, ungil());
	m.def("brep_write", &brep_write, ungil());
	m.def("brep_read", &brep_read, ungil());

	m.def("getSVG", &getSVG, ungil());

// REFLECTION
	m.def("near_edge", &near_edge, ungil());	
	m.def("near_face", &near_face, ungil());
	m.def("near_vertex", &near_vertex, ungil());

// PRESENTATION
	m.attr("white") = white;
	m.attr("black") = black;
	m.attr("red") = red;
	m.attr("green") = green;
	m.attr("blue") = blue;
	m.attr("yellow") = yellow;
	m.attr("gray") = gray;
	m.attr("mech") = mech;

	py::enum_<line_style>(m, "line_style")
		.value("solid_line", line_style::solid_line)
		.value("dash_line", line_style::dash_line)
		.value("dot_line", line_style::dot_line)
		.value("dotdash_line", line_style::dotdash_line)
	.export_values();

	m.def("draw_arrow", &draw::arrow, py::arg("pnt"), py::arg("vec"), py::arg("clr")=yellow, py::arg("arrlen")=1, py::arg("width")=1);
	m.def("draw_line", &draw::line, py::arg("a"), py::arg("b"), py::arg("clr")=black, py::arg("style")=line_style::solid_line, py::arg("width")=1);
	m.def("axis", &draw::axis, py::arg("pnt"), py::arg("dir"), py::arg("clr")=white);

	py::class_<geomprops>(m, "geomprops")
	//	.def("volume_properties", &geomprops::volume_properties)
		.def("mass", &geomprops::mass)
	//	.def("cmpoint", &GProp_GProps::CentreOfMass)
		.def("cmradius", &geomprops::cmradius)
		.def("center", &geomprops::center)
	//	.def("inermat", &GProp_GProps::MatrixOfInertia)
	;

	registry_displayable(m);
	registry_other(m);

	m.def("close_display_connection", &close_display_connection);
	m.def("vertex", &servoce::make_vertex);
}

std::vector<servoce::point3> points(const py::list& lst) 
{
	std::vector<servoce::point3> ret;
	ret.reserve(lst.size());
	for (auto& l : lst) 
	{
		bool b = py::isinstance<py::list>(l);
		if (b)
			ret.emplace_back(servoce::point3(l.cast<py::list>()));
		else 
			ret.emplace_back(l.cast<servoce::point3>());
	}
	return ret;
} 
