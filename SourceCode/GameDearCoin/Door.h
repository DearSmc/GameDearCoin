#pragma once
#include "AllInclude.h"
class Door
{
public:
	Door(int& state);
	~Door();
	void draw(sf::RenderWindow& window);

	void setOrigin(int distance);
	//void erase(int index);
	
	sf::FloatRect getGlobalBounds(int index);
	void setPosition(float x, float y, int index);
	sf::Vector2f getPosition(int index);
	size_t  HowMuch();

private:
	sf::RectangleShape door;
	std::vector<sf::RectangleShape> doorVector;
	
	int ndoor = 3;
	int *nowState;
	bool ever = true;
};

