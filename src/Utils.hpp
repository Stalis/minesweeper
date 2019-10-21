#pragma once

#include <iostream>
#ifdef WIN32
#include <windows.h>
#endif

namespace Utils
{
	void clear_screen()
	{
#ifdef WIN32
		std::system("cls");
#else
		std::system("clear");
#endif
    }
}