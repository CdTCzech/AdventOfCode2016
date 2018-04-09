#include "Day9.h"

#include "FileReader.h"

namespace day9
{
	int64_t part1()
	{
		std::string result;
		const auto& line = getLine("day9.txt");
		size_t index = 0;

		while (index < line.size())
		{
			if (line[index] == '(')
			{
				std::string buffer;

				++index;
				while (line[index] >= '0' && line[index] <= '9')
				{
					buffer += line[index];
					++index;
				}
				const auto characters = std::stoll(buffer);
				buffer.clear();

				++index;
				while (line[index] >= '0' && line[index] <= '9')
				{
					buffer += line[index];
					++index;
				}
				const auto repeats = std::stoll(buffer);
				buffer.clear();

				for (int64_t i = 0; i < characters; ++i)
				{
					++index;
					buffer += line[index];
				}

				for (int64_t i = 0; i < repeats; ++i)
				{
					result += buffer;
				}
			}
			else
			{
				result += line[index];
			}
			++index;
		}

		return result.size();
	}

	int64_t part2()
	{
		int64_t result = 0;
		size_t index = 0;

		const auto& line = getLine("day9.txt");
		std::vector<int64_t> weights;
		weights.resize(line.size());
		std::fill(weights.begin(), weights.end(), 1);

		while (index < line.size())
		{
			if (line[index] == '(')
			{
				std::string buffer;

				++index;
				while (line[index] >= '0' && line[index] <= '9')
				{
					buffer += line[index];
					++index;
				}
				const auto characters = std::stoll(buffer);
				buffer.clear();

				++index;
				while (line[index] >= '0' && line[index] <= '9')
				{
					buffer += line[index];
					++index;
				}
				const auto repeats = std::stoll(buffer);
				buffer.clear();

				for (int64_t i = 0; i < characters; ++i)
				{
					weights[index + i + 1] *= repeats;
				}
			}
			else
			{
				result += weights[index];
			}
			++index;
		}

		return result;
	}
}  // namespace day9