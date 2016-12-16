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
    Config& config = Config::Instance();
    std::ifstream file(config.mapPath);
    
    std::string line;
    while (!file.eof()) {
        std::getline(file, line);
        map.push_back(line);
    }
    map.pop_back();
    file.close();

    tileSet.loadFromFile(config.tileSetPath);
    
    empty = std::make_shared<sf::Sprite>(tileSet);
    empty->setTextureRect(sf::IntRect(0, 0, config.spriteSize, config.spriteSize));
    empty->setColor(sf::Color(0, 255, 0));

    wall = std::make_shared<sf::Sprite>(tileSet); 
    wall->setTextureRect(sf::IntRect(16, 0, config.spriteSize, config.spriteSize));
    
    auto knightSp = std::make_shared<sf::Sprite>(tileSet);
    knightSp->setTextureRect(sf::IntRect(0, 16, config.spriteSize, config.spriteSize));

    auto monsterSp = std::make_shared<sf::Sprite>(tileSet);
    monsterSp->setTextureRect(sf::IntRect(16, 16, config.spriteSize, config.spriteSize));

    auto magicianSp = std::make_shared<sf::Sprite>(tileSet);
    magicianSp->setTextureRect(sf::IntRect(48, 16, config.spriteSize, config.spriteSize));

    auto princessSp = std::make_shared<sf::Sprite>(tileSet);
    princessSp->setTextureRect(sf::IntRect(32, 16, config.spriteSize, config.spriteSize));

    auto healSp = std::make_shared<sf::Sprite>(tileSet);
    healSp->setTextureRect(sf::IntRect(32, 0, config.spriteSize, config.spriteSize));

    auto swordSp = std::make_shared<sf::Sprite>(tileSet);
    swordSp->setTextureRect(sf::IntRect(64, 0, config.spriteSize, config.spriteSize));

    auto fireballSp = std::make_shared<sf::Sprite>(tileSet);
    fireballSp->setTextureRect(sf::IntRect(48, 0, config.spriteSize, config.spriteSize));
    fireballSp->setColor(sf::Color(171, 7, 7));
    Fireball::setSprite(fireballSp);

    std::shared_ptr<GameObject> player;
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].length(); ++j) {
            bool isObject = false;

            if (map[i][j] == config.objects["knight"]) {
                player = std::make_shared<Knight>(Point{j, i}, knightSp, 100, 20);
                objects.push_back(player);
                isObject = true;
            }
            else if (map[i][j] == config.objects["monster"]) {
                objects.push_back(std::make_shared<Monster>(Point{j, i}, monsterSp, 60, 10));
                isObject = true;
            }
            else if (map[i][j] == config.objects["magician"]) {
                objects.push_back(std::make_shared<Magician>(Point{j, i}, magicianSp, 20, 10));
                isObject = true;
            }
            else if (map[i][j] == config.objects["heal"]) {
                objects.push_back(std::make_shared<Heal>(Point{j, i}, healSp, 20));
                isObject = true;
            }
            else if (map[i][j] == config.objects["princess"]) {
                princess = std::make_shared<Princess>(Point{j, i}, princessSp);
                objects.push_back(princess);
                isObject = true;
            }
            else if (map[i][j] == config.objects["sword"]) {
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
    Config& config = Config::Instance();

    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].length(); ++j) {
            if (map[i][j] == config.objects["empty"]) {
                empty->setPosition(sf::Vector2f(j * config.spriteSize, i * config.spriteSize));
                window.draw(*empty);
            }
            else if (map[i][j] == config.objects["wall"]) { 
                wall->setPosition(sf::Vector2f(j * config.spriteSize, i * config.spriteSize));
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
