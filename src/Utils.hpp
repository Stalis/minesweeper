#pragma once

#include <iostream>
#include <vector>
#include <functional>

#ifdef WIN32
#include <windows.h>
#endif

namespace Utils
{
static inline void clear_screen()
	{
#ifdef WIN32
		std::system("cls");
#else
		std::system("clear");
#endif
    }

template <typename T>
static inline std::vector<T> tail(std::vector<T> vec) {
    return std::vector<T>(vec.begin() + 1, vec.end());
}


template<typename T, typename U>
static std::vector<U> map(const std::vector<T>& vector, std::function<U(const T&)> functor)
{
	std::vector<U> res{};
	for (auto& item : vector)
	{
		res.push_back(functor(item));
	}
	return res;
}

template<typename T>
static std::vector<T> filter(const std::vector<T>& vector, std::function<bool(const T&)> predicate)
{
	std::vector<T> res{};
	for (auto& item : vector)
	{
		if (predicate(item))
		{
			res.push_back(item);
		}
	}
	return res;
}

template<typename T>
static T reduce(const std::vector<T>& vector, std::function<T(const T&, const T&)> functor)
{
	T res{};
	for (auto& item : vector)
	{
		res = functor(res, item);
	}
	return res;
}
}