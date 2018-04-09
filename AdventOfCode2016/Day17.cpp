#include "Day17.h"

#include "FileReader.h"

#include "Libraries/md5.h"

namespace day17
{
	void recursion(const int x, const int y, const std::string& path, std::string& result, const bool doPart2)
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

		if (hash[0] > 'a' && hash[0] < 'g' && y > 0) recursion(x, y - 1, path + 'U', result, doPart2);
		if (hash[1] > 'a' && hash[1] < 'g' && y < 3) recursion(x, y + 1, path + 'D', result, doPart2);
		if (hash[2] > 'a' && hash[2] < 'g' && x > 0) recursion(x - 1, y, path + 'L', result, doPart2);
		if (hash[3] > 'a' && hash[3] < 'g' && x < 3) recursion(x + 1, y, path + 'R', result, doPart2);
	}

	std::string part1()
	{
		std::string result;
		const auto path = getLine("day17.txt");
		recursion(0, 0, path, result, false);
		return result.substr(8);
	}

	int64_t part2()
	{
		std::string result;
		const auto path = getLine("day17.txt");
		recursion(0, 0, path, result, true);
		return result.size() - 8;
	}
}  // namespace day17