#include "Day16.h"

#include "FileReader.h"

#include <algorithm>

namespace day16
{
	std::string part1(const bool doPart2)
	{
		auto line = getLine("day16.txt");
		const size_t diskLength = (doPart2) ? 35'651'584 : 272;

		while (line.length() < diskLength)
		{
			auto lineB = line;
			std::reverse(lineB.begin(), lineB.end());
			std::for_each(lineB.begin(), lineB.end(), [](char& character) { if (character == '0') character = '1'; else character = '0'; });
			line += '0' + lineB;
		}

		line = line.substr(0, diskLength);
		auto result = line;

		while ((result.length() % 2) == 0)
		{
			result.clear();
			for (size_t i = 0; i < line.size() - 1; i += 2)
			{
				if (line[i] == line[i + 1])
				{
					result += '1';
				}
				else
				{
					result += '0';
				}
			}
			line = result;
		}

		return result;
	}

	std::string part1()
	{
		return part1(false);
	}

	std::string part2()
	{
		return part1(true);
	}
}  // namespace day16