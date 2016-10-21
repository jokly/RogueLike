#include "Game.hpp"

int main() {
    while (true) {
        Game game(sf::VideoMode(800, 600), "RogueLike", "../res/map.txt");
        if (game.startGame() == WindowState::Close)
            break;
    }

    return 0;
}
