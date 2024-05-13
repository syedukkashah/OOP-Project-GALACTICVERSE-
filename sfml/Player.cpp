#include "Player.h"
using namespace sf;
Player::Player(Texture* texture, Texture* blastTexture) : Ship(texture), powerUp(blastTexture) {
    Max_HP = 10;
    HP = Max_HP;
    shape.setScale(0.3, 0.3);
}
PowerBlast* Player::getPowerUp() {
    return &powerUp;
}
vector<Bullet>& Player::getBullets() {
    return bullets;
}
void Player::update(Time deltaTime, RenderWindow* window) {
    float speed = 100.0f;
    //collision with window
    if (getSprite()->getPosition().x <= 0) getSprite()->setPosition(0.f, getSprite()->getPosition().y); //left
    if (getSprite()->getPosition().x >= window->getSize().x - getSprite()->getGlobalBounds().width)getSprite()->setPosition(window->getSize().x - getSprite()->getGlobalBounds().width, getSprite()->getPosition().y); //right
    if (getSprite()->getPosition().y <= 0) getSprite()->setPosition(getSprite()->getPosition().x, 0.f); //top
    if (getSprite()->getPosition().y >= window->getSize().y - getSprite()->getGlobalBounds().height)getSprite()->setPosition(getSprite()->getPosition().x, window->getSize().y - getSprite()->getGlobalBounds().height); //bottom

   auto it = bullets.begin();
    while (it != bullets.end()) {
        it->update(deltaTime);
        if (it->isOffScreen()) {
            it = bullets.erase(it);
        }
        else {
            ++it;
        }
    }
}