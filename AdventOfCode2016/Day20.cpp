#include "Day20.h"

#include "FileReader.h"

#include <algorithm>

namespace day20
{
	int64_t part1(const bool doPart2)
	{
		std::vector<std::pair<int64_t, int64_t>> ranges;
		std::vector<int64_t> result;
		int64_t last = 0;

		for (const auto& line : getLineByLine("day20.txt"))
		{
			int64_t low, high;
			std::size_t start = 0, end = 0;
			while ((end = line.find('-', start)) != std::string::npos) {
				if (end != start) {
					low = std::stoll(line.substr(start, end - start));
				}
				start = end + 1;
			}
			if (end != start) {
				high = std::stoll(line.substr(start));
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
			return result.size();
		}
		return result[0];
	}

	int64_t part1()
	{
		return part1(false);
	}

	int64_t part2()
	{
		return part1(true);
	}
}  // namespace day20