#include "Game.hpp"
#include "Config.hpp"

int main() {
    Config& config = Config::Instance();
    config.loadConfig("../res/config.json");

    while (true) {
        Game game(sf::VideoMode(config.windowWidth, config.windowHeight),
                config.windowName, config.mapPath);
        if (game.startGame() == WindowState::Close)
            break;
    }

    return 0;
}
