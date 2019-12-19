#include <servoce/geomprops.h>
#include <servoce/geombase.h>
#include <BRepGProp.hxx>

servoce::geomprops servoce::geomprops::linear_properties(const servoce::shape& shp, double density)
{
	GProp_GProps scaled;
	GProp_GProps gener;
	BRepGProp::LinearProperties(shp.Shape(), gener);
	scaled.Add(gener);
	return scaled;
}

servoce::geomprops servoce::geomprops::surface_properties(const servoce::shape& shp, double density)
{
	GProp_GProps scaled;
	GProp_GProps gener;
	BRepGProp::SurfaceProperties(shp.Shape(), gener);
	scaled.Add(gener);
	return scaled;
}

servoce::geomprops servoce::geomprops::volume_properties(const servoce::shape& shp, double density)
{
	GProp_GProps scaled;
	GProp_GProps gener;
	BRepGProp::VolumeProperties(shp.Shape(), gener);
	scaled.Add(gener);
	return scaled;
}

double
servoce::geomprops::mass() const
{
	return Mass();
}

servoce::matrix33
servoce::geomprops::matrix_of_inertia() const
{
	return MatrixOfInertia();
}

std::tuple<double, double, double>
servoce::geomprops::static_moments() const
{
	double x,y,z;
	StaticMoments(x,y,z);
	return {x,y,z};
}

double
servoce::geomprops::moment_of_inertia(
    const servoce::vector3& axis) const
{
	throw std::runtime_error("NotImplemented");
	return 0;
}

double
servoce::geomprops::radius_of_gyration(
    const servoce::vector3& axis) const
{
	throw std::runtime_error("NotImplemented");
	return 0;
}