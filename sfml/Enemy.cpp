#include "Enemy.h"
using namespace sf;
Enemy::Enemy(Texture* texture, Vector2u windowSize) : Ship(texture) {
    Max_HP = rand() % 3 + 1;
    HP = Max_HP;
    shape.setScale(0.4, 0.4);
    shape.setPosition(windowSize.x - shape.getGlobalBounds().width, rand() % (int)(windowSize.y - (shape.getGlobalBounds().height*1.5f)));
}
void Enemy::takeDamage() { HP--; }
void Enemy::update(Time deltaTime) {
    shape.setPosition(shape.getPosition().x, shape.getPosition().y + deltaTime.asSeconds());
}