#pragma once
#include "SFML/Graphics.hpp"
#include <memory>

struct Point {
    int x, y;
    friend const Point operator+(const Point& left, const Point& right);
    friend bool operator==(const Point& left, const Point& right);
    friend bool operator!=(const Point& left, const Point& right);
};

class Knight;
class Monster;
class Princess;
class Magician;
class Fireball;

class GameObject {
public:
    GameObject(const Point& position, const std::shared_ptr<sf::Sprite> sprite,
        const int& health, const int& damage);
    void draw(sf::RenderWindow& window);
    Point getPosition();
    int getHealth();
    int getDamage();
    void hit(const int& damageSize);
    void changeDamage(const int& incSize);
    virtual void move(const Point& offset, std::vector<std::shared_ptr<GameObject>>& objects,
        const std::vector<std::string> map) = 0;
    // true - object can move to this point | false - can't
    virtual bool collide(GameObject& object) = 0;
    virtual bool collide(Knight& knight) = 0;
    virtual bool collide(Monster& monster) = 0;
    virtual bool collide(Princess& princess) = 0;
    virtual bool collide(Magician& magician) = 0;
    virtual bool collide(Fireball& fireball) = 0;
protected:
    Point position;
    int health, maxHealth, damage;
private:
    std::shared_ptr<sf::Sprite> sprite;
};
