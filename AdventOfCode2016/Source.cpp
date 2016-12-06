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

#include "Libraries\md5.h"
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

			std::istringstream numberStream(numberString);
			int64 number;
			numberStream >> number;

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

namespace day3
{
	void part1()
	{
		uint64 result = 0;

		for (const auto& line : getLineByLine("day3.txt"))
		{
			std::istringstream iss(line);
			int64 x, y, z;
			iss >> x >> y >> z;

			if (x + y > z && x + z > y && y + z > x) ++result;
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		uint64 result = 0;
		int64 x1, x2, x3;
		int64 y1, y2, y3;
		int64 z1, z2, z3;

		int lineIndex = 1;
		for (const auto& line : getLineByLine("day3.txt"))
		{
			std::istringstream iss(line);
			if (lineIndex == 1) iss >> x1 >> x2 >> x3;
			if (lineIndex == 2) iss >> y1 >> y2 >> y3;
			if (lineIndex == 3) iss >> z1 >> z2 >> z3;

			if (lineIndex == 3)
			{
				if (x1 + y1 > z1 && x1 + z1 > y1 && y1 + z1 > x1) ++result;
				if (x2 + y2 > z2 && x2 + z2 > y2 && y2 + z2 > x2) ++result;
				if (x3 + y3 > z3 && x3 + z3 > y3 && y3 + z3 > x3) ++result;
				lineIndex = 0;
			}

			++lineIndex;
		}

		std::cout << result << std::endl;
	}
}

namespace day4
{
	void part1(bool doPart2 = false)
	{
		int64 result = 0;

		for (const auto& line : getLineByLine("day4.txt"))
		{
			std::map<char, int> charCount;

			std::vector<std::string> tokens;
			std::size_t start = 0, end = 0;
			while ((end = line.find('-', start)) != std::string::npos) {
				if (end != start) {
					tokens.push_back({ line.substr(start, end - start) });
				}
				start = end + 1;
			}
			if (end != start) {
				tokens.push_back({ line.substr(start) });
			}

			for (size_t i = 0; i < tokens.size() - 1; ++i)
			{
				for (size_t j = 0; j < tokens[i].size(); ++j)
				{
					auto index = charCount.find(tokens[i][j]);
					if (index != charCount.end()) ++charCount[tokens[i][j]];
					else charCount.insert({ tokens[i][j], 1 });
				}
			}

			std::string fiveMostCommon;
			std::vector<std::pair<char, int>> charCountSorted(charCount.begin(), charCount.end());
			std::stable_sort(charCountSorted.begin(), charCountSorted.end(), [=](const std::pair<char, int>& a, const std::pair<char, int>& b) { return a.second > b.second; });

			for (size_t i = 0; i < 5; ++i)
			{
				fiveMostCommon += charCountSorted[i].first;
			}

			if (fiveMostCommon == tokens.back().substr(tokens.back().size() - 6, 5))
			{
				std::istringstream iss(tokens.back().substr(0, tokens.back().size() - 7));
				int number;
				iss >> number;

				if (doPart2)
				{
					for (size_t i = 0; i < tokens.size() - 1; ++i)
					{
						std::string word;
						for (size_t j = 0; j < tokens[i].size(); ++j)
						{
							word += (((tokens[i][j] - 'a') + number) % 26) + 'a';
						}

						if (word == "northpole")
						{
							std::cout << number << std::endl;
							return;
						}
					}
				}
				else
				{
					result += number;
				}
			}
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		part1(true);
	}
}

namespace day5
{
	void part1()
	{
		const auto& line = getLine("day5.txt");
		int counter = 0;
		for (unsigned int number = 0; number < 1'000'000'000; ++number)
		{
			auto hash = md5(line + std::to_string(number));
			if (hash.substr(0, 5) == "00000")
			{
				std::cout << hash[5];
				if (++counter == 8)
				{
					std::cout << std::endl;
					return;
				}
			}
		}
	}

	void part2()
	{
		const auto line = getLine("day5.txt");
		std::vector<bool> isInserted{ false, false, false, false, false, false , false, false };
		std::string result = "########";

		int counter = 0;
		for (unsigned int number = 0; number < 4'000'000'000; ++number)
		{
			auto test = line + std::to_string(number);
			auto hash = md5(test);
			if (hash.substr(0, 5) == "00000")
			{
				auto index = hash[5] - '0';
				if (index > 7) continue;

				if (!isInserted[index])
				{
					result[index] = hash[6];
					isInserted[index] = true;

					if (++counter == 8)
					{
						std::cout << result << std::endl;
						return;
					}
				}
			}
		}
	}
}

namespace day6
{
	void part1(bool doPart2 = false)
	{
		std::vector<std::vector<int>> frequencyMap;
		bool firstLine = true;

		for (const auto& line : getLineByLine("day6.txt"))
		{
			if (firstLine)
			{
				for (const auto& character : line)
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
				std::cout << static_cast<char>(std::distance(characterVector.cbegin(), std::min_element(characterVector.cbegin(), characterVector.cend())) + 'a');
			}
			else
			{
				std::cout << static_cast<char>(std::distance(characterVector.cbegin(), std::max_element(characterVector.cbegin(), characterVector.cend())) + 'a');
			}
		}

		std::cout << std::endl;
	}

	void part2()
	{
		part1(true);
	}
}

int main(int argc, char** argv)
{
	std::cout << "Day 1 Part 1 (expected 246): ";			day1::part1();
	std::cout << "Day 1 Part 2 (expected 124): ";			day1::part2();
	std::cout << "Day 2 Part 1 (expected 24862): ";			day2::part1();
	std::cout << "Day 2 Part 2 (expected 46C91): ";			day2::part2();
	std::cout << "Day 3 Part 1 (expected 993): ";			day3::part1();
	std::cout << "Day 3 Part 2 (expected 1849): ";			day3::part2();
	std::cout << "Day 4 Part 1 (expected 409147): ";		day4::part1();
	std::cout << "Day 4 Part 2 (expected 991): ";			day4::part2();
	std::cout << "Day 5 Part 1 (expected f97c354d): ";		day5::part1();
	std::cout << "Day 5 Part 2 (expected 863dde27): ";		day5::part2();
	std::cout << "Day 6 Part 1 (expected bjosfbce): ";		day6::part1();
	std::cout << "Day 6 Part 2 (expected veqfxzfx): ";		day6::part2();

	system("pause");
	return 0;
}
