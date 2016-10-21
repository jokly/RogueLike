#include "Sword.hpp"
#include "Knight.hpp"

Sword::Sword(const Point& position, const std::shared_ptr<sf::Sprite> sprite, const int& incDamage) :
    Item(position, sprite), incDamage(incDamage) {}

bool Sword::collide(Knight& knight) {
    knight.changeDamage(incDamage); 
    return Item::collide(knight);
}
