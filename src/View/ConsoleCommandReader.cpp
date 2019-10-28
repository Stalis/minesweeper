//
// Created by Stanislav on 28/10/2019.
//

#include "ConsoleCommandReader.hpp"
#include "src/Vector2.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

template<typename T>
static inline std::vector<T> tail(std::vector<T> vec)
{
	return std::vector<T>(vec.begin() + 1, vec.end());
}

static inline Vector2 twoWordsCoord(std::string& first, std::string& second, ConsoleCommandReader::TConverter converter);
static inline Vector2 oneWordCoord(std::string& word, ConsoleCommandReader::TConverter converter);
static inline Vector2 parseCoord(std::vector<std::string>& vec, ConsoleCommandReader::TConverter converter);
static const Vector2 INVALID_COORD = Vector2(-1, -1);

Command ConsoleCommandReader::convertToCommand(const std::string& input) const
{
	if (input.length() == 0)
	{
		return Command::INVALID;
	}
	std::vector<std::string> words{};
	std::stringstream stream(input);
	{
		std::string word;
		while (std::getline(stream, word, ' '))
		{
			words.push_back(word);
		}
	}

	for (auto& word : words)
	{
		std::cout << word << std::endl;
	}

	if (words.at(0) == "exit")
	{
		return Command::EXIT;
	}

	int x = -1, y = -1;
	Vector2 res{ INVALID_COORD };

	if (words.at(0) == "open" || words.at(0) == "o")
	{
		res = parseCoord(tail(words), _converter);

		if (res != INVALID_COORD)
		{
			return Command::Open(res.x, res.y);
		}
	}

	if (words.at(0) == "mark" || words.at(0) == "m")
	{
		res = parseCoord(tail(words), _converter);

		if (res != INVALID_COORD)
		{
			return Command::Mark(res.x, res.y);
		}
	}

	if (words.at(0) == "unmark" || words.at(0) == "um")
	{
		res = parseCoord(tail(words), _converter);

		if (res != INVALID_COORD)
		{
			return Command::Unmark(res.x, res.y);
		}
	}

	res = parseCoord(words, _converter);
	if (res != INVALID_COORD)
	{
		return Command::Open(res.x, res.y);
	}

	return Command::INVALID;
}

static inline Vector2 twoWordsCoord(std::string& first, std::string& second, ConsoleCommandReader::TConverter converter)
{
	int x, y;
	if (converter(first, x))
	{
		try
		{
			y = std::stoi(second) - 1;
			return Vector2(x, y);
		} catch (std::invalid_argument&)
		{}
	}
	return INVALID_COORD;
}
static inline Vector2 oneWordCoord(std::string& word, ConsoleCommandReader::TConverter converter)
{
	int x, y;
	if (word.length() >= 2)
	{
		auto substr = word.substr(0, 1);
		if (converter(substr, x))
		{
			try
			{
				y = std::stoi(word.substr(1, 1)) - 1;
				return Vector2(x, y);
			} catch (std::invalid_argument&)
			{}
		}
	}
	return INVALID_COORD;
}

inline Vector2 parseCoord(std::vector<std::string>& words, ConsoleCommandReader::TConverter converter)
{
	auto res = INVALID_COORD;

	if (words.size() >= 1)
	{
		res = oneWordCoord(words.at(0), converter);
	}

	if (res == INVALID_COORD && words.size() >= 2)
	{
		res = twoWordsCoord(words.at(0), words.at(1), converter);
	}
	return res;
}
