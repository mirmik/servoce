#ifndef SERVOCE_CURVE_ALGO_H
#define SERVOCE_CURVE_ALGO_H

#include <GCPnts_AbscissaPoint.hxx>
#include <GCPnts_UniformAbscissa.hxx>

#include <vector>

namespace servoce
{
	template<class Self, class PointType, class VectorType>
	class curve_algo
	{
		Self& self() { return (Self&) * this; }
		const Self& self() const { return (const Self&) * this; }

	public:
		double length() const
		{
			auto adaptor = self().AdaptorCurve();
			return GCPnts_AbscissaPoint::Length(*adaptor);
		}

		PointType d0(double arg) const
		{
			gp_Pnt pnt;
			self().AdaptorCurve()->D0(arg, pnt);
			return pnt;
		}

		std::pair<PointType, VectorType> d1(double arg) const
		{
			gp_Vec vec;
			gp_Pnt pnt;
			self().AdaptorCurve()->D1(arg, pnt, vec);
			return { pnt, vec };
		}

		double linoff(double dist, double start) const
		{
			auto adaptor = self().AdaptorCurve();
			GCPnts_AbscissaPoint algo(*adaptor, dist, start);
			return algo.Parameter();
		}

		/*double linoff(double dist) const
		{
			auto adaptor = self().AdaptorCurve();
			GCPnts_AbscissaPoint algo(adaptor, dist, adaptor.FirstParameter());
			return algo.Parameter();
		}*/

		std::pair<double, double> range() const
		{
			auto adaptor = self()->AdaptorCurve();
			return { adaptor->FirstParameter(), adaptor->LastParameter() };
		}

		PointType linoff_point(double dist, double start) const
		{
			return d0(linoff(dist, start));
		}

		/*PointType linoff_point(double dist) const
		{
			return d0(linoff(dist));
		}*/

		std::vector<PointType> uniform_points(int npoints, double strt, double fini) const
		{
			std::vector<PointType> ret;

			auto adaptor = self().AdaptorCurve();
			GCPnts_UniformAbscissa algo(*adaptor, npoints, strt, fini);

			for (int i = 0; i < npoints; ++i)
			{
				gp_Pnt pnt;
				adaptor->D0(algo.Parameter(i + 1), pnt);
				ret.push_back(pnt);
			}

			return ret;
		}

		std::vector<PointType> uniform_points(int npoints) const
		{
			std::vector<PointType> ret;

			auto adaptor = self().AdaptorCurve();
			GCPnts_UniformAbscissa algo(*adaptor, npoints);

			for (int i = 0; i < npoints; ++i)
			{
				//nos::println(i, algo.Parameter(i+1));
				gp_Pnt pnt;
				adaptor->D0(algo.Parameter(i + 1), pnt);
				ret.push_back(pnt);
			}

			return ret;
		}

		std::vector<double> uniform(int npoints, double strt, double fini) const
		{
			std::vector<double> ret;

			auto adaptor = self().AdaptorCurve();
			GCPnts_UniformAbscissa algo(*adaptor, npoints, strt, fini);

			for (int i = 0; i < npoints; ++i)
			{
				ret.push_back(algo.Parameter(i + 1));
			}

			return ret;
		}

		std::vector<double> uniform(int npoints) const
		{
			std::vector<double> ret;

			auto adaptor = self().AdaptorCurve();
			GCPnts_UniformAbscissa algo(*adaptor, npoints);

			for (int i = 0; i < npoints; ++i)
			{
				ret.push_back(algo.Parameter(i + 1));
			}

			return ret;
		}
	};

	template<class Self>
	class curve3_algo : public curve_algo<Self, servoce::point3, servoce::vector3>
	{
		Self& self() { return (Self&) * this; }
		const Self& self() const { return (const Self&) * this; }

	public:
		virtual std::unique_ptr<Adaptor3d_Curve> AdaptorCurve() const = 0;

		std::string curvetype()
		{
			auto adaptor = AdaptorCurve();
			auto type = adaptor->GetType();

			switch (type)
			{
				case GeomAbs_Line: return "line";
				case GeomAbs_Circle: return "circle";
				case GeomAbs_Ellipse: return "ellipse";
				case GeomAbs_Hyperbola: return "hyperbola";
				case GeomAbs_Parabola: return "parabola";
				case GeomAbs_BezierCurve: return "bezier";
				case GeomAbs_BSplineCurve: return "bspline";
				case GeomAbs_OffsetCurve: return "offset";
				case GeomAbs_OtherCurve: return "other";
				default: throw std::runtime_error("undefined curvetype");
			}
		}

		std::pair<point3, vector3> 
		line_parameters()
		{
			if (curvetype() != "line")
				throw std::runtime_error("curve is not line");

			gp_Lin o = AdaptorCurve()->Line();

			return {o.Location(), o.Direction()};
		}


		std::tuple<point3, double, vector3, vector3> 
		circle_parameters()
		{
			if (curvetype() != "circle")
				throw std::runtime_error("curve is not circle");

			gp_Circ o = AdaptorCurve()->Circle();
			gp_Ax2 p = o.Position();

			return std::make_tuple(point3(p.Location()), o.Radius(), vector3(p.XDirection()), vector3(p.YDirection()));
		}

		/*std::tuple<point3, double, double, vector3, vector3> 
		ellipse_parameters()
		{
			if (curvetype() != "circle")
				throw std::runtime_error("curve is not circle");

			gp_Elips o = AdaptorCurve().Line();
			gp_Ax2 p = o.Position();

			return {p.Location(), p.XDirection(), p.YDirection()};
		}*/
	};
}

#endif