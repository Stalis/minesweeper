#pragma once

#include <iostream>
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
}