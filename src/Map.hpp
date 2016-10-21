#pragma once
#include "GameObject.hpp"
#include <memory>
#include <vector>
#include <string>
                    
class Map {
public:
    Map(const std::string& mapFile);
    void draw(sf::RenderWindow& window);
    std::vector<std::shared_ptr<GameObject>>& getObjects();
    std::vector<std::string>& getMap();
    std::shared_ptr<GameObject> getPrincess();
private:
    std::vector<std::shared_ptr<GameObject>> objects;
    std::shared_ptr<GameObject> princess;
    std::vector<std::string> map;
    sf::Texture tileSet;
    std::shared_ptr<sf::Sprite> empty, wall;
};
