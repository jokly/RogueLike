#pragma once
#include "GameObject.hpp"

class Monster : public GameObject {
public:
    Monster(const Point& position, const std::shared_ptr<sf::Sprite> sprite,
        const int& health, const int& damage);
    void move(const Point& offset, std::vector<std::shared_ptr<GameObject>>& objects,
        const std::vector<std::string> map) override;
    bool collide(GameObject& object) override;
    bool collide(Knight& knight) override;
    bool collide(Monster& monster) override;
    bool collide(Princess& princess) override;
    bool collide(Magician& magician) override;
    bool collide(Fireball& fireball) override;
};
