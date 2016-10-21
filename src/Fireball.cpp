#include "Fireball.hpp"
#include "Knight.hpp"

std::shared_ptr<sf::Sprite> Fireball::staticSprite;

Fireball::Fireball(const Point& position, const int& damage, const int& dx, const int& dy) :
    GameObject(position, Fireball::staticSprite, 1, damage), dx(dx), dy(dy) {}

void Fireball::setSprite(const std::shared_ptr<sf::Sprite> sprite) {
    Fireball::staticSprite = sprite;
}

void Fireball::move(const Point& offset, std::vector<std::shared_ptr<GameObject>>& objects,
    const std::vector<std::string> map)
{
    Point toPos = position + Point{dx, dy};
    bool wasCollide = false;

    for (int i = 0; i < objects.size(); ++i) {
        if (toPos == objects[i]->getPosition())
            if (!objects[i]->collide(*this)) {
                wasCollide = true;
            }
    }

    if (!wasCollide && map[toPos.y][toPos.x] == '.')
        position = toPos;
    else if (map[toPos.y][toPos.x] == '#')
        health = 0;
}

bool Fireball::collide(GameObject& object) {
    return object.collide(*this);
}

bool Fireball::collide(Knight& knight) {
    health = 0;
    knight.hit(damage);
    return false;
}

bool Fireball::collide(Monster& monster) {
    return false;
}

bool Fireball::collide(Princess& princess) {
    return false;
}

bool Fireball::collide(Magician& magician) {
    return false;
}

bool Fireball::collide(Fireball& fireball) {
    health = 0;
    return false;
}
