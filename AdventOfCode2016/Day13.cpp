#include "Day13.h"

#include "FileReader.h"

#include <bitset>
#include <map>
#include <queue>

namespace day13
{
	int64_t part1(const bool doPart2)
	{
		std::queue<std::pair<int64_t, int64_t>> toGo;
		std::map<std::pair<int64_t, int64_t>, int64_t> distances;
		const std::pair<int64_t, int64_t> result = { 31, 39 };
		toGo.push({ 1, 1 });
		distances.insert({ { 1, 1 }, 0 });

		while (!toGo.empty())
		{
			auto head = toGo.front();
			toGo.pop();
			const auto distance = distances[head];

			if (doPart2 && distance == 50)
			{
				return distances.size();
			}

			if (!doPart2 && head == result)
			{
				return distance;
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

				const auto x = neighbor.first;
				const auto y = neighbor.second;
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
}  // namespace day13