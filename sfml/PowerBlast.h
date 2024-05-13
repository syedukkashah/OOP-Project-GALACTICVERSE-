#pragma once
#include "iostream"
#include "SFML/Graphics.hpp"
using namespace sf;
class PowerBlast
{
    Sprite blast;
    public:
		PowerBlast(Texture* texture)
		{
			blast.setTexture(*texture);
			blast.setScale(0.15, 0.15);
			blast.setPosition(-150.f, -150.f);
	    }
		Sprite* getBlast() {return &blast;}
};

