#pragma once
#include "SFML/Graphics.hpp"
#include "Map.hpp"
#include "GameObject.hpp"
#include <string>

enum class GameState { Game, Win, Lose };
enum class WindowState {Close, Restart};

class Game {
public:
    Game(const sf::VideoMode& videoMode, const std::string& windowName, const std::string& startMapFile);
    WindowState startGame();
private:
    sf::RenderWindow window;
    Map map;
    std::vector<std::shared_ptr<GameObject>> objects;
    std::string getInfoString(const std::shared_ptr<GameObject> gameObject);
};
