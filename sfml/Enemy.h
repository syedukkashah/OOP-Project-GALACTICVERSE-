#pragma once
#include "Ship.h"
using namespace sf;
class Enemy : public Ship {
public:
    Enemy(Texture* texture, Vector2u windowSize);
    void takeDamage();
    void update(Time deltaTime);
};

