#include "GameObject.hpp"
#include "Config.hpp"

const Point operator+(const Point& left, const Point& right) {
    return Point{left.x + right.x, left.y + right.y};
}

bool operator==(const Point& left, const Point& right) {
    return left.x == right.x && left.y == right.y;
}

bool operator!=(const Point& left, const Point& right) {
    return left.x != right.x || left.y != right.y;
}

GameObject::GameObject(const Point& position, std::shared_ptr<sf::Sprite> sprite, const int& health,
    const int& damage) : position(position), sprite(sprite), health(health), maxHealth(health), damage(damage) 
{}

void GameObject::draw(sf::RenderWindow& window) {
    Config& config = Config::Instance();
    sprite->setPosition(sf::Vector2f(position.x * config.spriteSize,
                position.y * config.spriteSize));

    window.draw(*sprite);
}

Point GameObject::getPosition() {
    return position;
}

int GameObject::getHealth() {
    return health;
}

int GameObject::getDamage() {
    return damage;
}

void GameObject::hit(const int& damageSize) {
    if (damageSize > 0)
        health -= damageSize;
}

void GameObject::changeDamage(const int& incSize) {
    damage += incSize;
}
