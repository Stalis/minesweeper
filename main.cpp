#include "src/Game.hpp"

int main() {
    Game game{};

	game.init();
    for (;;) {
        game.update();
        if (game.isExitState())
            break;
    }
    return 0;
}