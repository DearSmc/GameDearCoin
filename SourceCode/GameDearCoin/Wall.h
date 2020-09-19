#pragma once
#include "AllInclude.h"
#include "player.h"
class Wall
{
public:
	Wall();
	~Wall();

	void draw(sf::RenderWindow& window);

	sf::FloatRect getGlobalBounds(int index);
	void setPosition(float x, float y, int index);
	sf::Vector2f getPosition(int index);
	void loadPosition(int& state);
	size_t  HowMuch();

	void update(Player* player);
	sf::Vector2f giveDirection(int index);
	

private:
	unsigned int nWall;
	sf::RectangleShape block;
	std::vector<sf::RectangleShape> wall;

	sf::Vector2f direction;
	std::vector<sf::Vector2f> distance;
	std::vector<sf::Vector2f> dirVector;
	

};

