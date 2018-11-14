#pragma once

#include "Utils.h"

#include <experimental/generator>

#include <fstream>
#include <functional>
#include <string>


template <typename T = std::string>
auto getLine(std::string filename, std::function<T(std::string&)> func = [](std::string& var) { return var; })
{
	std::ifstream infile(filename);

	if (!infile.good())
	{
		throw utils::AoCException("Reading file " + filename, __FILE__, __LINE__);
	}

	std::string line;

	getline(infile, line);
	return func(line);
}

template <typename T = std::string>
auto getLineByLine(std::string filename, std::function<T(std::string&)> func = [](std::string& var) { return var; })
{
	std::ifstream infile(filename);

	if (!infile.good())
	{
		auto ICE = "Reading file " + filename;
		throw utils::AoCException(ICE, __FILE__, __LINE__);
	}

	std::string line;

	while (getline(infile, line))
	{
		co_yield func(line);
	}
}
