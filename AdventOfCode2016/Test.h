#pragma once

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>

#include <Windows.h>


namespace test
{
	template<typename T>
	bool test(const uint8_t day, const uint8_t part, const T expected, std::function<T()> func)
	{
		const auto start = std::chrono::high_resolution_clock::now();
		const auto result = func();
		const auto time = std::chrono::high_resolution_clock::now() - start;
		const auto same = result == expected;
		const auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO info;
		WORD attributes = 7;
		if (GetConsoleScreenBufferInfo(handle, &info))
		{
			attributes = info.wAttributes;
		}

		auto dayString = std::to_string(day);
		if (day < 10) dayString = '0' + dayString;
		auto partSring = std::to_string(part);
		if (part < 10) partSring = '0' + partSring;

		const auto message = dayString + '|' + partSring + " time: " + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(time).count()) + " result: ";

		if (same)
		{
			SetConsoleTextAttribute(handle, 10);
			std::cout << message << result << ") status: OK\n";
			SetConsoleTextAttribute(handle, attributes);
		}
		else
		{
			SetConsoleTextAttribute(handle, 12);
			std::cout << message << result << " expected: " << expected << ") status: FAIL\n";
			SetConsoleTextAttribute(handle, attributes);
		}

		return same;
	}

	template<typename T>
	bool bench(const uint8_t day, const uint8_t part, const size_t repetitions, const T expected, std::function<T()> func)
	{
		std::vector<T> results;
		std::vector<int64_t> times;

		for (size_t i = 0; i < repetitions; ++i)
		{
			const auto start = std::chrono::high_resolution_clock::now();
			const auto result = func();
			times.emplace_back(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count());
			results.emplace_back(result);
		}

		auto allOk = true;

		for (const auto& result : results)
		{
			if (result != expected)
			{
				allOk = false;
			}
		}

		std::string status;

		if (allOk)
		{
			status = "OK";
		}
		else
		{
			status = "FAIL";
		}

		const auto average = std::accumulate(times.begin(), times.end(), static_cast<int64_t>(0)) / times.size();

		auto dayString = std::to_string(day);
		if (day < 10) dayString = '0' + dayString;
		auto partSring = std::to_string(part);
		if (part < 10) partSring = '0' + partSring;

		std::cout << dayString << '|' << partSring << " bench status: " << status << " time: " << average << "\n";

		return allOk;
	}
}
