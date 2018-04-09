#include "Day3.h"

#include "FileReader.h"

#include <sstream>

namespace day3
{
	int64_t part1()
	{
		int64_t result = 0;

		for (const auto& line : getLineByLine("day3.txt"))
		{
			std::istringstream iss(line);
			int64_t x, y, z;
			iss >> x >> y >> z;

			if (x + y > z && x + z > y && y + z > x) ++result;
		}

		return result;
	}

	int64_t part2()
	{
		int64_t result = 0;
		int64_t x1, x2, x3;
		int64_t y1, y2, y3;
		int64_t z1, z2, z3;

		int lineIndex = 1;
		for (const auto& line : getLineByLine("day3.txt"))
		{
			std::istringstream iss(line);
			if (lineIndex == 1) iss >> x1 >> x2 >> x3;
			if (lineIndex == 2) iss >> y1 >> y2 >> y3;
			if (lineIndex == 3) iss >> z1 >> z2 >> z3;

			if (lineIndex == 3)
			{
				if (x1 + y1 > z1 && x1 + z1 > y1 && y1 + z1 > x1) ++result;
				if (x2 + y2 > z2 && x2 + z2 > y2 && y2 + z2 > x2) ++result;
				if (x3 + y3 > z3 && x3 + z3 > y3 && y3 + z3 > x3) ++result;
				lineIndex = 0;
			}

			++lineIndex;
		}

		return result;
	}
}  // namespace day3