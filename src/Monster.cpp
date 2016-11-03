#include "Monster.hpp"
#include "Knight.hpp"
#include "Fireball.hpp"
#include <ctime>
#include <cmath>

Monster::Monster(const Point& position, const std::shared_ptr<sf::Sprite> sprite,
    const int& health, const int& damage) : GameObject(position, sprite, health, damage) {}

void Monster::move(const Point& offset, std::vector<std::shared_ptr<GameObject>>& objects,
    const std::vector<std::string> map)
{
    int playerVizible = 5;

    int distToPlayer = sqrt(pow(offset.x - position.x, 2) + pow(offset.y - position.y, 2));
    Point toPos;
    if (distToPlayer <= playerVizible) {
        int dx = offset.x - position.x;
        int dy = offset.y - position.y;
        dx /= dx == 0 ? 1 : abs(dx);
        dy /= dy == 0 ? 1 : abs(dy);
        
        if (dx == 0)
            toPos = position + Point{0, dy};
        else if (dy == 0)
            toPos = position + Point{dx, 0};
        else {
            // 0 - dx, 1 - dy
            int index = rand() % 2;
            toPos = index == 0 ? position + Point{dx, 0} : position + Point{0, dy};
        }
    }
    else {
        Point offsets[] = {Point{1, 0}, Point{-1, 0}, Point{0, 1}, Point{0, -1}};
        srand(time(0));
        int index = rand() % 4;
        toPos = position + offsets[index];
    }

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

bool Monster::collide(GameObject& object) {
    return object.collide(*this);
}

bool Monster::collide(Knight& knight) {
    health -= knight.getDamage();
    return false;
}

bool Monster::collide(Monster& monster) {
    return false;
}

bool Monster::collide(Princess& princess) {
    return false;
}

bool Monster::collide(Magician& magician) {
    return false;
}

bool Monster::collide(Fireball& fireball) {
    fireball.hit(fireball.getHealth());
    health -= fireball.getDamage();
    return false;
}
