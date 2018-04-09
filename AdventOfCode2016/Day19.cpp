#include "Day19.h"

#include "FileReader.h"

#include <algorithm>

namespace day19
{
	int64_t part1()
	{
		const auto number = std::stoll(getLine("day19.txt"));
		const auto logarithm = static_cast<int64_t>(std::log(number) / std::log(2));
		const auto power = static_cast<int64_t>(std::pow(2, logarithm));
		return (number - power) * 2 + 1;
	}

	int64_t part2()
	{
		const auto number = std::stoll(getLine("day19.txt"));
		const auto logarithm = static_cast<int64_t>(std::log(number) / std::log(3));
		const auto power = static_cast<int64_t>(std::pow(3, logarithm));
		const auto maximum = std::max(number - 2 * power, static_cast<int64_t>(0));
		return number - power + maximum;
	}
}  // namespace day19