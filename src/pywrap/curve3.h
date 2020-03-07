py::class_<curve3>(m, "curve3")
.def("value", &curve3::value)
.def("range", &curve3::range)
.def(py::pickle(
[](const curve3 & self) { return b64::base64_encode(string_dump(self)); },
[](const std::string & in) { return restore_string_dump<curve3>(b64::base64_decode(in)); }), ungil())
;

py::class_<bounded_curve3, curve3>(m, "bounded_curve3")
.def(py::pickle(
[](const bounded_curve3 & self) { return b64::base64_encode(string_dump(self)); },
[](const std::string & in) { return restore_string_dump<bounded_curve3>(b64::base64_decode(in)); }), ungil())
;

// basic:
m.def("line_curve3",
      &line_curve3, ungil());

m.def("bezier_curve3", (bounded_curve3(*)(const std::vector<point3>&))
      &bezier_curve3, ungil(),
      py::arg("pnts"));

m.def("bezier_curve3", (bounded_curve3(*)(const std::vector<point3>&, const std::vector<double>&))
      &bezier_curve3, ungil(),
      py::arg("pnts"),
      py::arg("weights"));

m.def("bspline_curve3", (bounded_curve3(*)(
                             const std::vector<point3>& poles, const std::vector<double>& knots, const std::vector<int>& multiplicities,
                             int degree, bool periodic))
      &bspline_curve3, ungil(),
      py::arg("pnts"),
      py::arg("knots"),
      py::arg("multiplicities"),
      py::arg("degree"),
      py::arg("periodic") = false);

m.def("bspline_curve3", (bounded_curve3(*)(
                             const std::vector<point3>& poles, const std::vector<double>& weights, const std::vector<double>& knots, const std::vector<int>& multiplicities,
                             int degree, bool periodic, bool check_rational))
      &bspline_curve3, ungil(),
      py::arg("pnts"),
      py::arg("knots"),
      py::arg("weights"),
      py::arg("multiplicities"),
      py::arg("degree"),
      py::arg("periodic") = false,
      py::arg("check_rational") = true
     );

// advanced:
m.def("interpolate_curve3", (curve3(*)(const std::vector<point3>&, const std::vector<vector3>&, bool))
      &interpolate_curve3, ungil(),
      py::arg("pnts"),
      py::arg("tang"),
      py::arg("closed") = false
     );
m.def("interpolate_curve3", (curve3(*)(const std::vector<point3>&, const bool))
      &interpolate_curve3, ungil(),
      py::arg("pnts"),
      py::arg("closed") = false
     );

