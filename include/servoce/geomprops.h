#ifndef SERVOCE_GEOMPROPS_H
#define SERVOCE_GEOMPROPS_H

#include <BRepGProp.hxx>

namespace servoce 
{
	class geomprops 
	{
		 GProp_GProps _props;

	public:	
		static geomprops linear_properties(const servoce::shape& shp);
		static geomprops surface_properties(const servoce::shape& shp);
		static geomprops volume_properties(const servoce::shape& shp);

		//Returns the mass of the current system. If no density is attached to the components of the current system the returned value corresponds to : More...
		Standard_Real 	Mass () const
 
		//Returns the center of mass of the current system. If the gravitational field is uniform, it is the center of gravity. The coordinates returned for the center of mass are expressed in the absolute Cartesian coordinate system. More...
 		gp_Pnt 	CentreOfMass () const
 	
gp_Mat 	MatrixOfInertia () const
 	returns the matrix of inertia. It is a symmetrical matrix. The coefficients of the matrix are the quadratic moments of inertia. More...
 
void 	StaticMoments (Standard_Real &Ix, Standard_Real &Iy, Standard_Real &Iz) const
 	Returns Ix, Iy, Iz, the static moments of inertia of the current system; i.e. the moments of inertia about the three axes of the Cartesian coordinate system. More...
 
Standard_Real 	MomentOfInertia (const gp_Ax1 &A) const
 	computes the moment of inertia of the material system about the axis A. More...
 
GProp_PrincipalProps 	PrincipalProperties () const
 	Computes the principal properties of inertia of the current system. There is always a set of axes for which the products of inertia of a geometric system are equal to 0; i.e. the matrix of inertia of the system is diagonal. These axes are the principal axes of inertia. Their origin is coincident with the center of mass of the system. The associated moments are called the principal moments of inertia. This function computes the eigen values and the eigen vectors of the matrix of inertia of the system. Results are stored by using a presentation framework of principal properties of inertia (GProp_PrincipalProps object) which may be queried to access the value sought. More...
 
Standard_Real 	RadiusOfGyration (const gp_Ax1 &A) const
 	Returns the radius of gyration of the current system about the axis A. More...
	};
}

#endif