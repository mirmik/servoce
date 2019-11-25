#include <servoce/boolops.h>
#include <servoce/topo.h>

#include <local/util.h>

#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <TopExp_Explorer.hxx>

#include <chrono>
#include <iostream>
#include <TopoDS.hxx>

#include <servoce/face.h>

static inline TopoDS_Shape __make_union(const TopoDS_Shape& a, const TopoDS_Shape& b)
{
	BRepAlgoAPI_Fuse algo(a, b);//.Shape();
	algo.Build();
	if ( ! algo.IsDone() ) {
		printf("warn: union algotithm failed\n");
		algo.GetReport()->Dump(std::cout);
		//printf("error status: %d \n", algo.ErrorStatus());
		//printf("warning status: %d \n", algo.WarningStatus());
	}
	return algo.Shape();
}

static inline TopoDS_Shape __make_difference(const TopoDS_Shape& a, const TopoDS_Shape& b)
{
	BRepAlgoAPI_Cut algo(a, b);//.Shape();
	algo.Build();
	if ( ! algo.IsDone() ) {
		printf("warn: difference algotithm failed\n");
		algo.GetReport()->Dump(std::cout);
		//printf("error status: %d \n", algo.ErrorStatus());
		//printf("warning status: %d \n", algo.WarningStatus());
	}
	return algo.Shape();
}

static inline TopoDS_Shape __make_intersect(const TopoDS_Shape& a, const TopoDS_Shape& b)
{
	BRepAlgoAPI_Common algo(a, b);//.Shape();
	algo.Build();
	if ( ! algo.IsDone() ) {
		printf("warn: intersect algotithm failed\n");
		algo.GetReport()->Dump(std::cout);
		//printf("error status: %d \n", algo.ErrorStatus());
		//printf("warning status: %d \n", algo.WarningStatus());
	}
	return algo.Shape();
}

servoce::shape servoce::make_union(const shape& a, const shape& b)
{
	return __make_union(a.Shape(), b.Shape());
}

servoce::shape servoce::make_difference(const shape& a, const shape& b)
{
	return __make_difference(a.Shape(), b.Shape());
}

servoce::shape servoce::make_intersect(const shape& a, const shape& b)
{
	return __make_intersect(a.Shape(), b.Shape());
}

servoce::shape servoce::make_union(const std::vector<const servoce::shape*>& vec)
{
	if (vec.size() == 1) return *vec[0];

	unsigned int nrsize;
	unsigned int rsize = vec.size() / 2 + vec.size() % 2;
	//TopoDS_Shape narr[rsize];
	TopoDS_Shape* narr = (TopoDS_Shape*) alloca(sizeof(TopoDS_Shape) * rsize);

	for (unsigned int i = 0; i < rsize; ++i)
	{
		new (&narr[i]) TopoDS_Shape();
	}

	for (unsigned int i = 0; i < vec.size() / 2; ++i)
	{
		narr[i] = __make_union(vec[i]->Shape(), vec[vec.size() - i - 1]->Shape());
	}

	if (vec.size() % 2)
	{
		narr[rsize - 1] = vec[vec.size() / 2]->Shape();
	}

	while (rsize != 1)
	{
		nrsize = rsize / 2 + rsize % 2;;

		for (unsigned int i = 0; i < rsize / 2; ++i)
			narr[i] = __make_union(narr[i], narr[rsize - i - 1]);

		if (rsize % 2)
			narr[nrsize - 1] = narr[rsize / 2];

		rsize = nrsize;
	}

	return narr[0];
}

servoce::shape servoce::make_difference(const std::vector<const servoce::shape*>& vec)
{
	TopoDS_Shape ret = vec[0]->Shape();

	for (unsigned int i = 1; i < vec.size(); ++i)
	{
		ret = __make_difference(ret, vec[i]->Shape());
	}

	return ret;
}

servoce::shape servoce::make_intersect(const std::vector<const servoce::shape*>& vec)
{
	TopoDS_Shape ret = vec[0]->Shape();

	for (unsigned int i = 1; i < vec.size(); ++i)
	{
		ret = __make_intersect(ret, vec[i]->Shape());
	}

	return ret;
}

///////////////////////////SECTION ALGO///////////////////////////////////////
static inline TopoDS_Shape __make_section(const TopoDS_Shape& a, 
	const TopoDS_Shape& b)
{
	BRepAlgoAPI_Section algo(a, b);//.Shape();
	algo.Build();
	if ( ! algo.IsDone() ) {
		printf("warn: section algotithm failed\n");
	}
	return algo.Shape();
}

servoce::shape servoce::make_section(const servoce::shape& a, 
	const servoce::shape& b)
{
	return __make_section(a.Shape(), b.Shape());
}

servoce::shape servoce::make_section(const servoce::shape& a)
{
	return make_section(a, servoce::infplane());
}
/////////////////////////////////////////////////////////////////////////////
