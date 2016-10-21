#pragma once
#include "Item.hpp"

class Sword : public Item {
public:
    Sword(const Point& position, const std::shared_ptr<sf::Sprite> sprite, const int& incDamage);
    bool collide(Knight& knight) override;
private:
    int incDamage;
};
