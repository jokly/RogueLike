#include "Magician.hpp"
#include "Knight.hpp"
#include "Fireball.hpp"
#include <cmath>

#define SHOT_DISTANCE 6
#define TIMER 5

Magician::Magician(const Point& position, const std::shared_ptr<sf::Sprite> sprite,
    const int& health, const int& damage) : GameObject(position, sprite, health, damage), fireballTick(0) {}

void Magician::move(const Point& offset, std::vector<std::shared_ptr<GameObject>>& objects,
    const std::vector<std::string> map)
{
    int distance = (int)sqrt(pow(offset.x - position.x, 2) + pow(offset.y - position.y, 2));
    if (distance <= SHOT_DISTANCE && fireballTick == 0) {
        fireballTick = TIMER;
        objects.push_back(std::make_shared<Fireball>(position, 10, -1, 0));
        objects.push_back(std::make_shared<Fireball>(position, 10, 1, 0));
        objects.push_back(std::make_shared<Fireball>(position, 10, 0, -1));
        objects.push_back(std::make_shared<Fireball>(position, 10, 0, 1));
    }
    else if (distance > SHOT_DISTANCE)
        fireballTick = 0;
    else
        --fireballTick;
}

bool Magician::collide(GameObject& object) {
    return object.collide(*this);
}

bool Magician::collide(Knight& knight) {
    health -= knight.getDamage(); 
}

bool Magician::collide(Monster& monster) {
    return false;
}

bool Magician::collide(Princess& princess) {
    return false;
}

bool Magician::collide(Magician& magician) {
    return false;
}

bool Magician::collide(Fireball& fireball) {
    fireball.hit(fireball.getHealth());
    return false;
}
