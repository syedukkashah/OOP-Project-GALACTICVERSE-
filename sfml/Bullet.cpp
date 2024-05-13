#include "Bullet.h"
void Bullet::update(Time deltaTime) {
    getBullet()->setPosition(getBullet()->getPosition().x, getBullet()->getPosition().y - deltaTime.asSeconds());
}
bool Bullet::isOffScreen() {
    return getBullet()->getPosition().y < 0;
}