#include "Day23.h"

#include "FileReader.h"

#include <array>
#include <iterator>
#include <sstream>

namespace day23
{
	int64_t part1(const bool doPart2)
	{
		std::vector<std::vector<std::string>> codeLines;
		for (const auto& line : getLineByLine("day23.txt"))
		{
			std::istringstream iss(line);
			const std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };
			codeLines.push_back(tokens);
		}

		uint64_t index = 0;
		std::array<int64_t, 4> result = { 7, 0, 0, 0 };
		if (doPart2)
		{
			result[0] = 12;
		}

		while (index < codeLines.size())
		{
			if (codeLines[index][0] == "cpy")
			{
				if (codeLines[index][1][0] >= 'a' && codeLines[index][1][0] <= 'd')
				{
					result[codeLines[index][2][0] - 'a'] = result[codeLines[index][1][0] - 'a'];
				}
				else if (codeLines[index][2][0] >= 'a' && codeLines[index][2][0] <= 'd')
				{
					const auto number = std::stoll(codeLines[index][1]);
					result[codeLines[index][2][0] - 'a'] = number;
				}
			}
			else if (codeLines[index][0] == "inc")
			{
				if (codeLines[index][1][0] >= 'a' && codeLines[index][1][0] <= 'd')
				{
					++result[codeLines[index][1][0] - 'a'];
				}
			}
			else if (codeLines[index][0] == "dec")
			{
				if (codeLines[index][1][0] >= 'a' && codeLines[index][1][0] <= 'd')
				{
					--result[codeLines[index][1][0] - 'a'];
				}
			}
			else if (codeLines[index][0] == "jnz")
			{
				int64_t number1;
				if (codeLines[index][1][0] >= 'a' && codeLines[index][1][0] <= 'd')
				{
					number1 = result[codeLines[index][1][0] - 'a'];
				}
				else
				{
					number1 = std::stoll(codeLines[index][1]);
				}

				int64_t number2;
				if (codeLines[index][2][0] >= 'a' && codeLines[index][2][0] <= 'd')
				{
					number2 = result[codeLines[index][2][0] - 'a'];
				}
				else
				{
					number2 = std::stoll(codeLines[index][2]);
				}

				if (number1)
				{
					index += number2;
					--index;
				}

			}
			else if (codeLines[index][0] == "tgl")
			{
				int64_t number;

				if (codeLines[index][1][0] >= 'a' && codeLines[index][1][0] <= 'd')
				{
					number = result[codeLines[index][1][0] - 'a'];
				}
				else
				{
					number = std::stoll(codeLines[index][1]);
				}

				const auto newIndex = index + number;
				if (newIndex < codeLines.size())
				{
					if (codeLines[newIndex].size() == 2)
					{
						codeLines[newIndex][0] = (codeLines[newIndex][0] == "inc") ? "dec" : "inc";
					}
					else if (codeLines[index + number].size() == 3)
					{
						codeLines[newIndex][0] = (codeLines[newIndex][0] == "jnz") ? "cpy" : "jnz";
					}
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
}  // namespace day23