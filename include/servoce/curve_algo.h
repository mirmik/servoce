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
		Self& self() { return (Self&)*this; }
		const Self& self() const { return (const Self&) *this; }

	public:
		double length() const
		{
			auto adaptor = self().AdaptorCurve();
			return GCPnts_AbscissaPoint::Length(adaptor);
		}

		PointType d0(double arg) const 
		{
			gp_Pnt pnt;
			self().AdaptorCurve().D0(arg, pnt);
			return pnt;
		}

		std::pair<PointType, VectorType> d1(double arg) const 
		{
			gp_Vec vec;
			gp_Pnt pnt;
			self().AdaptorCurve().D1(arg, pnt, vec);
			return { pnt, vec };
		}

		double linoff(double dist, double start) const 
		{
			auto adaptor = self().AdaptorCurve();
			GCPnts_AbscissaPoint algo(adaptor, dist, start);
			return algo.Parameter();
		}

		/*double linoff(double dist) const 
		{
			auto adaptor = self().AdaptorCurve();
			GCPnts_AbscissaPoint algo(adaptor, dist, adaptor.FirstParameter());
			return algo.Parameter();
		}*/

		std::pair<double,double> range() const
		{
			auto adaptor = self().AdaptorCurve();
			return { adaptor.FirstParameter(), adaptor.LastParameter() };
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
			GCPnts_UniformAbscissa algo(adaptor, npoints, strt, fini);

			for (int i = 0; i < npoints; ++i)
			{
				gp_Pnt pnt;
				adaptor.D0(algo.Parameter(i+1), pnt);
				ret.push_back(pnt);
			}

			return ret;
		}

		std::vector<PointType> uniform_points(int npoints) const
		{
			std::vector<PointType> ret;

			auto adaptor = self().AdaptorCurve();
			GCPnts_UniformAbscissa algo(adaptor, npoints);

			for (int i = 0; i < npoints; ++i)
			{
				//nos::println(i, algo.Parameter(i+1));
				gp_Pnt pnt;
				adaptor.D0(algo.Parameter(i+1), pnt);
				ret.push_back(pnt);
			}

			return ret;
		}
	};
}

#endif