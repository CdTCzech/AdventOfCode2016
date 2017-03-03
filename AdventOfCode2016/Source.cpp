#include <algorithm>
#include <array>
#include <bitset> 
#include <iostream>
#include <iterator>
#include <locale>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "Libraries\md5.h"
#include "FileReader.h"
#include "Utils.h"


namespace day1
{
	void part1(bool doPart2 = false)
	{
		const auto& line = getLine("day1.txt");
		std::istringstream iss(line);
		std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };

		int64_t result = 0;
		int64_t x = 0;
		int64_t y = 0;
		uint64_t facing = 0;

		std::set<std::pair<int64_t, int64_t>> locations;

		for (auto& token : tokens)
		{
			std::string numberString;
			for (size_t i = 1; i < token.size() - 1; ++i)
			{
				numberString += token[i];
			}

			auto number = toInteger(numberString);
			auto turnRight = (token[0] == 'R');

			for (int64_t i = 0; i < number; ++i)
			{
				std::pair<int64_t, int64_t> location(x, y);
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
		uint64_t result = 0;

		for (const auto& line : getLineByLine("day3.txt"))
		{
			std::istringstream iss(line);
			int64_t x, y, z;
			iss >> x >> y >> z;

			if (x + y > z && x + z > y && y + z > x) ++result;
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		uint64_t result = 0;
		int64_t x1, x2, x3;
		int64_t y1, y2, y3;
		int64_t z1, z2, z3;

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
		int64_t result = 0;

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
				auto number = toInteger<int>(tokens.back().substr(0, tokens.back().size() - 7));

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
			auto hash = md5(line + std::to_string(number));
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

namespace day7
{
	void part1(bool doPart2 = false)
	{
		uint64_t result = 0;

		for (auto& line : getLineByLine("day7.txt"))
		{
			std::vector<std::string> tokens;
			std::size_t start = 0, end = 0;
			while ((end = line.find_first_of("[]", start)) != std::string::npos) {
				if (end != start) {
					tokens.push_back({ line.substr(start, end - start) });
				}
				start = end + 1;
			}
			if (end != start) {
				tokens.push_back({ line.substr(start) });
			}

			bool isInside = false;
			bool foundAbba = false;
			bool foundInside = false;

			std::set<std::string> insideSet;
			std::set<std::string> outsideSet;

			for (const auto& token : tokens)
			{
				for (size_t i = 0; i < token.size() - (doPart2 ? 2 : 3); ++i)
				{
					if (doPart2)
					{
						if (token[i] == token[i + 2] && token[i] != token[i + 1])
						{
							if (isInside)
								insideSet.emplace(token[i + 1], token[i]);
							else
								outsideSet.emplace(token[i], token[i + 1]);
						}
					}
					else
					{
						if (token[i] == token[i + 3] && token[i + 1] == token[i + 2] && token[i] != token[i + 1])
						{
							if (isInside)
							{
								foundInside = true;
								break;
							}
							else
							{
								foundAbba = true;
							}
						}
					}
				}

				isInside = !isInside;
			}

			if (doPart2)
			{
				for (const auto& aba : insideSet)
				{
					if (outsideSet.find(aba) != outsideSet.cend())
					{
						++result;
						break;
					}
				}
			}
			else
			{
				if (!foundInside && foundAbba) ++result;
			}
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		part1(true);
	}
}

namespace day8
{
	void part1(bool doPart2 = false)
	{
		uint64_t result = 0;
		std::array<std::array<bool, 50>, 6> display;
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
				uint64_t tall = 0;
				for (const auto& character : tokens[1])
				{
					if (character == 'x')
					{
						wide = toInteger<uint64_t>(numberBuffer);
						numberBuffer.clear();
						continue;
					}

					numberBuffer += character;
				}
				tall = toInteger<uint64_t>(numberBuffer);

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
				uint64_t xy = 0;
				uint64_t by = 0;

				for (const auto& character : tokens[2])
				{
					if (character == 'x' || character == 'y' || character == '=') continue;
					numberBuffer += character;
				}
				xy = toInteger<uint64_t>(numberBuffer);
				numberBuffer.clear();

				for (const auto& character : tokens[4])
				{
					numberBuffer += character;
				}
				by = toInteger<uint64_t>(numberBuffer);

				if (tokens[1] == "row")
				{
					for (uint64_t i = 0; i < by; ++i)
					{
						bool buffer = display[xy].back();
						for (uint64_t j = display[xy].size() - 1; j > 0; --j)
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
						bool buffer = display.back()[xy];
						for (uint64_t j = display.size() - 1; j > 0; --j)
						{
							display[j][xy] = display[j - 1][xy];
						}
						display[0][xy] = buffer;
					}
				}
			}
		}

		if (doPart2)
		{
			std::cout << std::endl;
			for (auto& row : display)
			{
				for (auto& column : row)
				{
					if (column)
					{
						std::cout << "#";
					}
					else
					{
						std::cout << " ";
					}
				}
				std::cout << std::endl;
			}
		}
		else
		{
			for (auto& row : display)
			{
				for (auto& column : row)
				{
					if (column) ++result;
				}
			}
			std::cout << result << std::endl;
		}
	}

	void part2()
	{
		part1(true);
	}
}

namespace day9
{
	void part1()
	{
		std::string result;
		const auto& line = getLine("day9.txt");
		size_t index = 0;

		while (index < line.size())
		{
			if (line[index] == '(')
			{
				std::string buffer;
				uint64_t characters = 0;
				uint64_t repeats = 0;

				++index;
				while (line[index] >= '0' && line[index] <= '9')
				{
					buffer += line[index];
					++index;
				}
				characters = toInteger<uint64_t>(buffer);
				buffer.clear();

				++index;
				while (line[index] >= '0' && line[index] <= '9')
				{
					buffer += line[index];
					++index;
				}
				repeats = toInteger<uint64_t>(buffer);
				buffer.clear();

				for (uint64_t i = 0; i < characters; ++i)
				{
					++index;
					buffer += line[index];
				}

				for (uint64_t i = 0; i < repeats; ++i)
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

		std::cout << result.size() << std::endl;
	}

	void part2()
	{
		uint64_t result = 0;
		size_t index = 0;

		const auto& line = getLine("day9.txt");
		std::vector<uint64_t> weights;
		weights.resize(line.size());
		std::fill(weights.begin(), weights.end(), 1);

		while (index < line.size())
		{
			if (line[index] == '(')
			{
				std::string buffer;
				uint64_t characters = 0;
				uint64_t repeats = 0;

				++index;
				while (line[index] >= '0' && line[index] <= '9')
				{
					buffer += line[index];
					++index;
				}
				characters = toInteger<uint64_t>(buffer);
				buffer.clear();

				++index;
				while (line[index] >= '0' && line[index] <= '9')
				{
					buffer += line[index];
					++index;
				}
				repeats = toInteger<uint64_t>(buffer);
				buffer.clear();

				for (uint64_t i = 0; i < characters; ++i)
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

		std::cout << result << std::endl;
	}
}

namespace day10
{
	class Bot
	{
	public:
		Bot(int chip) : low(chip), high(-1) {};

		void addChip(int chip)
		{
			_ASSERT(high < 0);
			high = chip;
			if (low > high)
			{
				std::swap(low, high);
			}
		}

		std::pair<int, int> getChips()
		{
			_ASSERT(high > 0);
			return { low, high };
		}

	private:
		int low;
		int high;
	};

	void part1(bool doPart2 = false)
	{
		std::map<int, std::unique_ptr<Bot>> values;
		std::map<int, std::pair<std::pair<bool, int>, std::pair<bool, int>>> gives;
		std::map<int, int> outputs;
		std::queue<int> toTake;

		for (const auto& line : getLineByLine("day10.txt"))
		{
			std::istringstream iss(line);
			std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };
			if (tokens[0][0] == 'v')
			{
				auto number1 = toInteger<int>(tokens[1]);
				auto number2 = toInteger<int>(tokens[5]);
				if (values.find(number2) != values.end())
				{
					values[number2]->addChip(number1);
					toTake.push(number2);
				}
				else
				{
					values.insert({ number2, std::make_unique<Bot>(number1) });
				}
			}
			else
			{
				auto number1 = toInteger<int>(tokens[1]);
				auto number2 = toInteger<int>(tokens[6]);
				auto number3 = toInteger<int>(tokens[11]);
				_ASSERT(gives.find(number1) == gives.end());
				gives.insert({ number1, { { tokens[5][0] == 'b', number2 }, { tokens[10][0] == 'b', number3 } } });
			}
		}

		while (!toTake.empty())
		{
			auto head = toTake.front();
			toTake.pop();
			const auto chips = values[head]->getChips();

			if (!doPart2 && chips.first == 17 && chips.second == 61)
			{
				std::cout << head << std::endl;
				return;
			}

			const auto giveLow = gives[head].first;
			const auto giveHigh = gives[head].second;

			if (giveLow.first)
			{
				if (values.find(giveLow.second) != values.end())
				{
					values[giveLow.second]->addChip(chips.first);
					toTake.push(giveLow.second);
				}
				else
				{
					values.insert({ giveLow.second, std::make_unique<Bot>(chips.first) });
				}
			}
			else
			{
				outputs.insert({ giveLow.second, chips.first });
			}

			if (giveHigh.first)
			{
				if (values.find(giveHigh.second) != values.end())
				{
					values[giveHigh.second]->addChip(chips.second);
					toTake.push(giveHigh.second);
				}
				else
				{
					values.insert({ giveHigh.second, std::make_unique<Bot>(chips.second) });
				}
			}
			else
			{
				outputs.insert({ giveHigh.second, chips.second });
			}
		}

		if (doPart2)
		{
			std::cout << outputs[0] * outputs[1] * outputs[2] << std::endl;
		}
	}

	void part2()
	{
		part1(true);
	}
}

namespace day11
{
	void part1()
	{
		std::cout << std::endl;
	}

	void part2()
	{
		std::cout << std::endl;
	}
}

namespace day12
{
	void part1(bool doPart2 = false)
	{
		std::vector<std::vector<std::string>> codeLines;
		for (const auto& line : getLineByLine("day12.txt"))
		{
			std::istringstream iss(line);
			std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };
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
					auto number = toInteger(codeLines[index][1]);
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
				int64_t number2 = toInteger(codeLines[index][2]);

				if (codeLines[index][1][0] >= 'a' && codeLines[index][1][0] <= 'd')
				{
					number1 = result[codeLines[index][1][0] - 'a'];
				}
				else
				{
					number1 = toInteger(codeLines[index][1]);
				}

				if (number1)
				{
					index += number2;
					--index;
				}
				
			}
			++index;
		}

		std::cout << result[0] << std::endl;
	}

	void part2()
	{
		part1(true);
	}
}

namespace day13
{
	void part1(bool doPart2 = false)
	{
		std::queue<std::pair<int64_t, int64_t>> toGo;
		std::map<std::pair<int64_t, int64_t>, int64_t> distances;
		std::pair<int64_t, int64_t> result = { 31, 39 };
		toGo.push({ 1, 1 });
		distances.insert({ {1, 1}, 0 });

		while (!toGo.empty())
		{
			auto head = toGo.front();
			toGo.pop();
			const auto distance = distances[head];

			if (doPart2 && distance == 50)
			{
				std::cout << distances.size() << std::endl;
				return;
			}

			if (!doPart2 && head == result)
			{
				std::cout << distance << std::endl;
				return;
			}

			std::vector<std::pair<int64_t, int64_t>> neighbors =
			{
				{ head.first + 1, head.second },
				{ head.first - 1, head.second },
				{ head.first, head.second + 1 },
				{ head.first, head.second - 1 }
			};

			for (auto& neighbor : neighbors)
			{
				if (neighbor.first < 0 || neighbor.second < 0 || distances.find(neighbor) != distances.end())
				{
					continue;
				}

				uint64_t x = neighbor.first;
				uint64_t y = neighbor.second;
				uint64_t number = x * x + 3 * x + 2 * x * y + y + y * y;
				number += 1350;
				std::bitset<64> bits(number);

				if (bits.count() % 2)
				{
					continue;
				}

				toGo.push(neighbor);
				distances.emplace(neighbor, distance + 1);
			}
		}
	}

	void part2()
	{
		part1(true);
	}
}

namespace day14
{
	size_t THREADSIZE = 8;

	void part1(bool doPart2 = false)
	{
		const auto line = getLine("day14.txt");
		auto keyNumber = 0;
		std::vector<std::string> hashes;
		std::vector<std::thread> threads;
		hashes.resize(24'000);
		threads.resize(THREADSIZE);

		for (size_t number = 0; number < hashes.size(); number += THREADSIZE)
		{
			for (auto i = 0; i < THREADSIZE; ++i)
			{
				threads[i] = std::thread(
					[&hashes, &line, doPart2](size_t number)
					{
						hashes[number] = md5(line + std::to_string(number));
						if (doPart2)
						{
							for (auto i = 0; i < 2016; ++i)
							{
								hashes[number] = md5(hashes[number]);
							}
						}
					},
					number + i
				);
			}

			for (auto i = 0; i < THREADSIZE; ++i)
			{
				threads[i].join();
			}
		}

		for (size_t number = 0; number < hashes.size(); ++number)
		{
			char previous = ' ';
			auto counter = 1;

			for (size_t index = 0; index < 32; ++index)
			{
				if (hashes[number][index] == previous)
				{
					++counter;
					if (counter == 3)
					{
						break;
					}
				}
				else
				{
					previous = hashes[number][index];
					counter = 1;
				}
			}

			if (counter != 3)
			{
				continue;
			}

			for (unsigned int index = 0; index < 1'000; ++index)
			{
				auto number2 = number + index + 1;
				std::string toFind = { previous, previous, previous, previous, previous };
				auto it = hashes[number2].find(toFind);
				if (it == std::string::npos)
				{
					continue;
				}

				++keyNumber;
				if (keyNumber == 64)
				{
					std::cout << number << std::endl;
					return;
				}
				break;
			}
		}
	}

	void part2()
	{
		part1(true);
	}
}

namespace day15
{
	void part1(bool doPart2 = false)
	{
		uint64_t time = 0;
		std::vector<std::pair<int, int>> disks;
		std::vector<int> positions;

		for (const auto& line : getLineByLine("day15.txt"))
		{
			std::istringstream iss(line);
			std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };
			disks.emplace_back(toInteger<int>(tokens[3]), toInteger<int>(tokens[11].substr(0, tokens[11].size() - 1)));
		}

		if (doPart2)
		{
			disks.emplace_back(11, 0);
		}

		positions.resize(disks.size());

		for (size_t i = 0; i < disks.size(); ++i)
		{
			positions[i] = (disks[i].second + i + 1) % disks[i].first;
		}

		while (!std::equal(positions.begin() + 1, positions.end(), positions.begin()))
		{
			for (size_t i = 0; i < disks.size(); ++i)
			{
				++positions[i];
				positions[i] %= disks[i].first;
			}
			++time;
		} 

		std::cout << time << std::endl;
	}

	void part2()
	{
		part1(true);
	}
}

namespace day16
{
	void part1(bool doPart2 = false)
	{
		auto line = getLine("day16.txt");
		const size_t diskLength = (doPart2) ? 35'651'584 : 272;
		std::string result;

		while (line.length() < diskLength)
		{
			std::string lineB = line;
			std::reverse(lineB.begin(), lineB.end());
			std::for_each(lineB.begin(), lineB.end(), [](char& character) { if (character == '0') character = '1'; else character = '0'; });
			line += '0' + lineB;
		}

		line = line.substr(0, diskLength);
		result = line;

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

		std::cout << result << std::endl;
	}

	void part2()
	{
		part1(true);
	}
}

namespace day17
{
	std::string result;

	void part1Recursion(int x, int y, std::string& path, bool doPart2)
	{
		if (x == 3 && y == 3)
		{
			if ((doPart2 && path.size() > result.size()) ||
				(!doPart2 && (path.size() < result.size() || result.empty())))
			{
				result = path;
			}
			return;
		}

		auto hash = md5(path);

		if (hash[0] > 'a' && hash[0] < 'g' && y > 0) part1Recursion(x, y - 1, path + 'U', doPart2);
		if (hash[1] > 'a' && hash[1] < 'g' && y < 3) part1Recursion(x, y + 1, path + 'D', doPart2);
		if (hash[2] > 'a' && hash[2] < 'g' && x > 0) part1Recursion(x - 1, y, path + 'L', doPart2);
		if (hash[3] > 'a' && hash[3] < 'g' && x < 3) part1Recursion(x + 1, y, path + 'R', doPart2);
	}

	void part1(bool doPart2 = false)
	{
		auto path = getLine("day17.txt");
		part1Recursion(0, 0, path, doPart2);
		if (doPart2)
		{
			std::cout << result.size() - 8 << std::endl;
		}
		else
		{
			std::cout << result.substr(8) << std::endl;
		}
	}

	void part2()
	{
		part1(true);
	}
}

namespace day18
{
	void part1(bool doPart2 = false)
	{
		auto pathA = '.' + getLine("day18.txt") + '.';
		uint64_t result = 0;
		uint64_t limit = (doPart2 ? 400'000 : 40);

		for (uint64_t i = 0; i < limit; ++i)
		{
			std::for_each(pathA.begin(), pathA.end(), [&result](char character) { if (character == '.') ++result; });
			result -= 2;

			std::string pathB;
			pathB += '.';
			for (size_t j = 1; j < pathA.size() - 1; ++j)
			{
				if ((pathA[j - 1] == '^' && pathA[j] == '^' && pathA[j + 1] == '.') ||
					(pathA[j - 1] == '.' && pathA[j] == '^' && pathA[j + 1] == '^') ||
					(pathA[j - 1] == '^' && pathA[j] == '.' && pathA[j + 1] == '.') ||
					(pathA[j - 1] == '.' && pathA[j] == '.' && pathA[j + 1] == '^'))
				{
					pathB += '^';
				}
				else
				{
					pathB += '.';
				}
			}
			pathB += '.';
			pathA = pathB;
		}
		std::cout << result << std::endl;
	}

	void part2()
	{
		part1(true);
	}
}

namespace day19
{
	void part1()
	{
		auto number = toInteger<uint64_t>(getLine("day19.txt"));
		int64_t logarithm = static_cast<int64_t>(std::log(number) / std::log(2));
		int64_t power = static_cast<int64_t>(std::pow(2, logarithm));
		std::cout << (number - power) * 2 + 1 << std::endl;
	}

	void part2()
	{
		auto number = toInteger<int64_t>(getLine("day19.txt"));
		int64_t logarithm = static_cast<int64_t>(std::log(number) / std::log(3));
		int64_t power = static_cast<int64_t>(std::pow(3, logarithm));
		int64_t maximum = std::max(number - 2 * power, static_cast<int64_t>(0));
		std::cout << number - power + maximum << std::endl;
	}
}

namespace day20
{
	void part1(bool doPart2 = false)
	{
		std::vector<std::pair<uint32_t, uint32_t>> ranges;
		std::vector<uint32_t> result;
		uint32_t last = 0;

		for (const auto& line : getLineByLine("day20.txt"))
		{
			uint32_t low, high;
			std::size_t start = 0, end = 0;
			while ((end = line.find('-', start)) != std::string::npos) {
				if (end != start) {
					low = toInteger<uint32_t>(line.substr(start, end - start));
				}
				start = end + 1;
			}
			if (end != start) {
				high = toInteger<uint32_t>(line.substr(start));
			}

			ranges.emplace_back(low, high);
		}

		std::sort(ranges.begin(), ranges.end());

		for (const auto& range : ranges)
		{
			if (range.first > last)
			{
				for (auto i = last + 1; i < range.first; ++i)
				{
					result.push_back(i);
				}
			}
			
			if (range.second > last) {
				last = range.second;
			}
		}

		if (doPart2)
		{
			std::cout << result.size() << std::endl;
		}
		else
		{
			std::cout << result[0] << std::endl;
		}
	}

	void part2()
	{
		part1(true);
	}
}

namespace day21
{
	void part1()
	{
		std::string result = "abcdefgh";

		for (const auto& line : getLineByLine("day21.txt"))
		{
			std::istringstream iss(line);
			std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };

			if (tokens[0][0] == 's' && tokens[1][0] == 'p')
			{
				auto X = toInteger<uint32_t>(tokens[2]);
				auto Y = toInteger<uint32_t>(tokens[5]);
				std::swap(result[X], result[Y]);
			}
			else if (tokens[0][0] == 's' && tokens[1][0] == 'l')
			{
				auto X = result.find(tokens[2][0]);
				auto Y = result.find(tokens[5][0]);
				std::swap(result[X], result[Y]);
			}
			else if (tokens[0][0] == 'r' && tokens[1][0] == 'l')
			{
				auto X = toInteger<uint32_t>(tokens[2]) % result.size();
				std::rotate(result.begin(), result.begin() + X, result.end());
			}
			else if (tokens[0][0] == 'r' && tokens[1][0] == 'r')
			{
				auto X = toInteger<uint32_t>(tokens[2]) % result.size();
				std::rotate(result.begin(), result.begin() + (result.size() - X), result.end());
			}
			else if (tokens[0][0] == 'r' && tokens[1][0] == 'b')
			{
				auto X = result.find(tokens[6][0]);
				X += (X >= 4) ? 2 : 1;
				X = X % result.size();
				std::rotate(result.begin(), result.begin() + (result.size() - X), result.end());
			}
			else if (tokens[0][0] == 'r' && tokens[1][0] == 'p')
			{
				auto X = toInteger<uint32_t>(tokens[2]);
				auto Y = toInteger<uint32_t>(tokens[4]);
				std::reverse(result.begin() + X, result.begin() + Y + 1);
			}
			else if (tokens[0][0] == 'm' && tokens[1][0] == 'p')
			{
				auto X = toInteger<uint32_t>(tokens[2]);
				auto Y = toInteger<uint32_t>(tokens[5]);
				auto temp = result[X];

				result.erase(X, 1);
				result.insert(result.begin() + Y, temp);
			}
			else
			{
				_ASSERT(false);
			}
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		std::string result = "fbgdceah";
		std::vector<std::string> lines;

		for (const auto& line : getLineByLine("day21.txt"))
		{
			lines.push_back(line);
		}

		std::reverse(lines.begin(), lines.end());

		for (const auto& line : lines)
		{
			std::istringstream iss(line);
			std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };

			if (tokens[0][0] == 's' && tokens[1][0] == 'p')
			{
				auto X = toInteger<uint32_t>(tokens[2]);
				auto Y = toInteger<uint32_t>(tokens[5]);
				std::swap(result[Y], result[X]);
			}
			else if (tokens[0][0] == 's' && tokens[1][0] == 'l')
			{
				auto X = result.find(tokens[2][0]);
				auto Y = result.find(tokens[5][0]);
				std::swap(result[Y], result[X]);
			}
			else if (tokens[0][0] == 'r' && tokens[1][0] == 'l')
			{
				auto X = toInteger<uint32_t>(tokens[2]) % result.size();
				std::rotate(result.begin(), result.begin() + (result.size() - X), result.end());
			}
			else if (tokens[0][0] == 'r' && tokens[1][0] == 'r')
			{
				auto X = toInteger<uint32_t>(tokens[2]) % result.size();
				std::rotate(result.begin(), result.begin() + X, result.end());
			}
			else if (tokens[0][0] == 'r' && tokens[1][0] == 'b')
			{
				auto X = result.find(tokens[6][0]);
				X += (X  != 0 && X % 2 == 0) ? result.size() : 0;
				X = (X / 2 + 1) % result.size();
				std::rotate(result.begin(), result.begin() + X, result.end());
			}
			else if (tokens[0][0] == 'r' && tokens[1][0] == 'p')
			{
				auto X = toInteger<uint32_t>(tokens[2]);
				auto Y = toInteger<uint32_t>(tokens[4]);
				std::reverse(result.begin() + X, result.begin() + Y + 1);
			}
			else if (tokens[0][0] == 'm' && tokens[1][0] == 'p')
			{
				auto X = toInteger<uint32_t>(tokens[2]);
				auto Y = toInteger<uint32_t>(tokens[5]);
				auto temp = result[Y];

				result.erase(Y, 1);
				result.insert(result.begin() + X, temp);
			}
			else
			{
				_ASSERT(false);
			}
		}

		std::cout << result << std::endl;
	}
}

namespace day22
{
	class Node
	{
	public:
		Node(uint32_t x, uint32_t y, uint32_t size, uint32_t used, uint32_t avail, uint32_t use) :
			m_x(x), m_y(y), m_size(size), m_used(used), m_avail(avail), m_use(use)
		{}

	public:
		uint32_t m_x;
		uint32_t m_y;
		uint32_t m_size;
		uint32_t m_used;
		uint32_t m_avail;
		uint32_t m_use;
	};

	uint32_t BFS(std::pair<uint32_t, uint32_t> start, std::pair<uint32_t, uint32_t> end, uint32_t maxX, uint32_t maxY, std::function<bool(std::pair<uint32_t, uint32_t>&)> isWall)
	{
		std::map<std::pair<uint32_t, uint32_t>, uint32_t> distances;
		std::queue<std::pair<uint32_t, uint32_t>> toGo;
		toGo.push(start);

		while (!toGo.empty())
		{
			auto head = toGo.front();
			toGo.pop();
			const auto distance = distances[head];

			std::vector<std::pair<uint32_t, uint32_t>> neighbors =
			{
				{ head.first + 1, head.second },
				{ head.first - 1, head.second },
				{ head.first, head.second + 1 },
				{ head.first, head.second - 1 }
			};

			for (auto& neighbor : neighbors)
			{
				if (neighbor.first < 0 || neighbor.second < 0 || neighbor.first > maxX || neighbor.second > maxY || distances.find(neighbor) != distances.end())
				{
					continue;
				}

				if (isWall(neighbor))
				{
					continue;
				}


				if (neighbor.first == end.first && neighbor.second == end.second)
				{
					return distance + 1;
				}

				toGo.push(neighbor);
				distances.emplace(neighbor, distance + 1);
			}
		}

		return 0;
	}

	void part1(bool doPart2 = false)
	{
		std::vector<Node> nodes;
		std::map<std::pair<uint32_t, uint32_t>, uint32_t> nodesMap;
		size_t lineIndex = 0;
		uint32_t result = 0;

		uint32_t minimum = 500;
		uint32_t maxX = 0;
		uint32_t maxY = 0;
		uint32_t emptyX = 0;
		uint32_t emptyY = 0;

		for (const auto& line : getLineByLine("day22.txt"))
		{
			if (lineIndex < 2)
			{
				++lineIndex;
				continue;
			}

			std::istringstream iss(line);
			std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };

			std::size_t start = 0, end = 0;
			while ((end = tokens[0].find('-', start)) != std::string::npos) {
				if (end != start) {
					tokens.push_back(tokens[0].substr(start, end - start));
				}
				start = end + 1;
			}
			if (end != start) {
				tokens.push_back(tokens[0].substr(start));
			}

			tokens[1].pop_back();
			tokens[2].pop_back();
			tokens[3].pop_back();
			tokens[4].pop_back();
			auto size	= toInteger<uint32_t>(tokens[1]);
			auto used	= toInteger<uint32_t>(tokens[2]);
			auto avail	= toInteger<uint32_t>(tokens[3]);
			auto use	= toInteger<uint32_t>(tokens[4]);

			auto x		= toInteger<uint32_t>(tokens[6].substr(1));
			auto y		= toInteger<uint32_t>(tokens[7].substr(1));

			if (size < minimum) minimum = size;
			if (x > maxX) maxX = x;
			if (y > maxY) maxY = y;
			if (used == 0)
			{
				emptyX = x;
				emptyY = y;
			}

			nodes.emplace_back(x, y, size, used, avail, use);
			nodesMap.emplace(std::make_pair(x, y), static_cast<uint32_t>(nodes.size() - 1));
		}


		if (doPart2)
		{
			auto isWall = [&nodes, &nodesMap, &minimum](std::pair<uint32_t, uint32_t> coord) { return nodes[nodesMap[coord]].m_used > minimum; };
			auto distanceToGoal = BFS({ emptyX, emptyY }, { maxX - 1, 0 }, maxX, maxY, isWall);
			auto distanceTo00 = BFS({ maxX - 1, 0 }, { 0, 0 }, maxX, maxY, isWall);
			std::cout << distanceTo00 * 5 + 1 + distanceToGoal << std::endl;
		}
		else
		{
			for (size_t i = 0; i < nodes.size(); ++i)
			{
				if (nodes[i].m_used <= 0)
				{
					continue;
				}

				for (size_t j = 0; j < nodes.size(); ++j)
				{
					if (i != j && nodes[i].m_used <= nodes[j].m_avail)
					{
						++result;
					}
				}
			}

			std::cout << result << std::endl;
		}
	}

	void part2()
	{
		part1(true);
	}
}

namespace day23
{
	void part1(bool doPart2 = false)
	{
		std::vector<std::vector<std::string>> codeLines;
		for (const auto& line : getLineByLine("day23.txt"))
		{
			std::istringstream iss(line);
			std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };
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
					auto number = toInteger(codeLines[index][1]);
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
					number1 = toInteger(codeLines[index][1]);
				}

				int64_t number2;
				if (codeLines[index][2][0] >= 'a' && codeLines[index][2][0] <= 'd')
				{
					number2 = result[codeLines[index][2][0] - 'a'];
				}
				else
				{
					number2 = toInteger(codeLines[index][2]);
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
					number = toInteger(codeLines[index][1]);
				}

				auto newIndex = index + number;
				if (newIndex >= 0 && newIndex < codeLines.size())
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

		std::cout << result[0] << std::endl;
	}

	void part2()
	{
		part1(true);
	}
}

int main(int argc, char** argv)
{
	std::cout << "Day 1 Part 1 (expected 246): ";					day1::part1();
	std::cout << "Day 1 Part 2 (expected 124): ";					day1::part2();
	std::cout << "Day 2 Part 1 (expected 24862): ";					day2::part1();
	std::cout << "Day 2 Part 2 (expected 46C91): ";					day2::part2();
	std::cout << "Day 3 Part 1 (expected 993): ";					day3::part1();
	std::cout << "Day 3 Part 2 (expected 1849): ";					day3::part2();
	std::cout << "Day 4 Part 1 (expected 409147): ";				day4::part1();
	std::cout << "Day 4 Part 2 (expected 991): ";					day4::part2();
	std::cout << "Day 5 Part 1 (expected f97c354d): ";				day5::part1();
	std::cout << "Day 5 Part 2 (expected 863dde27): ";				day5::part2();
	std::cout << "Day 6 Part 1 (expected bjosfbce): ";				day6::part1();
	std::cout << "Day 6 Part 2 (expected veqfxzfx): ";				day6::part2();
	std::cout << "Day 7 Part 1 (expected 115): ";					day7::part1();
	std::cout << "Day 7 Part 2 (expected 231): ";					day7::part2();
	std::cout << "Day 8 Part 1 (expected 116): ";					day8::part1();
	std::cout << "Day 8 Part 2 (expected UPOJFLBCEZ): ";			day8::part2();
	std::cout << "Day 9 Part 1 (expected 150914): ";				day9::part1();
	std::cout << "Day 9 Part 2 (expected 11052855125): ";			day9::part2();
	std::cout << "Day 10 Part 1 (expected 157): ";					day10::part1();
	std::cout << "Day 10 Part 2 (expected 1085): ";					day10::part2();
	std::cout << "Day 11 Part 1 (expected ): ";						day11::part1();
	std::cout << "Day 11 Part 2 (expected ): ";						day11::part2();
	std::cout << "Day 12 Part 1 (expected 318020): ";				day12::part1();
	std::cout << "Day 12 Part 2 (expected 9227674): ";				day12::part2();
	std::cout << "Day 13 Part 1 (expected 92): ";					day13::part1();
	std::cout << "Day 13 Part 2 (expected 124): ";					day13::part2();
	std::cout << "Day 14 Part 1 (expected 15035): ";				day14::part1();
	std::cout << "Day 14 Part 2 (expected 19968): ";				day14::part2();
	std::cout << "Day 15 Part 1 (expected 148737): ";				day15::part1();
	std::cout << "Day 15 Part 2 (expected 2353212): ";				day15::part2();
	std::cout << "Day 16 Part 1 (expected 10010010110011010): ";	day16::part1();
	std::cout << "Day 16 Part 2 (expected 01010100101011100): ";	day16::part2();
	std::cout << "Day 17 Part 1 (expected DDRUDLRRRD): ";			day17::part1();
	std::cout << "Day 17 Part 2 (expected 398): ";					day17::part2();
	std::cout << "Day 18 Part 1 (expected 1978): ";					day18::part1();
	std::cout << "Day 18 Part 2 (expected 20003246): ";				day18::part2();
	std::cout << "Day 19 Part 1 (expected 1834903): ";				day19::part1();
	std::cout << "Day 19 Part 2 (expected 1420280): ";				day19::part2();
	std::cout << "Day 20 Part 1 (expected 22887907): ";				day20::part1();
	std::cout << "Day 20 Part 2 (expected 109): ";					day20::part2();
	std::cout << "Day 21 Part 1 (expected fdhbcgea): ";				day21::part1();
	std::cout << "Day 21 Part 2 (expected egfbcadh): ";				day21::part2();
	std::cout << "Day 22 Part 1 (expected 1043): ";					day22::part1();
	std::cout << "Day 22 Part 2 (expected 185): ";					day22::part2();
	std::cout << "Day 23 Part 1 (expected 11736): ";				day23::part1();
	std::cout << "Day 23 Part 2 (expected 479008296): ";			day23::part2();

	system("pause");
	return 0;
}
