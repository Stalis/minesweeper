//
// Created by Stanislav on 19/10/2019.
//

#pragma once

enum class CommandType
{
	OPEN,
	MARK,
	UNMARK,
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
	static Command Mark(int x, int y);
	static Command Unmark(int x, int y);
};
