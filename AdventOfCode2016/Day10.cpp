#include "Day10.h"

#include "FileReader.h"

#include <iterator>
#include <map>
#include <queue>
#include <sstream>

namespace day10
{
	int64_t part1(const bool doPart2)
	{
		std::map<int64_t, std::unique_ptr<Bot>> values;
		std::map<int64_t, std::pair<std::pair<bool, int64_t>, std::pair<bool, int64_t>>> gives;
		std::map<int64_t, int64_t> outputs;
		std::queue<int64_t> toTake;

		for (const auto& line : getLineByLine("day10.txt"))
		{
			std::istringstream iss(line);
			std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };
			if (tokens[0][0] == 'v')
			{
				auto number1 = std::stoll(tokens[1]);
				auto number2 = std::stoll(tokens[5]);
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
				const auto number1 = std::stoll(tokens[1]);
				auto number2 = std::stoll(tokens[6]);
				auto number3 = std::stoll(tokens[11]);
				_ASSERT(gives.find(number1) == gives.end());
				gives.insert({ number1,{ { tokens[5][0] == 'b', number2 },{ tokens[10][0] == 'b', number3 } } });
			}
		}

		while (!toTake.empty())
		{
			auto head = toTake.front();
			toTake.pop();
			const auto chips = values[head]->getChips();

			if (!doPart2 && chips.first == 17 && chips.second == 61)
			{
				return head;
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
			return outputs[0] * outputs[1] * outputs[2];
		}

		return 0;
	}

	int64_t part1()
	{
		return part1(false);
	}

	int64_t part2()
	{
		return part1(true);
	}
}  // namespace day10