#include <servoce/geomprops.h>
#include <BRepGProp.hxx>

servoce::geomprops servoce::geomprops::linear_properties(const servoce::shape& shp, double density)
{
	//return BRepGProp::LinearProperties(shp, *this);
}

servoce::geomprops servoce::geomprops::surface_properties(const servoce::shape& shp, double density)
{
	//return BRepGProp::SurfaceProperties(shp, *this);
}

servoce::geomprops servoce::geomprops::volume_properties(const servoce::shape& shp, double density)
{
	GProp_GProps scaled;
	GProp_GProps gener;
	BRepGProp::VolumeProperties(shp.Shape(), gener);
	scaled.Add(gener);
	return scaled;
}