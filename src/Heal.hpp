#pragma once
#include "Item.hpp"

class Heal : public Item {
public:
    Heal(const Point& position, const std::shared_ptr<sf::Sprite> sprite, const int& healSize);
    bool collide(Knight& knight) override;
private:
    int healSize;
};
