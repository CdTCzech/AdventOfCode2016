#include "Day14.h"

#include "FileReader.h"

#include "Libraries/md5.h"

#include <thread>

namespace day14
{
	int64_t part1(bool doPart2)
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
				threads[i] = std::thread([&hashes, &line, doPart2](size_t number)
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
			auto previous = ' ';
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
				const auto number2 = number + index + 1;
				const std::string toFind = { previous, previous, previous, previous, previous };
				const auto it = hashes[number2].find(toFind);
				if (it == std::string::npos)
				{
					continue;
				}

				++keyNumber;
				if (keyNumber == 64)
				{
					return number;
				}
				break;
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
}  // namespace day14