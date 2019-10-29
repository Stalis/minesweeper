#include "src/Game.hpp"
#include <iostream>
#include <string>

void playGame()
{
	Game game{};

	game.init();
	for (;;)
	{
		game.update();
		if (game.isExitState())
			break;
	}
}

int main() {
__retry:
	playGame();

	std::cout << "Retry? [y/N]: " << std::flush;
	std::string answer{};
	std::getline(std::cin, answer);
	if (answer == "y")
	{
		goto __retry;
	}

    return 0;
}