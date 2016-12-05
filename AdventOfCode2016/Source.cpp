#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <locale>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <vector>

#include "FileReader.h"

typedef __int64 int64;
typedef unsigned __int64 uint64;


namespace day1
{
	void part1(bool doPart2 = false)
	{
		const auto& line = getLine("day1.txt");
		std::istringstream iss(line);
		std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };

		int64 result = 0;
		int64 x = 0;
		int64 y = 0;
		uint64 facing = 0;

		std::set<std::pair<int64, int64>> locations;

		for (auto& token : tokens)
		{
			std::string numberString;
			for (size_t i = 1; i < token.size() - 1; ++i)
			{
				numberString += token[i];
			}

			std::istringstream iss(numberString);
			int64 number;
			iss >> number;

			auto turnRight = (token[0] == 'R');

			for (int64 i = 0; i < number; ++i)
			{
				std::pair<int64, int64> location(x, y);
				if (doPart2 && locations.find(location) != locations.cend())
				{
					std::cout << abs(x + y) << std::endl;
					return;
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
			std::cout << abs(x + y) << std::endl;
		}
		else
		{
			std::cout << "ERROR" << std::endl;
		}
	}

	void part2()
	{
		part1(true);
	}
}

namespace day2
{
	void part1()
	{
		int64 result = 0;
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
		std::cout << result << std::endl;
	}

	void part2()
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
		std::cout << result << std::endl;
	}
}

int main(int argc, char** argv)
{
	std::cout << "Day 1 Part 1 (expected 246): ";			day1::part1();
	std::cout << "Day 1 Part 2 (expected 124): ";			day1::part2();
	std::cout << "Day 2 Part 1 (expected 24862): ";			day2::part1();
	std::cout << "Day 2 Part 1 (expected 46C91): ";			day2::part2();

	system("pause");
	return 0;
}
