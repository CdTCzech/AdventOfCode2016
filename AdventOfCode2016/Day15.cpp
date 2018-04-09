#include "Day15.h"

#include "FileReader.h"

#include <iterator>
#include <sstream>

namespace day15
{
	int64_t part1(const bool doPart2)
	{
		int64_t time = 0;
		std::vector<std::pair<int64_t, int64_t>> disks;
		std::vector<int64_t> positions;

		for (const auto& line : getLineByLine("day15.txt"))
		{
			std::istringstream iss(line);
			std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };
			disks.emplace_back(std::stoll(tokens[3]), std::stoll(tokens[11].substr(0, tokens[11].size() - 1)));
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

		return time;
	}

	int64_t part1()
	{
		return part1(false);
	}

	int64_t part2()
	{
		return part1(true);
	}
}  // namespace day15