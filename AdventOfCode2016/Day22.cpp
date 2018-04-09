#include "Day22.h"

#include "FileReader.h"

#include <iterator>
#include <map>
#include <queue>
#include <sstream>

namespace day22
{
	class Node
	{
	public:
		Node(const int64_t x, const int64_t y, const int64_t size, const int64_t used, const int64_t avail, const int64_t use) :
			m_x(x), m_y(y), m_size(size), m_used(used), m_avail(avail), m_use(use)
		{}

	public:
		int64_t m_x;
		int64_t m_y;
		int64_t m_size;
		int64_t m_used;
		int64_t m_avail;
		int64_t m_use;
	};

	int64_t BFS(const std::pair<int64_t, int64_t> start, const std::pair<int64_t, int64_t> end, const int64_t maxX, const int64_t maxY, const std::function<bool(std::pair<int64_t, int64_t>&)>& isWall)
	{
		std::map<std::pair<int64_t, int64_t>, int64_t> distances;
		std::queue<std::pair<int64_t, int64_t>> toGo;
		toGo.push(start);

		while (!toGo.empty())
		{
			auto head = toGo.front();
			toGo.pop();
			const auto distance = distances[head];

			std::vector<std::pair<int64_t, int64_t>> neighbors =
			{
				{ head.first + 1, head.second },
				{ head.first - 1, head.second },
				{ head.first, head.second + 1 },
				{ head.first, head.second - 1 }
			};

			for (auto& neighbor : neighbors)
			{
				if (neighbor.first > maxX || neighbor.second > maxY || distances.find(neighbor) != distances.end())
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

	int64_t part1(const bool doPart2)
	{
		std::vector<Node> nodes;
		std::map<std::pair<int64_t, int64_t>, int64_t> nodesMap;
		size_t lineIndex = 0;
		int64_t result = 0;

		int64_t minimum = 500;
		int64_t maxX = 0;
		int64_t maxY = 0;
		int64_t emptyX = 0;
		int64_t emptyY = 0;

		for (const auto& line : getLineByLine("day22.txt"))
		{
			if (lineIndex < 2)
			{
				++lineIndex;
				continue;
			}

			std::istringstream iss(line);
			std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };

			size_t start = 0, end;
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
			auto size = std::stoll(tokens[1]);
			auto used = std::stoll(tokens[2]);
			auto avail = std::stoll(tokens[3]);
			auto use = std::stoll(tokens[4]);

			auto x = std::stoll(tokens[6].substr(1));
			auto y = std::stoll(tokens[7].substr(1));

			if (size < minimum) minimum = size;
			if (x > maxX) maxX = x;
			if (y > maxY) maxY = y;
			if (used == 0)
			{
				emptyX = x;
				emptyY = y;
			}

			nodes.emplace_back(x, y, size, used, avail, use);
			nodesMap.emplace(std::make_pair(x, y), static_cast<int64_t>(nodes.size() - 1));
		}


		if (doPart2)
		{
			const auto isWall = [&nodes, &nodesMap, &minimum](std::pair<int64_t, int64_t> coord) { return nodes[nodesMap[coord]].m_used > minimum; };
			const auto distanceToGoal = BFS({ emptyX, emptyY }, { maxX - 1, 0 }, maxX, maxY, isWall);
			const auto distanceTo00 = BFS({ maxX - 1, 0 }, { 0, 0 }, maxX, maxY, isWall);
			return distanceTo00 * 5 + 1 + distanceToGoal;
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

			return result;
		}
	}

	int64_t part1()
	{
		return part1(false);
	}

	int64_t part2()
	{
		return part1(true);
	}
}  // namespace day22