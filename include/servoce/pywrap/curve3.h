py::class_<curve3::curve3>(m, "curve3")
.def("value", &curve3::curve3::value)
.def(py::pickle(
[](const curve3::curve3 & self) { return b64::base64_encode(string_dump(self)); },
[](const std::string & in) { return restore_string_dump<curve3::curve3>(b64::base64_decode(in)); }), ungil())
;

py::class_<curve3::bounded_curve3, curve3::curve3>(m, "bounded_curve3")
.def(py::pickle(
[](const curve3::bounded_curve3 & self) { return b64::base64_encode(string_dump(self)); },
[](const std::string & in) { return restore_string_dump<curve3::bounded_curve3>(b64::base64_decode(in)); }), ungil())
;

// basic:
m.def("curve3_line",
      &curve3::line, ungil());

m.def("curve3_bezier", (curve3::bounded_curve3(*)(const std::vector<point3>&))
      &curve3::bezier, ungil(),
      py::arg("pnts"));

m.def("curve3_bezier", (curve3::bounded_curve3(*)(const std::vector<point3>&, const std::vector<double>&))
      &curve3::bezier, ungil(),
      py::arg("pnts"),
      py::arg("weights"));

m.def("curve3_bspline", (curve3::bounded_curve3(*)(
                             const std::vector<point3>& poles, const std::vector<double>& knots, const std::vector<int>& multiplicities,
                             int degree, bool periodic))
      &curve3::bspline, ungil(),
      py::arg("pnts"),
      py::arg("knots"),
      py::arg("multiplicities"),
      py::arg("degree"),
      py::arg("periodic") = false);

m.def("curve3_bspline", (curve3::bounded_curve3(*)(
                             const std::vector<point3>& poles, const std::vector<double>& weights, const std::vector<double>& knots, const std::vector<int>& multiplicities,
                             int degree, bool periodic, bool check_rational))
      &curve3::bspline, ungil(),
      py::arg("pnts"),
      py::arg("knots"),
      py::arg("weights"),
      py::arg("multiplicities"),
      py::arg("degree"),
      py::arg("periodic") = false,
      py::arg("check_rational") = true
     );

// advanced:
m.def("curve3_interpolate", (curve3::curve3(*)(const std::vector<point3>&, const std::vector<vector3>&, bool))
      &curve3::interpolate, ungil(),
      py::arg("pnts"),
      py::arg("tang"),
      py::arg("closed") = false
     );
m.def("curve3_interpolate", (curve3::curve3(*)(const std::vector<point3>&, const bool))
      &curve3::interpolate, ungil(),
      py::arg("pnts"),
      py::arg("closed") = false
     );

