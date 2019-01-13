#ifndef ZENCAD_UTIL_H
#define ZENCAD_UTIL_H

#include <sstream>

template<class T>
std::string string_dump(const T& obj)
{
	std::stringstream sstrm;
	obj.dump(sstrm);
	return sstrm.str();
}

template<class T>
T restore_string_dump(const std::string& in)
{
	std::stringstream sstrm(in);
	T obj;
	obj.load(sstrm);
	return obj;
}

#endif