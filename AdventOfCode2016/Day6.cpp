#include "Day6.h"

#include "FileReader.h"

#include <algorithm>

namespace day6
{
	std::string part1(const bool doPart2)
	{
		std::string result;
		std::vector<std::vector<int>> frequencyMap;
		bool firstLine = true;

		for (const auto& line : getLineByLine("day6.txt"))
		{
			if (firstLine)
			{
				for (size_t i = 0; i < line.size(); ++i)
				{
					frequencyMap.emplace_back(std::vector<int>(26, 0));
				}

				firstLine = false;
			}

			for (size_t i = 0; i < line.size(); ++i)
			{
				++frequencyMap[i][line[i] - 'a'];
			}
		}

		for (auto& characterVector : frequencyMap)
		{
			if (doPart2)
			{
				result += static_cast<char>(std::distance(characterVector.cbegin(), std::min_element(characterVector.cbegin(), characterVector.cend())) + 'a');
			}
			else
			{
				result += static_cast<char>(std::distance(characterVector.cbegin(), std::max_element(characterVector.cbegin(), characterVector.cend())) + 'a');
			}
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
}  // namespace day6