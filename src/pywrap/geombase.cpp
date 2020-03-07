
#include <pybind11/pybind11.h>
#include <local/pywrap_util.h>

#include <servoce/util.h>
#include <servoce/util/b64.h>

#include <servoce/geombase.h>

#include <pywrap/transformable.h>
#include <pywrap/displayable.h>

namespace py = pybind11;
using namespace servoce;

void registry_geombase_shape(py::module & m)
{


// OBJECTS
	auto cls_point3=py::class_<point3>(m, "point3")
	.def(py::init<>())
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
	.def("__iter__", [](const point3 & p) {return py::make_iterator(&p.x, &p.x + 3);})
	.def("__len__", [](const point3&) {return 3;})
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
		sprintf(buf, "point3(%f,%f,%f)", (double)pnt.x, (double)pnt.y, (double)pnt.z);
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
	.def(py::init<>())
	.def(py::init<double, double>())
	.def(py::init<const servoce::point2&>())
	.def(py::init<py::list>())
	.def(py::init<py::tuple>())
	.def("__len__", [](const point2&) {return 2;})
	.def("__iter__", [](const point2 & p) {return py::make_iterator(&p.x, &p.x + 2);})
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
		sprintf(buf, "point2(%f,%f)", (double)pnt.x, (double)pnt.y);
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

	py::class_<xyz>(m, "xyz")
	.def("__add__", &gp_XYZ::operator+ )
	.def("__sub__", &gp_XYZ::operator- )
	.def("__mul__", (gp_XYZ(gp_XYZ::*)(double)const)&gp_XYZ::operator* )
	//.def("__mul__", (gp_XYZ(gp_XYZ::* const)(double))&gp_XYZ::operator* )
	.def("dot", &gp_XYZ::Dot)
	;

	auto cls_vector3=py::class_<vector3>(m, "vector3")
	.def(py::init<>())
	.def(py::init<const servoce::vector3&>())
	.def(py::init<double, double, double>())
	.def(py::init<double, double>())
	.def(py::init<py::list>())
	.def(py::init<py::tuple>())
	.def("to_point3", &vector3::to_point3)
	.def("__iter__", [](const vector3 & p) {return py::make_iterator(&p.x, &p.x + 3);})
	.def_readwrite("x", &vector3::x)
	.def_readwrite("y", &vector3::y)
	.def_readwrite("z", &vector3::z)
	.def("__len__", [](const vector3&) {return 3;})
	.def("__mul__", (vector3(*)(const vector3&, double)) &servoce::operator* )
	.def("__rmul__", (vector3(*)(const vector3&, double)) &servoce::operator* )
	.def("__truediv__", (vector3(*)(const vector3&, double)) &servoce::operator/ )
	.def("__add__", (vector3(*)(const vector3&, const vector3&)) &servoce::operator+ )
	.def("__sub__", (vector3(*)(const vector3&, const vector3&)) &servoce::operator- )
	.def("__neg__", (vector3(vector3::* const)()) &servoce::vector3::operator- )
	.def("__setitem__", [](vector3 & self, int key, double value) { self[key] = value; })
	.def("__getitem__", [](const vector3 & self, int key) { return self[key]; })
	.def("normalize", &vector3::normalize)
	.def("outerprod", &vector3::outerprod)
	.def("length", &vector3::length)
	.def("length2", &vector3::length2)
	.def("early", &vector3::early)
	.def("dot", &vector3::dot)
	.def("iszero", &vector3::iszero)
	.def("cross", &vector3::cross)
	.def("vecmul_matrix", &vector3::vecmul_matrix)
	.def("elementwise_mul", &vector3::elementwise_mul)
	.def("__repr__", [](const vector3 & pnt)
	{
		char buf[128];
		sprintf(buf, "vector3(%f,%f,%f)", (double)pnt.x, (double)pnt.y, (double)pnt.z);
		return std::string(buf);
	})
	.def(py::pickle(
	         [](const vector3 & self)
	{
		double arr[3] = {self.x, self.y, self.z};
		return b64::base64_encode((uint8_t*)&arr, 3 * sizeof(double));
	},
	[](const std::string & in)
	{
		double arr[3];
		std::string decoded = b64::base64_decode(in);
		memcpy(&arr, decoded.data(), 3 * sizeof(double));
		return vector3(arr);
	}))
	;

	py::class_<quaternion>(m, "quaternion")
	.def(py::init<>())
	.def(py::init<double, double, double, double>())
	.def(py::init<py::list>())
	.def(py::init<py::tuple>())
	.def("__iter__", [](const quaternion & p) {return py::make_iterator(&p.x, &p.x + 4);})
	.def_readwrite("x", &quaternion::x)
	.def_readwrite("y", &quaternion::y)
	.def_readwrite("z", &quaternion::z)
	.def_readwrite("w", &quaternion::w)
	.def("normalize", &quaternion::normalize)
	.def("__len__", [](const quaternion&) {return 4;})
	.def("rotation_vector", &quaternion::rotation_vector)
	.def("rotate", &quaternion::rotate)
	.def("to_matrix", &quaternion::to_matrix)
	.def("inverse", &quaternion::inverse)
	.def("__repr__", [](const quaternion & pnt)
	{
		char buf[128];
		sprintf(buf, "quaternion(%f,%f,%f,%f)", (double)pnt.x, (double)pnt.y, (double)pnt.z, (double)pnt.w);
		return std::string(buf);
	})
	.def(py::pickle(
	         [](const quaternion & self)
	{
		return b64::base64_encode((const uint8_t*)self.data(), 4 * sizeof(double));
	},
	[](const std::string & in)
	{
		double arr[4];
		std::string decoded = b64::base64_decode(in);
		memcpy(&arr, decoded.data(), 4 * sizeof(double));
		return quaternion(arr);
	}))
	;

	py::class_<matrix33>(m, "matrix33", py::buffer_protocol())
	.def(py::init<>())
	.def(py::init<double, double, double>())
	.def(py::init<double, double, double, double, double, double, double, double, double>())
	.def("inverse", &matrix33::inverse)
	.def("transpose", &matrix33::transpose)
	.def("__mul__", (matrix33(matrix33::*)(const matrix33&)) &matrix33::operator*)
	.def("__mul__", (vector3(matrix33::*)(const vector3&)) &matrix33::operator*)
	.def("__mul__", (matrix33(matrix33::*)(double)) &matrix33::operator*)
	.def("__rmul__", (matrix33(matrix33::*)(double)) &matrix33::operator*)
	.def("__add__", (matrix33(matrix33::*)(const matrix33&)) &matrix33::operator+)
	.def("__sub__", (matrix33(matrix33::*)(const matrix33&)) &matrix33::operator-)
	.def("__getitem__", (double & (matrix33::*)(std::pair<int, int>))&matrix33::operator())
	.def("__repr__", [](const matrix33 & m)
	{
		char buf[128];
		sprintf(buf, "matrix33(%f,%f,%f,%f,%f,%f,%f,%f,%f)",
		        m.x.x, m.y.x, m.z.x, m.x.y, m.y.y, m.z.y, m.x.z, m.y.z, m.z.z);
		return std::string(buf);
	})
	.def_buffer([](matrix33 & m) -> py::buffer_info
	{
		return py::buffer_info(
		    m.data(),                               /* Pointer to buffer */
		    sizeof(double),                          /* Size of one scalar */
		    py::format_descriptor<double>::format(), /* Python struct-style format descriptor */
		    2,                                      /* Number of dimensions */
		{ m.rows(), m.cols() },                 /* Buffer dimensions */
		{
			sizeof(double),             /* Strides (in bytes) for each index */
			sizeof(double) * m.cols()
		}
		);
	})
	.def(py::pickle(
	         [](const matrix33 & self)
	{
		return b64::base64_encode((const uint8_t*)self.data(), 9 * sizeof(double));
	},
	[](const std::string & in)
	{
		double arr[9];
		std::string decoded = b64::base64_decode(in);
		memcpy(&arr, decoded.data(), 9 * sizeof(double));
		return matrix33(arr);
	}))
	;

	pywrap_transformable<servoce::vector3>(cls_vector3);
	pywrap_transformable<servoce::point3>(cls_point3);
}