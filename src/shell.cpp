#include <servoce/shell.h>
#include <servoce/solid.h>
#include <servoce/face.h>

#include <BRepBuilderAPI_Sewing.hxx>
#include <BRepOffsetAPI_Sewing.hxx>

servoce::shell_shape servoce::make_shell(const std::vector<const servoce::shape*>& vec)
{
	BRepOffsetAPI_Sewing algo(0.1);

	for (auto* a : vec)
	{
		algo.Add((TopoDS_Shape&)a->Face());
	}

	algo.Perform();

	//ShapeFix_Shell fixer((TopoDS_Shell&)algo.SewedShape());
	//return fixer.Shell();
	return (TopoDS_Shell&) algo.SewedShape();
}

servoce::shell_shape servoce::make_shell(const std::vector<servoce::face_shape>& vec)
{
	BRepOffsetAPI_Sewing algo(0.1);

	for (auto& a : vec)
	{
		algo.Add((TopoDS_Shape&)a.Face());
	}

	algo.Perform();

	//ShapeFix_Shell fixer((TopoDS_Shell&)algo.SewedShape());
	//return fixer.Shell();
	return (TopoDS_Shell&) algo.SewedShape();
}

servoce::solid_shape servoce::shell_shape::fill() 
{
	return servoce::make_solid(*this);
}


servoce::shell_shape 
servoce::polyhedron_shell(const std::vector<servoce::point3>& pnts, const std::vector<std::vector<int>>& faces_no) 
{
	std::vector<servoce::face_shape> faces;

	for (const std::vector<int>& nums : faces_no) 
	{
		std::vector<servoce::point3> fpnts;

		for (int i : nums) 
			fpnts.push_back(pnts[i]);

		faces.push_back(servoce::polygon(fpnts));
	}

	return servoce::make_shell(faces);
}