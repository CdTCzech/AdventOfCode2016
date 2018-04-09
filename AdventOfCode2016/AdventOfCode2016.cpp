#include "Day1.h"
#include "Day2.h"
#include "Day3.h"
#include "Day4.h"
#include "Day5.h"
#include "Day6.h"
#include "Day7.h"
#include "Day8.h"
#include "Day9.h"
#include "Day10.h"
//#include "Day11.h"
#include "Day12.h"
#include "Day13.h"
#include "Day14.h"
#include "Day15.h"
#include "Day16.h"
#include "Day17.h"
#include "Day18.h"
#include "Day19.h"
#include "Day20.h"
#include "Day21.h"
#include "Day22.h"
#include "Day23.h"
//#include "Day24.h"
//#include "Day25.h"

#include "Test.h"

#include <cstdint>
#include <string>

const char* upojflbcez = R"(
#  # ###   ##    ## #### #    ###   ##  #### #### x
#  # #  # #  #    # #    #    #  # #  # #       # x
#  # #  # #  #    # ###  #    ###  #    ###    #  x
#  # ###  #  #    # #    #    #  # #    #     #   x
#  # #    #  # #  # #    #    #  # #  # #    #    x
 ##  #     ##   ##  #    #### ###   ##  #### #### x
)";

int main(int /*argc*/, char** /*argv*/)
{
	try
	{
		test::test<int64_t>(     1, 1,                 246, day1::part1);
		test::test<int64_t>(     1, 2,                 124, day1::part2);
		test::test<int64_t>(     2, 1,              24'862, day2::part1);
		test::test<std::string>( 2, 2,             "46C91", day2::part2);
		test::test<int64_t>(     3, 1,                 993, day3::part1);
		test::test<int64_t>(     3, 2,               1'849, day3::part2);
		test::test<int64_t>(     4, 1,             409'147, day4::part1);
		test::test<int64_t>(     4, 2,                 991, day4::part2);
		test::test<std::string>( 5, 1,          "f97c354d", day5::part1);
		test::test<std::string>( 5, 2,          "863dde27", day5::part2);
		test::test<std::string>( 6, 1,          "bjosfbce", day6::part1);
		test::test<std::string>( 6, 2,          "veqfxzfx", day6::part2);
		test::test<int64_t>(     7, 1,                 115, day7::part1);
		test::test<int64_t>(     7, 2,                 231, day7::part2);
		test::test<int64_t>(     8, 1,                 116, day8::part1);
		test::test<std::string>( 8, 2,          upojflbcez, day8::part2);
		test::test<int64_t>(     9, 1,             150'914, day9::part1);
		test::test<int64_t>(     9, 2,      11'052'855'125, day9::part2);
		test::test<int64_t>(    10, 1,                 157, day10::part1);
		test::test<int64_t>(    10, 2,               1'085, day10::part2);
		//test::test<std::string>(11, 1,                  "", day11::part1);
		//test::test<std::string>(11, 2,                  "", day11::part2);
		test::test<int64_t>(    12, 1,             318'020, day12::part1);
		test::test<int64_t>(    12, 2,           9'227'674, day12::part2);
		test::test<int64_t>(    13, 1,                  92, day13::part1);
		test::test<int64_t>(    13, 2,                 124, day13::part2);
		test::test<int64_t>(    14, 1,              15'035, day14::part1);
		test::test<int64_t>(    14, 2,              19'968, day14::part2);
		test::test<int64_t>(    15, 1,             148'737, day15::part1);
		test::test<int64_t>(    15, 2,           2'353'212, day15::part2);
		test::test<std::string>(16, 1, "10010010110011010", day16::part1);
		test::test<std::string>(16, 2, "01010100101011100", day16::part2);
		test::test<std::string>(17, 1,        "DDRUDLRRRD", day17::part1);
		test::test<int64_t>(    17, 2,                 398, day17::part2);
		test::test<int64_t>(    18, 1,               1'978, day18::part1);
		test::test<int64_t>(    18, 2,          20'003'246, day18::part2);
		test::test<int64_t>(    19, 1,           1'834'903, day19::part1);
		test::test<int64_t>(    19, 2,           1'420'280, day19::part2);
		test::test<int64_t>(    20, 1,          22'887'907, day20::part1);
		test::test<int64_t>(    20, 2,                 109, day20::part2);
		test::test<std::string>(21, 1,          "fdhbcgea", day21::part1);
		test::test<std::string>(21, 2,          "egfbcadh", day21::part2);
		test::test<int64_t>(    22, 1,               1'043, day22::part1);
		test::test<int64_t>(    22, 2,                 185, day22::part2);
		test::test<int64_t>(    23, 1,              11'736, day23::part1);
		test::test<int64_t>(    23, 2,         479'008'296, day23::part2);
		//test::test<int64_t>(    24, 1,                   0, day24::part1);
		//test::test<int64_t>(    24, 2,                   0, day24::part2);
		//test::test<int64_t>(    25, 1,                   0, day25::part1);
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}

	system("pause");
	return 0;
}
