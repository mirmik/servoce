m.def("segment",
      make_segment, ungil()
     );

m.def("polysegment", (wire_shape(*)(const std::vector<point3>&, const bool))
      &make_polysegment, ungil(),
      py::arg("pnts"),
      py::arg("closed") = false
     );

m.def("interpolate", (edge_shape(*)(const std::vector<point3>&, const std::vector<vector3>&, bool))
      &make_interpolate, ungil(),
      py::arg("pnts"),
      py::arg("tang"),
      py::arg("closed") = false
     );

m.def("interpolate", (edge_shape(*)(const std::vector<point3>&, const bool))
      &make_interpolate, ungil(),
      py::arg("pnts"),
      py::arg("closed") = false
     );

m.def("bezier", (edge_shape(*)(const std::vector<point3>&, const std::vector<double>&))
      &bezier, ungil(),
      py::arg("pnts"),
      py::arg("weights")
     );

m.def("bezier", (edge_shape(*)(const std::vector<point3>&))
      &bezier, ungil(),
      py::arg("pnts")
     );

m.def("bspline", (edge_shape(*)(
                      const std::vector<point3>& poles, const std::vector<double>& knots, const std::vector<int>& multiplicities,
                      int degree, bool periodic))
      &bspline, ungil(),
      py::arg("pnts"),
      py::arg("knots"),
      py::arg("multiplicities"),
      py::arg("degree"),
      py::arg("periodic") = false
     );

m.def("bspline", (edge_shape(*)(
                      const std::vector<point3>& poles, const std::vector<double>& weights, const std::vector<double>& knots, const std::vector<int>& multiplicities,
                      int degree, bool periodic, bool check_rational))
      &bspline, ungil(),
      py::arg("pnts"),
      py::arg("knots"),
      py::arg("weights"),
      py::arg("multiplicities"),
      py::arg("degree"),
      py::arg("periodic") = false,
      py::arg("check_rational") = true
     );

m.def("helix",
      make_helix, ungil(),
      py::arg("step"),
      py::arg("height"),
      py::arg("radius"),
      py::arg("angle") = 0,
      py::arg("leftHanded") = false,
      py::arg("newStyle") = true
     );

m.def("long_helix",
      make_long_helix, ungil(),
      py::arg("step"),
      py::arg("height"),
      py::arg("radius"),
      py::arg("angle") = 0,
      py::arg("leftHanded") = false
     );

m.def("circle_arc",
      &circle_arc, ungil()
     );

m.def("sew",
      &sew, ungil()
     );

m.def("extract_curve", &extract_curve, ungil());