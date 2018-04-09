#include "Day2.h"

#include "FileReader.h"

namespace day2
{
	int64_t part1()
	{
		int64_t result = 0;
		int position = 5;

		for (const auto& line : getLineByLine("day2.txt"))
		{
			for (const auto& direction : line)
			{
				if (direction == 'U' && position != 1 && position != 2 && position != 3) position -= 3;
				if (direction == 'D' && position != 7 && position != 8 && position != 9) position += 3;
				if (direction == 'L' && position != 1 && position != 4 && position != 7) position -= 1;
				if (direction == 'R' && position != 3 && position != 6 && position != 9) position += 1;
			}

			result *= 10;
			result += position;
		}
		return result;
	}

	std::string part2()
	{
		std::string result;
		int position = 5;

		for (const auto& line : getLineByLine("day2.txt"))
		{
			for (const auto& direction : line)
			{
				if (direction == 'U' && position != 1 && position != 2 && position != 4 && position != 5 && position != 9)
				{
					if (position == 3 || position == 13) position -= 2;
					else position -= 4;
				}
				if (direction == 'D' && position != 5 && position != 9 && position != 10 && position != 12 && position != 13)
				{
					if (position == 1 || position == 11) position += 2;
					else position += 4;
				}
				if (direction == 'L' && position != 1 && position != 2 && position != 5 && position != 10 && position != 13) position -= 1;
				if (direction == 'R' && position != 1 && position != 4 && position != 9 && position != 12 && position != 13) position += 1;
			}

			if (position > 9)
			{
				result += ('A' - 10) + position;
			}
			else
			{
				result += '0' + position;
			}
		}
		return result;
	}
}  // namespace day2