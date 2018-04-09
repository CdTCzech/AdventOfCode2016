#include "Day7.h"

#include "FileReader.h"

#include <set>

namespace day7
{
	int64_t part1(const bool doPart2)
	{
		int64_t result = 0;

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
							foundAbba = true;
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
}  // namespace day7