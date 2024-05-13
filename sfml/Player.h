#pragma once
#include "Ship.h"
#include "Bullet.h"
#include "PowerBlast.h"
#include <vector>
using namespace std;
using namespace sf;
class Player : public Ship {
    vector<Bullet> bullets;
    PowerBlast powerUp;
public:
    Player(Texture* texture, Texture* blastTexture);
    PowerBlast* getPowerUp();
    vector<Bullet>& getBullets();
    void update(Time deltaTime, RenderWindow* window);
};


