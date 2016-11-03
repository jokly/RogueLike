#include "Knight.hpp"
#include "Monster.hpp"
#include "Magician.hpp"
#include "Fireball.hpp"

Knight::Knight(const Point& position, const std::shared_ptr<sf::Sprite> sprite,
   const int& health, const int& damage) : GameObject(position, sprite, health, damage) {}

void Knight::move(const Point& offset, std::vector<std::shared_ptr<GameObject>>& objects,
    const std::vector<std::string> map)
{
    Point toPos = position + offset;
    bool wasCollide = false;

    for (int i = 0; i < objects.size(); ++i) {
        if (toPos == objects[i]->getPosition())
            if (!objects[i]->collide(*this)) {
                wasCollide = true;
            }
    }

    if (!wasCollide && map[toPos.y][toPos.x] == '.')
        position = toPos;
}

void Knight::heal(int healSize) {
    health += healSize;
    health = health > maxHealth ? maxHealth : health;
}

void Knight::castFireball(std::vector<std::shared_ptr<GameObject>>& objects,
    const std::vector<std::string> map, const int& dx, const int& dy)
{
    objects.push_back(std::make_shared<Fireball>(position, 60, dx, dy));
    objects.back()->move(Point{dx, dy}, objects, map);
}

bool Knight::collide(GameObject& object) {
    return object.collide(*this);
}

bool Knight::collide(Knight& knight) {
    return false;
}

bool Knight::collide(Monster& monster) {
   health -= monster.getDamage();
   return false;
}

bool Knight::collide(Princess& princess) {
    return false;
}

bool Knight::collide(Magician& magician) {
    health -= magician.getDamage();
    return false;
}

bool Knight::collide(Fireball& fireball) {
    health -= fireball.getDamage();
    fireball.hit(fireball.getHealth());
    return true;
}
