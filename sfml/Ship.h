#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
class Ship{
protected:
    Sprite shape;
    int HP, Max_HP;
public:
    Ship(Texture* texture);
    virtual ~Ship(); // Virtual destructor for proper cleanup
    Sprite* getSprite();
    int getHP() const;
    int getMaxHP() const;
    void setHP(int hp);
    void setMaxHP(int maxHp);
};


