#include "Ship.h"
using namespace sf;
Ship::Ship(Texture* texture) {
    this->shape.setTexture(*texture);
    this->Max_HP = 10;
    this->HP = Max_HP;
}
Ship::~Ship() {}
Sprite* Ship::getSprite() {
    return &shape;
}
int Ship::getHP() const {
    return HP;
}
int Ship::getMaxHP() const {
    return Max_HP;
}
void Ship::setHP(int hp) {
    this->HP = hp;
}
void Ship::setMaxHP(int maxHp) {
    this->Max_HP = maxHp;
}
