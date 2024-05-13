#pragma once
#include "iostream"
#include "SFML/Graphics.hpp"
using namespace sf;
class Animation{
		Vector2u imageCount;
		Vector2u currentImage;
		float totalTime;
		float switchTime;
	public:
		IntRect uvRect;
		Animation() : imageCount(1,1), switchTime(1.0f), currentImage(1,1), totalTime(0.0f) {} 
		Animation(Texture* texture, Vector2u imageCount, float switchTime)
		{
			this->imageCount = imageCount;
			this->switchTime = switchTime;
			totalTime = 0.0f;
			currentImage.x = 0;
			uvRect.width = texture->getSize().x / float(imageCount.x);
			uvRect.height = texture->getSize().y / float(imageCount.y);
		}
		void Update(int row, float deltaTime)
		{
			currentImage.y = row;
			totalTime += deltaTime;
			if (totalTime >= switchTime)
			{
				totalTime -= switchTime;
				currentImage.x++;
				if (currentImage.x >= imageCount.x)
				{
					currentImage.x = 0;
				}
			}
			uvRect.left = currentImage.x * uvRect.width;
			uvRect.top = currentImage.y * uvRect.height;
		}
};