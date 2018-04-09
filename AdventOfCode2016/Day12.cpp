#include "Day12.h"

#include "FileReader.h"

#include <array>
#include <iterator>
#include <sstream>

namespace day12
{
	int64_t part1(const bool doPart2)
	{
		std::vector<std::vector<std::string>> codeLines;
		for (const auto& line : getLineByLine("day12.txt"))
		{
			std::istringstream iss(line);
			const std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };
			codeLines.push_back(tokens);
		}

		uint64_t index = 0;
		std::array<int64_t, 4> result = { 0, 0, 0, 0 };
		if (doPart2)
		{
			result[2] = 1;
		}

		while (index < codeLines.size())
		{
			if (codeLines[index][0] == "cpy")
			{
				if (codeLines[index][1][0] >= 'a' && codeLines[index][1][0] <= 'd')
				{
					result[codeLines[index][2][0] - 'a'] = result[codeLines[index][1][0] - 'a'];
				}
				else
				{
					const auto number = std::stoll(codeLines[index][1]);
					result[codeLines[index][2][0] - 'a'] = number;
				}
			}
			else if (codeLines[index][0] == "inc")
			{
				++result[codeLines[index][1][0] - 'a'];
			}
			else if (codeLines[index][0] == "dec")
			{
				--result[codeLines[index][1][0] - 'a'];
			}
			else if (codeLines[index][0] == "jnz")
			{
				int64_t number1;
				const auto number2 = std::stoll(codeLines[index][2]);

				if (codeLines[index][1][0] >= 'a' && codeLines[index][1][0] <= 'd')
				{
					number1 = result[codeLines[index][1][0] - 'a'];
				}
				else
				{
					number1 = std::stoll(codeLines[index][1]);
				}

				if (number1)
				{
					index += number2;
					--index;
				}

			}
			++index;
		}

		return result[0];
	}

	int64_t part1()
	{
		return part1(false);
	}

	int64_t part2()
	{
		return part1(true);
	}
}  // namespace day12