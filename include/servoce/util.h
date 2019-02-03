#ifndef ZENCAD_UTIL_H
#define ZENCAD_UTIL_H

#include <sstream>
//#include <nos/trace.h>
#include <servoce/util/b64.h>

template<class T>
std::string string_dump(const T& obj)
{
//	TRACE();
	std::stringstream sstrm;
	obj.dump(sstrm);
	return sstrm.str();
}

template<class T>
T restore_string_dump(const std::string& in)
{
//	TRACE();
	std::stringstream sstrm(in);
	T obj;
	obj.load(sstrm);
	return obj;
}

#endif