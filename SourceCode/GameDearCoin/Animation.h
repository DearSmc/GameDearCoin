#pragma once
#include "AllInclude.h"

class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();

	void Update(int row, float deltaTime , bool faceRight);

public:
	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount; 
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
};

