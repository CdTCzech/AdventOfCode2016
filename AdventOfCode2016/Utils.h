#pragma once

#include <string>
#include <sstream>


template<typename T = int64_t>
auto toInteger(std::string number)
{
	T result;
	std::istringstream numberStream(number);
	numberStream >> result;
	return result;
}