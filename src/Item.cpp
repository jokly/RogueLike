#include "Item.hpp"

Item::Item(const Point& position, const std::shared_ptr<sf::Sprite> sprite)
    : GameObject(position, sprite, 1, 0) {}

void Item::move(const Point& offset, std::vector<std::shared_ptr<GameObject>>& objects,
    const std::vector<std::string> map) {}

bool Item::collide(GameObject& object) {
    return object.collide(*this);
}

bool Item::collide(Knight& knight) {
    health = 0;
    return true;
}

bool Item::collide(Monster& monster) {
    return false;
}

bool Item::collide(Princess& princess) {
    return false;
}

bool Item::collide(Magician& magician) {
    return false;
}

bool Item::collide(Fireball& fireball) {
    health = 0;
    return true;
}
