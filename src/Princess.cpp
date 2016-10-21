#include "Princess.hpp"
#include "Fireball.hpp"

Princess::Princess(const Point& position, const std::shared_ptr<sf::Sprite> sprite)
    : GameObject(position, sprite, 1, 0) {}

void Princess::move(const Point& offset, std::vector<std::shared_ptr<GameObject>>& objects,
    const std::vector<std::string> map) {}

bool Princess::collide(GameObject& object) {
    return object.collide(*this);
}

bool Princess::collide(Knight& knight) {
    health = 0;
    return true;
}

bool Princess::collide(Monster& monster) {
    return false;
}

bool Princess::collide(Princess& princess) {
    return false;
}

bool Princess::collide(Magician& magician) {
    return false;
}

bool Princess::collide(Fireball& fireball) {
    fireball.hit(fireball.getHealth());
    return false;
}
