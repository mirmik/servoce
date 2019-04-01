#ifndef SERVOCE_CONVERT_H
#define SERVOCE_CONVERT_H

#include <string>
#include <servoce/servoce.h>

#include <gp_Ax2.hxx>
#include <BRepLib.hxx>
#include <HLRBRep_Algo.hxx>
#include <HLRBRep_HLRToShape.hxx>

namespace servoce
{
	class shape;
	bool make_stl(const servoce::shape& shp, const std::string& path, double deflection = 0.01);

	void brep_write(const servoce::shape& shp, const std::string& path);
	servoce::shape brep_read(const std::string& path);


	class project_builder 
	{
		Handle(HLRBRep_Algo) hlr;
		HLRAlgo_Projector projector;
		std::unique_ptr<HLRBRep_HLRToShape> hlr_shapes;

	public:
		project_builder(const servoce::shape& shp) : 
			projector(gp_Ax2(gp_Pnt(), gp_Dir(0,0,1)))
		{
			hlr = new HLRBRep_Algo;
			hlr->Add(shp.Shape());

			hlr_shapes = std::make_unique<HLRBRep_HLRToShape>(hlr);

			hlr->Projector(projector);
    		hlr->Update();
    		hlr->Hide();
		}

		servoce::shape vcompound() { 
			auto shape = hlr_shapes->VCompound(); 
			BRepLib::BuildCurves3d(shape);
			return shape;
		}
		
		servoce::shape hcompound() { 
			auto shape = hlr_shapes->HCompound(); 
			BRepLib::BuildCurves3d(shape);
			return shape;
		}
		
		servoce::shape rg1linevcompound() { 
			auto shape = hlr_shapes->OutLineVCompound(); 
			BRepLib::BuildCurves3d(shape);
			return shape;
		}

		servoce::shape outlinevcompound() { 
			auto shape = hlr_shapes->OutLineVCompound(); 
			BRepLib::BuildCurves3d(shape);
			return shape;
		}
		
		servoce::shape outlinehcompound() { 
			auto shape = hlr_shapes->OutLineHCompound(); 
			BRepLib::BuildCurves3d(shape);
			return shape;
		}

		
	};

	std::string getSVG(const servoce::shape& shp);
	std::string makeSVGedge(const TopoDS_Edge& edge);
	std::vector<std::string> getPaths(const servoce::shape& shp);
}

#endif