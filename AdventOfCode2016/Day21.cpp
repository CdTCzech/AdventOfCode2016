#include "Day21.h"

#include "FileReader.h"

#include <iterator>
#include <sstream>

namespace day21
{
	std::string part1()
	{
		std::string result = "abcdefgh";

		for (const auto& line : getLineByLine("day21.txt"))
		{
			std::istringstream iss(line);
			std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };

			if (tokens[0][0] == 's' && tokens[1][0] == 'p')
			{
				const auto X = std::stoll(tokens[2]);
				const auto Y = std::stoll(tokens[5]);
				std::swap(result[X], result[Y]);
			}
			else if (tokens[0][0] == 's' && tokens[1][0] == 'l')
			{
				const auto X = result.find(tokens[2][0]);
				const auto Y = result.find(tokens[5][0]);
				std::swap(result[X], result[Y]);
			}
			else if (tokens[0][0] == 'r' && tokens[1][0] == 'l')
			{
				const auto X = std::stoll(tokens[2]) % result.size();
				std::rotate(result.begin(), result.begin() + X, result.end());
			}
			else if (tokens[0][0] == 'r' && tokens[1][0] == 'r')
			{
				const auto X = std::stoll(tokens[2]) % result.size();
				std::rotate(result.begin(), result.begin() + (result.size() - X), result.end());
			}
			else if (tokens[0][0] == 'r' && tokens[1][0] == 'b')
			{
				auto X = result.find(tokens[6][0]);
				X += (X >= 4) ? 2 : 1;
				X = X % result.size();
				std::rotate(result.begin(), result.begin() + (result.size() - X), result.end());
			}
			else if (tokens[0][0] == 'r' && tokens[1][0] == 'p')
			{
				const auto X = std::stoll(tokens[2]);
				const auto Y = std::stoll(tokens[4]);
				std::reverse(result.begin() + X, result.begin() + Y + 1);
			}
			else if (tokens[0][0] == 'm' && tokens[1][0] == 'p')
			{
				const auto X = std::stoll(tokens[2]);
				const auto Y = std::stoll(tokens[5]);
				const auto temp = result[X];

				result.erase(X, 1);
				result.insert(result.begin() + Y, temp);
			}
			else
			{
				_ASSERT(false);
			}
		}

		return result;
	}

	std::string part2()
	{
		std::string result = "fbgdceah";
		std::vector<std::string> lines;

		for (const auto& line : getLineByLine("day21.txt"))
		{
			lines.push_back(line);
		}

		std::reverse(lines.begin(), lines.end());

		for (const auto& line : lines)
		{
			std::istringstream iss(line);
			std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };

			if (tokens[0][0] == 's' && tokens[1][0] == 'p')
			{
				const auto X = std::stoll(tokens[2]);
				const auto Y = std::stoll(tokens[5]);
				std::swap(result[Y], result[X]);
			}
			else if (tokens[0][0] == 's' && tokens[1][0] == 'l')
			{
				const auto X = result.find(tokens[2][0]);
				const auto Y = result.find(tokens[5][0]);
				std::swap(result[Y], result[X]);
			}
			else if (tokens[0][0] == 'r' && tokens[1][0] == 'l')
			{
				const auto X = std::stoll(tokens[2]) % result.size();
				std::rotate(result.begin(), result.begin() + (result.size() - X), result.end());
			}
			else if (tokens[0][0] == 'r' && tokens[1][0] == 'r')
			{
				const auto X = std::stoll(tokens[2]) % result.size();
				std::rotate(result.begin(), result.begin() + X, result.end());
			}
			else if (tokens[0][0] == 'r' && tokens[1][0] == 'b')
			{
				auto X = result.find(tokens[6][0]);
				X += (X != 0 && X % 2 == 0) ? result.size() : 0;
				X = (X / 2 + 1) % result.size();
				std::rotate(result.begin(), result.begin() + X, result.end());
			}
			else if (tokens[0][0] == 'r' && tokens[1][0] == 'p')
			{
				const auto X = std::stoll(tokens[2]);
				const auto Y = std::stoll(tokens[4]);
				std::reverse(result.begin() + X, result.begin() + Y + 1);
			}
			else if (tokens[0][0] == 'm' && tokens[1][0] == 'p')
			{
				const auto X = std::stoll(tokens[2]);
				const auto Y = std::stoll(tokens[5]);
				const auto temp = result[Y];

				result.erase(Y, 1);
				result.insert(result.begin() + X, temp);
			}
			else
			{
				_ASSERT(false);
			}
		}

		return result;
	}
}  // namespace day21