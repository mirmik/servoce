#include <servoce/boolops.h>
#include <servoce/topo.h>

#include <local/util.h>

#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <TopExp_Explorer.hxx>

#include <gxx/print.h>
#include <chrono>
#include <iostream>
#include <TopoDS.hxx>

static inline TopoDS_Shape __make_union(const TopoDS_Shape& a, const TopoDS_Shape& b) {
	return BRepAlgoAPI_Fuse(a, b).Shape();
}

static inline TopoDS_Shape __make_difference(const TopoDS_Shape& a, const TopoDS_Shape& b) {
	return BRepAlgoAPI_Cut(a, b).Shape();
}

static inline TopoDS_Shape __make_intersect(const TopoDS_Shape& a, const TopoDS_Shape& b) {
	return BRepAlgoAPI_Common(a, b).Shape();
}

servoce::solid servoce::boolops::make_union(const solid& a, const shape& b) {
	return __make_union(a.Shape(), b.Shape());
}

servoce::solid servoce::boolops::make_difference(const solid& a, const shape& b) {
	return __make_difference(a.Shape(), b.Shape());
}

servoce::solid servoce::boolops::make_intersect(const solid& a, const shape& b) {
	return __make_intersect(a.Shape(), b.Shape());
}

servoce::face servoce::boolops::make_union(const face& a, const shape& b) {
	return __make_union(a.Shape(), b.Shape());
}

servoce::face servoce::boolops::make_difference(const face& a, const shape& b) {
	return __make_difference(a.Shape(), b.Shape());
}

servoce::face servoce::boolops::make_intersect(const face& a, const shape& b) {
	return __make_intersect(a.Shape(), b.Shape());
}

servoce::wire servoce::boolops::make_union(const wire& a, const shape& b) {
	gxx::panic("StrangeOperation");
	//return __make_union(a.Shape(), b.Shape());
}

servoce::wire servoce::boolops::make_difference(const wire& a, const shape& b) {
	auto inter = __make_difference(a.Shape(), b.Shape());
	TopExp_Explorer explorer(inter, TopAbs_WIRE);
	return explorer.Current();
}

servoce::wire servoce::boolops::make_intersect(const wire& a, const shape& b) {
	auto inter = __make_intersect(a.Shape(), b.Shape());
	TopExp_Explorer explorer(inter, TopAbs_WIRE);
	return explorer.Current();
}

/*TopoDS_Shape __make_union(const TopoDS_Shape* vec, size_t size) {
	/*if (size == 1) return vec[0];
	
	int rsize = size / 2 + size % 2;
	TopoDS_Shape narr[rsize];
	
	gxx::println("here", rsize);
	for (int i = 0; i < size; ++i)
		narr[i] = vec[i] + vec[size-i-1];
	if (size % 2) 
		narr[rsize-1] = vec[size/2];
	return make_union(narr, rsize);*/
//}

servoce::solid servoce::boolops::make_union(const std::vector<const servoce::solid*>& vec) {
	if (vec.size() == 1) return *vec[0];
	
	int nrsize;
	int rsize = vec.size() / 2 + vec.size() % 2;
	TopoDS_Shape narr[rsize];

	for (int i = 0; i < vec.size() / 2; ++i) {
		narr[i] = __make_union(vec[i]->Shape(), vec[vec.size()-i-1]->Shape());
	}
	if (vec.size() % 2) {
		narr[rsize-1] = vec[vec.size()/2]->Shape();
	}
		
	while (rsize != 1) {
		nrsize = rsize/2 + rsize%2;;
		for (int i = 0; i < rsize / 2; ++i)
			narr[i] = __make_union(narr[i], narr[rsize-i-1]);
		if (rsize % 2) 
			narr[nrsize-1] = narr[rsize/2];
		rsize = nrsize; 
	}

	return narr[0];
}

servoce::face servoce::boolops::make_union(const std::vector<const servoce::face*>& vec) {
	if (vec.size() == 1) return *vec[0];
	
	int nrsize;
	int rsize = vec.size() / 2 + vec.size() % 2;
	TopoDS_Shape narr[rsize];

	for (int i = 0; i < vec.size() / 2; ++i) {
		narr[i] = __make_union(vec[i]->Shape(), vec[vec.size()-i-1]->Shape());
	}
	if (vec.size() % 2) {
		narr[rsize-1] = vec[vec.size()/2]->Shape();
	}
		
	while (rsize != 1) {
		nrsize = rsize/2 + rsize%2;;
		for (int i = 0; i < rsize / 2; ++i)
			narr[i] = __make_union(narr[i], narr[rsize-i-1]);
		if (rsize % 2) 
			narr[nrsize-1] = narr[rsize/2];
		rsize = nrsize; 
	}

	return narr[0];
}

servoce::solid servoce::boolops::make_difference(const std::vector<const servoce::solid*>& vec) {
	TopoDS_Shape ret = vec[0]->Shape();
	for (int i = 1; i < vec.size(); ++i) {
		ret = __make_difference(ret, vec[i]->Shape());
	}
	return ret;
}


servoce::face servoce::boolops::make_difference(const std::vector<const servoce::face*>& vec) {
	TopoDS_Shape ret = vec[0]->Shape();
	for (int i = 1; i < vec.size(); ++i) {
		ret = __make_difference(ret, vec[i]->Shape());
	}
	return ret;
}

servoce::solid servoce::boolops::make_intersect(const std::vector<const servoce::solid*>& vec) {
	TopoDS_Shape ret = vec[0]->Shape();
	for (int i = 1; i < vec.size(); ++i) {
		ret = __make_intersect(ret, vec[i]->Shape());
	}
	return ret;
}

servoce::face servoce::boolops::make_intersect(const std::vector<const servoce::face*>& vec) {
	TopoDS_Shape ret = vec[0]->Shape();
	for (int i = 1; i < vec.size(); ++i) {
		ret = __make_intersect(ret, vec[i]->Shape());
	}
	return ret;
}