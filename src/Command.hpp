//
// Created by Stanislav on 19/10/2019.
//

#pragma once

enum class CommandType
{
	OPEN,
	EXIT,
	INVALID,
};

struct Command
{
	CommandType type;
	int x;
	int y;

	static Command EXIT;
	static Command INVALID;
	static Command Open(int x, int y);
};
