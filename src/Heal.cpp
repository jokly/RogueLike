#include "Heal.hpp"
#include "Knight.hpp"

Heal::Heal(const Point& position, const std::shared_ptr<sf::Sprite> sprite, const int& healSize) :
    Item(position, sprite), healSize(healSize) {}

bool Heal::collide(Knight& knight) {
    knight.heal(healSize);
    return Item::collide(knight);
}
