#pragma once
#include "iostream"
#include "SFML/Graphics.hpp"
using namespace sf;
class Bullet {
	Sprite bullet;
    public:
	Bullet(Texture* texture, Vector2f position)
	{
		bullet.setTexture(*texture);
		bullet.setScale(0.5f, 0.5f);
		bullet.setPosition(position);
	}
	void update(Time deltaTime);
	bool isOffScreen();
	Sprite* getBullet() {return &bullet;}
	~Bullet(){}
};



