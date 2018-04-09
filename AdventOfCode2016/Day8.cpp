#include "Day8.h"

#include "FileReader.h"

#include <array>
#include <sstream>

namespace day8
{
	std::array<std::array<bool, 50>, 6> compute()
	{
		std::array<std::array<bool, 50>, 6> display{};
		for (auto& row : display)
		{
			for (auto& column : row)
			{
				column = false;
			}
		}

		for (const auto& line : getLineByLine("day8.txt"))
		{
			std::istringstream iss(line);
			std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };
			if (tokens[0] == "rect")
			{
				std::string numberBuffer;
				uint64_t wide = 0;
				for (const auto& character : tokens[1])
				{
					if (character == 'x')
					{
						wide = std::stoull(numberBuffer);
						numberBuffer.clear();
						continue;
					}

					numberBuffer += character;
				}
				const auto tall = std::stoull(numberBuffer);

				for (uint64_t row = 0; row < tall; ++row)
				{
					for (uint64_t column = 0; column < wide; ++column)
					{
						display[row][column] = true;
					}
				}
			}
			else
			{
				std::string numberBuffer;

				for (const auto& character : tokens[2])
				{
					if (character == 'x' || character == 'y' || character == '=') continue;
					numberBuffer += character;
				}
				const auto xy = std::stoull(numberBuffer);
				numberBuffer.clear();

				for (const auto& character : tokens[4])
				{
					numberBuffer += character;
				}
				const auto by = std::stoull(numberBuffer);

				if (tokens[1] == "row")
				{
					for (uint64_t i = 0; i < by; ++i)
					{
						const auto buffer = display[xy].back();
						for (auto j = display[xy].size() - 1; j > 0; --j)
						{
							display[xy][j] = display[xy][j - 1];
						}
						display[xy][0] = buffer;
					}
				}
				else
				{
					for (uint64_t i = 0; i < by; ++i)
					{
						const auto buffer = display.back()[xy];
						for (auto j = display.size() - 1; j > 0; --j)
						{
							display[j][xy] = display[j - 1][xy];
						}
						display[0][xy] = buffer;
					}
				}
			}
		}
		return display;
	}

	int64_t part1()
	{
		int64_t result = 0;
		const auto display = compute();
		for (auto& row : display)
		{
			for (auto& column : row)
			{
				if (column) ++result;
			}
		}
		return result;
	}

	std::string part2()
	{
		std::string result;
		const auto display = compute();
		result += '\n';
		for (auto& row : display)
		{
			for (auto& column : row)
			{
				if (column)
				{
					result += "#";
				}
				else
				{
					result += " ";
				}
			}
			result += "x\n";
		}
		return result;
	}
}  // namespace day8