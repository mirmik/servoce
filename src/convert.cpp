#include <servoce/convert.h>
#include <servoce/topo.h>

#include <StlAPI_Writer.hxx>
#include <BRepMesh_IncrementalMesh.hxx>

#include <BRepTools.hxx>
#include <BRep_Builder.hxx>

#include <fstream>

#include <HLRBRep_Algo.hxx>
#include <HLRBRep_HLRToShape.hxx>
#include <GCPnts_QuasiUniformDeflection.hxx>
#include <BRepAdaptor_Curve.hxx>

bool servoce::make_stl(const servoce::shape& shp, const std::string& path, double deflection)
{
	BRepMesh_IncrementalMesh mesh(shp.Shape(), deflection);

	if (mesh.IsDone() == false) { return false; }

	StlAPI_Writer stl_writer;
	stl_writer.Write(shp.Shape(), path.c_str());
	return true;
}

void servoce::brep_write(const servoce::shape& shp, const std::string& path)
{
	std::ofstream file(path);
	BRepTools::Write(shp.Shape(), file);
}

servoce::shape servoce::brep_read(const std::string& path)
{
	TopoDS_Shape shp;
	BRep_Builder builder;
	std::ifstream file(path);

	BRepTools::Read (shp, file, builder);
	return servoce::shape(shp);
}

const char* SVG_TEMPLATE = R"x(<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<svg
    xmlns:svg="http://www.w3.org/2000/svg"
    xmlns="http://www.w3.org/2000/svg"
    width="{width}"
    height="{height}"
>
    <g transform="scale({unitScale}, -{unitScale})   translate({xTranslate},{yTranslate})" stroke-width="{strokeWidth}"  fill="none">
        <!-- hidden lines -->
        <g  stroke="rgb(160, 160, 160)" fill="none" stroke-dasharray="{strokeWidth},{strokeWidth}" >
{hiddenContent}        </g>
        <!-- solid lines -->
        <g  stroke="rgb(0, 0, 0)" fill="none">
{visibleContent}        </g>
    </g>
    <g transform="translate(20,{textboxY})" stroke="rgb(0,0,255)">
        <line x1="30" y1="-30" x2="75" y2="-33" stroke-width="3" stroke="#000000" />
         <text x="80" y="-30" style="stroke:#000000">X </text>

        <line x1="30" y1="-30" x2="30" y2="-75" stroke-width="3" stroke="#000000" />
         <text x="25" y="-85" style="stroke:#000000">Y </text>

        <line x1="30" y1="-30" x2="58" y2="-15" stroke-width="3" stroke="#000000" />
         <text x="65" y="-5" style="stroke:#000000">Z </text>
        <!--
            <line x1="0" y1="0" x2="%(unitScale)s" y2="0" stroke-width="3" />
            <text x="0" y="20" style="stroke:#000000">1  %(uom)s </text>
        -->
    </g>
</svg>
)x";

const char* PATHTEMPLATE = "            <path d=\"%s\" />\n";

std::string servoce::getSVG(const servoce::shape& shp) 
{
	servoce::project_builder project(shp);

	auto visible_paths = servoce::getPaths(project.vcompound());
	auto hidden_paths = servoce::getPaths(project.hcompound());
	
	std::string visible_content = "";
	for (auto p : visible_paths) 
	{
		char buf[128];
		sprintf(buf, PATHTEMPLATE, p);
		visible_content.append(buf);
	}
	
	std::string hidden_content = "";
	for (auto p : hidden_paths) 
	{
		char buf[128];
		sprintf(buf, PATHTEMPLATE, p);
		hidden_content.append(buf);
	}

	/*std::string svg = nos::format(SVG_TEMPLATE,
		"width"_a = 800,
		"height"_a = 800,
		"hiddenContent"_a = hidden_content,
		"visibleContent"_a = visible_content,
		"unitScale"_a = 10,
		"xTranslate"_a = 10,
		"yTranslate"_a = 10,
		"textboxY"_a = 10,
		"strokeWidth"_a = 1,
		"uom"_a = ""
	);*/
	std::string svg = "TODO";

	return svg;
}

std::vector<std::string> servoce::getPaths(const servoce::shape& shp) 
{
	std::vector<std::string> ret;
	
	auto edges = shp.edges();
	ret.reserve(edges.size());

	for (const servoce::shape& e : edges) 
		ret.emplace_back(servoce::makeSVGedge(e.Edge()));

	return ret;
}

std::string servoce::makeSVGedge(const TopoDS_Edge& edg) 
{
	const double DISCRETIZATION_TOLERANCE = 1e-3;

	double FirstParameter;
	double LastParameter;
	std::string ret = "";
	
	BRep_Tool::Range(edg, FirstParameter, LastParameter);
	BRepAdaptor_Curve curve = BRepAdaptor_Curve(edg);

	GCPnts_QuasiUniformDeflection points(
		curve, DISCRETIZATION_TOLERANCE,
		FirstParameter, LastParameter);

	if (points.IsDone()) 
	{
		int NbPoints = points.NbPoints();

		auto p = points.Value(1);
		
		char buf[128];
		sprintf(buf, "M%f,%f ", p.X(), p.Y());
		ret.append(buf);
		
		for (int i = 2; i < NbPoints + 1; i++) 
		{
			auto p = points.Value(i);
			sprintf(buf, "M%f,%f ", p.X(), p.Y());
			ret.append(buf);
		} 
	}

	return ret;
}