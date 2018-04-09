#pragma once

#include <algorithm>
#include <cstdint>
#include <utility>

namespace day10
{
	class Bot
	{
	public:
		Bot(const int64_t chip) : low(chip), high(-1) {};

		void addChip(const int64_t chip)
		{
			_ASSERT(high < 0);
			high = chip;
			if (low > high)
			{
				std::swap(low, high);
			}
		}

		std::pair<int64_t, int64_t> getChips()
		{
			_ASSERT(high > 0);
			return { low, high };
		}

	private:
		int64_t low;
		int64_t high;
	};

	int64_t part1();
	int64_t part2();
}  // namespace day10