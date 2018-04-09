#include "Day4.h"

#include "FileReader.h"

#include <algorithm>
#include <map>

namespace day4
{
	int64_t part1(const bool doPart2)
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
					const auto index = charCount.find(tokens[i][j]);
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
				const auto number = std::stoll(tokens.back().substr(0, tokens.back().size() - 7));

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
							return number;
						}
					}
				}
				else
				{
					result += number;
				}
			}
		}

		return result;
	}

	int64_t part1()
	{
		return part1(false);
	}

	int64_t part2()
	{
		return part1(true);
	}
}  // namespace day4