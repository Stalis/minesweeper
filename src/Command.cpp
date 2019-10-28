#include "Command.hpp"

Command Command::EXIT = Command{ CommandType::EXIT };
Command Command::INVALID = Command{ CommandType::INVALID };

Command Command::Open(int x, int y)
{
	return Command{ CommandType::OPEN, x, y };
}

Command Command::Mark(int x, int y)
{
	return Command{ CommandType::MARK, x, y };
}

Command Command::Unmark(int x, int y)
{
	return Command{ CommandType::UNMARK, x, y };
}
