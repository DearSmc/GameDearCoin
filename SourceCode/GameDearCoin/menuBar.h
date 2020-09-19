#pragma once
#include "AllInclude.h"
#include "Collision.h"
class menuBar
{
public:
	menuBar();
	void update(int intScore, int intLife, int intTime);
	void draw(sf::RenderWindow& window);
	void bonusTime(int intTime, float bonusTime);

private:
	sf::Texture scoreTexture;
	sf::Texture lifeTexture;
	sf::Texture timeTexture;

	sf::RectangleShape scoreBar;
	sf::RectangleShape lifeBar;
	sf::RectangleShape timeBar;

	sf::Font font;
	
	sf::Text scoreText;
	sf::Text lifeText;
	sf::Text timeText;
	
	sf::RectangleShape Time;
	sf::Texture TimeTexture;
	sf::Text TimetoEnd;
	int intBonusTime;
	bool check;
	bool state;
	
};

