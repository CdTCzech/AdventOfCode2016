#pragma once

#include <string>
#include <sstream>

typedef __int64 int64;
typedef unsigned __int64 uint64;


template<typename T = int64>
auto toInteger(std::string number)
{
	T result;
	std::istringstream numberStream(number);
	numberStream >> result;
	return result;
}