#include <servoce/geomprops.h>
#include <servoce/geombase.h>
#include <BRepGProp.hxx>
#include <GProp_PrincipalProps.hxx>
#include <gp_Ax3.hxx>

servoce::geomprops servoce::geomprops::linear_properties(const servoce::shape& shp, double density)
{
	GProp_GProps scaled;
	GProp_GProps gener;
	BRepGProp::LinearProperties(shp.Shape(), gener);
	scaled.Add(gener, density);
	return scaled;
}

servoce::geomprops servoce::geomprops::surface_properties(const servoce::shape& shp, double density)
{
	GProp_GProps scaled;
	GProp_GProps gener;
	BRepGProp::SurfaceProperties(shp.Shape(), gener);
	scaled.Add(gener, density);
	return scaled;
}

servoce::geomprops servoce::geomprops::volume_properties(const servoce::shape& shp, double density)
{
	GProp_GProps scaled;
	GProp_GProps gener;
	BRepGProp::VolumeProperties(shp.Shape(), gener);
	scaled.Add(gener, density);
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
	return std::make_tuple(x,y,z);
}

double
servoce::geomprops::moment_of_inertia(
    const servoce::vector3& axis) const
{
	(void)axis;
	throw std::runtime_error("NotImplemented");
	return 0;
}

double
servoce::geomprops::radius_of_gyration(
    const servoce::vector3& axis) const
{
	(void)axis;
	throw std::runtime_error("NotImplemented");
	return 0;
}


std::tuple<servoce::vector3, servoce::vector3, servoce::vector3> 
servoce::geomprops::principal_inertia_axes() const
{
	GProp_PrincipalProps pprops = PrincipalProperties(); 
	servoce::vector3 a = pprops.FirstAxisOfInertia(); 
	servoce::vector3 b = pprops.SecondAxisOfInertia(); 
	servoce::vector3 c = pprops.ThirdAxisOfInertia(); 

	return {a,b,c};
}


std::tuple<double, double, double> 
servoce::geomprops::principal_inertia_moments() const
{
	double Ixx, Iyy, Izz;
	GProp_PrincipalProps pprops = PrincipalProperties(); 
	pprops.Moments(Ixx, Iyy, Izz);
	return {Ixx, Iyy, Izz};
}

servoce::transformation servoce::geomprops::inertia_frame() const 
{
	/// Работает???

	gp_Trsf trsf;

	auto axes = principal_inertia_axes();
	auto cm = cmradius();

	auto ax3 = gp_Ax3(servoce::point3(cm).Pnt(), std::get<1>(axes).Dir(), std::get<2>(axes).Dir());
	
	trsf.SetTransformation(ax3);
	return trsf;
}