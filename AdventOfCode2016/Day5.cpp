#include "Day5.h"

#include "FileReader.h"

#include "Libraries/md5.h"

namespace day5
{
	std::string part1()
	{
		const auto& line = getLine("day5.txt");
		std::string result;

		auto counter = 0;
		for (unsigned int number = 0; number < 1'000'000'000; ++number)
		{
			auto hash = md5(line + std::to_string(number));
			if (hash.substr(0, 5) == "00000")
			{
				result += hash[5];
				if (++counter == 8)
				{
					return result;
				}
			}
		}
		return result;
	}

	std::string part2()
	{
		const auto line = getLine("day5.txt");
		std::vector<bool> isInserted{ false, false, false, false, false, false , false, false };
		std::string result = "########";

		auto counter = 0;
		for (unsigned int number = 0; number < 4'000'000'000; ++number)
		{
			auto hash = md5(line + std::to_string(number));
			if (hash.substr(0, 5) == "00000")
			{
				const auto index = hash[5] - '0';
				if (index > 7) continue;

				if (!isInserted[index])
				{
					result[index] = hash[6];
					isInserted[index] = true;

					if (++counter == 8)
					{
						return result;
					}
				}
			}
		}
		return result;
	}
}  // namespace day5