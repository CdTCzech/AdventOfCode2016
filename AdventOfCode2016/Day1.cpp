#include "Day1.h"

#include "FileReader.h"

#include <iterator>
#include <set>
#include <sstream>

namespace day1
{
	int64_t part1(const bool doPart2)
	{
		const auto& line = getLine("day1.txt");
		std::istringstream iss(line);
		std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };
		tokens.back() += ',';

		int64_t x = 0;
		int64_t y = 0;
		uint64_t facing = 0;

		std::set<std::pair<int64_t, int64_t>> locations;

		for (auto& token : tokens)
		{
			std::string numberString;
			for (size_t i = 1; i < token.size() - 1; ++i)
			{
				numberString += token[i];
			}

			const auto number = std::stoll(numberString);
			const auto turnRight = (token[0] == 'R');

			for (int64_t i = 0; i < number; ++i)
			{
				const std::pair<int64_t, int64_t> location(x, y);
				if (doPart2 && locations.find(location) != locations.cend())
				{
					return abs(x + y);
				}
				locations.insert(location);

				if (facing == 0)
				{
					x += (turnRight) ? 1 : -1;
				}
				else if (facing == 1)
				{
					y += (turnRight) ? 1 : -1;
				}
				else if (facing == 2)
				{
					x += (turnRight) ? -1 : 1;
				}
				else if (facing == 3)
				{
					y += (turnRight) ? -1 : 1;
				}
			}

			if (facing == 0)
			{
				facing = (turnRight) ? 3 : 1;
			}
			else if (facing == 1)
			{
				facing = (turnRight) ? 0 : 2;
			}
			else if (facing == 2)
			{
				facing = (turnRight) ? 1 : 3;
			}
			else if (facing == 3)
			{
				facing = (turnRight) ? 2 : 0;
			}
		}

		if (!doPart2)
		{
			return abs(x + y);
		}

		return 0;
	}

	int64_t part1()
	{
		return part1(false);
	}

	int64_t part2()
	{
		return part1(true);
	}
}  // namespace day1