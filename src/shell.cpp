#include <servoce/shell.h>
#include <servoce/solid.h>
#include <servoce/face.h>

#include <TopoDS_Shell.hxx>
#include <TopoDS_Wire.hxx>

#include <BRepBuilderAPI_Sewing.hxx>
#include <BRepOffsetAPI_Sewing.hxx>
#include <ShapeFix_Shell.hxx>

#include <BRepFill.hxx>

servoce::shell_shape servoce::make_shell(const std::vector<const servoce::shape*>& vec)
{
	BRepOffsetAPI_Sewing algo;
	for (auto* a : vec)
	{
		algo.Add(a->Shape());
	}
	algo.Perform();

	if (vec.size() > 1)
	{
		ShapeFix_Shell fixer((TopoDS_Shell&)algo.SewedShape());
		fixer.Perform();
		return fixer.Shell();
	}
	else
	{
		return (TopoDS_Shell&)algo.SewedShape();
	}
}

servoce::shell_shape servoce::make_shell(const std::vector<servoce::face_shape>& vec)
{
	// FOR POLYGON

	BRepOffsetAPI_Sewing algo;
	for (auto& a : vec)
	{
		algo.Add(a.Shape());
	}
	algo.Perform();

	if (vec.size() > 1)
	{
		ShapeFix_Shell fixer((TopoDS_Shell&)algo.SewedShape());
		fixer.Perform();
		return fixer.Shell();
	}
	else
	{
		return (TopoDS_Shell&)algo.SewedShape();
	}
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


servoce::shell_shape servoce::ruled_shell(const servoce::shape& a, const servoce::shape& b)
{
	TopoDS_Shell aShell = BRepFill::Shell (a.Wire_orEdgeToWire(), b.Wire_orEdgeToWire());
	return aShell;
}