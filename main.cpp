#include "src/Game.hpp"

int main() {
    Game game{};

    for (;;) {
        game.update();
        if (game.isExitState())
            break;
    }
    return 0;
}