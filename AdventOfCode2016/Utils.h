#pragma once

#include <string>


namespace utils
{
	class AoCException : public std::exception
	{
	public:
		AoCException(const std::string& what, const std::string& file, const int line) : m_what("!!! EXCEPTION !!!\nFile: " + file + "\nLine: " + std::to_string(line) + "\nError: " + what)
		{
		}

		const char* what() const override
		{
			return m_what.c_str();
		}

	private:
		std::string m_what;
	};
}
