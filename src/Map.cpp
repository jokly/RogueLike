#include "Map.hpp"
#include "Config.hpp"
#include "Knight.hpp"
#include "Monster.hpp"
#include "Magician.hpp"
#include "Princess.hpp"
#include "Heal.hpp"
#include "Sword.hpp"
#include "Fireball.hpp"
#include <fstream>

Map::Map(const std::string& mapFile) {
    std::ifstream file(mapFile);
    
    std::string line;
    while (!file.eof()) {
        std::getline(file, line);
        map.push_back(line);
    }
    map.pop_back();
    file.close();

    tileSet.loadFromFile("../res/tile_set.png");
    
    empty = std::make_shared<sf::Sprite>(tileSet);
    empty->setTextureRect(sf::IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE));
    empty->setColor(sf::Color(0, 255, 0));

    wall = std::make_shared<sf::Sprite>(tileSet); 
    wall->setTextureRect(sf::IntRect(16, 0, SPRITE_SIZE, SPRITE_SIZE));
    
    auto knightSp = std::make_shared<sf::Sprite>(tileSet);
    knightSp->setTextureRect(sf::IntRect(0, 16, SPRITE_SIZE, SPRITE_SIZE));

    auto monsterSp = std::make_shared<sf::Sprite>(tileSet);
    monsterSp->setTextureRect(sf::IntRect(16, 16, SPRITE_SIZE, SPRITE_SIZE));

    auto magicianSp = std::make_shared<sf::Sprite>(tileSet);
    magicianSp->setTextureRect(sf::IntRect(48, 16, SPRITE_SIZE, SPRITE_SIZE));

    auto princessSp = std::make_shared<sf::Sprite>(tileSet);
    princessSp->setTextureRect(sf::IntRect(32, 16, SPRITE_SIZE, SPRITE_SIZE));

    auto healSp = std::make_shared<sf::Sprite>(tileSet);
    healSp->setTextureRect(sf::IntRect(32, 0, SPRITE_SIZE, SPRITE_SIZE));

    auto swordSp = std::make_shared<sf::Sprite>(tileSet);
    swordSp->setTextureRect(sf::IntRect(64, 0, SPRITE_SIZE, SPRITE_SIZE));

    auto fireballSp = std::make_shared<sf::Sprite>(tileSet);
    fireballSp->setTextureRect(sf::IntRect(48, 0, SPRITE_SIZE, SPRITE_SIZE));
    fireballSp->setColor(sf::Color(171, 7, 7));
    Fireball::setSprite(fireballSp);

    std::shared_ptr<GameObject> player;
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].length(); ++j) {
            bool isObject = false;

            if (map[i][j] == 'K') {
                player = std::make_shared<Knight>(Point{j, i}, knightSp, 100, 20);
                objects.push_back(player);
                isObject = true;
            }
            else if (map[i][j] == 'M') {
                objects.push_back(std::make_shared<Monster>(Point{j, i}, monsterSp, 60, 10));
                isObject = true;
            }
            else if (map[i][j] == '@') {
                objects.push_back(std::make_shared<Magician>(Point{j, i}, magicianSp, 20, 10));
                isObject = true;
            }
            else if (map[i][j] == '+') {
                objects.push_back(std::make_shared<Heal>(Point{j, i}, healSp, 20));
                isObject = true;
            }
            else if (map[i][j] == 'P') {
                princess = std::make_shared<Princess>(Point{j, i}, princessSp);
                objects.push_back(princess);
                isObject = true;
            }
            else if (map[i][j] == '!') {
                objects.push_back(std::make_shared<Sword>(Point{j, i}, swordSp, 40));
                isObject = true;
            }       

            if (isObject)
                map[i][j] = '.';
        }
    }

    for (int i = 0; i < objects.size(); ++i)
        if (objects[i] == player) {
            objects.erase(objects.begin() + i);
            break;
        }

    objects.insert(objects.begin(), player);
}

void Map::draw(sf::RenderWindow& window) {
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].length(); ++j) {
            if (map[i][j] == '.') {
                empty->setPosition(sf::Vector2f(j * SPRITE_SIZE, i * SPRITE_SIZE));
                window.draw(*empty);
            }
            else { 
                wall->setPosition(sf::Vector2f(j * SPRITE_SIZE, i * SPRITE_SIZE));
                window.draw(*wall);
            }
        }
    }
}

std::vector<std::shared_ptr<GameObject>>& Map::getObjects() {
    return objects;
}

std::vector<std::string>& Map::getMap() {
    return map;
}

std::shared_ptr<GameObject> Map::getPrincess() {
    return princess;
}
