#include "Day18.h"

#include "FileReader.h"

#include <algorithm>

namespace day18
{
	int64_t part1(const bool doPart2)
	{
		auto pathA = '.' + getLine("day18.txt") + '.';
		int64_t result = 0;
		const int64_t limit = (doPart2 ? 400'000 : 40);

		for (int64_t i = 0; i < limit; ++i)
		{
			std::for_each(pathA.begin(), pathA.end(), [&result](char character) { if (character == '.') ++result; });
			result -= 2;

			std::string pathB;
			pathB += '.';
			for (size_t j = 1; j < pathA.size() - 1; ++j)
			{
				if ((pathA[j - 1] == '^' && pathA[j] == '^' && pathA[j + 1] == '.') ||
					(pathA[j - 1] == '.' && pathA[j] == '^' && pathA[j + 1] == '^') ||
					(pathA[j - 1] == '^' && pathA[j] == '.' && pathA[j + 1] == '.') ||
					(pathA[j - 1] == '.' && pathA[j] == '.' && pathA[j + 1] == '^'))
				{
					pathB += '^';
				}
				else
				{
					pathB += '.';
				}
			}
			pathB += '.';
			pathA = pathB;
		}
		return result;
	}

	int64_t part1()
	{
		return part1(false);
	}

	int64_t part2()
	{
		return part1(true);
	}
}  // namespace day18