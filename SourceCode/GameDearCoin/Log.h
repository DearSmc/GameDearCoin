#pragma once
#include "AllInclude.h"

class Log
{
public: 
	Log(float speed);
	~Log();
	void draw(sf::RenderWindow& window);
	void insertLog();
	void update(float deltaTime);

	size_t HowMuch();
	sf::Vector2f getPosition(int index);
	void setPosition(float x,float y,int index);
	sf::FloatRect getGlobalBounds(int index);
	sf::Vector2f movement;
	void clear(int state);

private:
	float speed;

	sf::RectangleShape smallLog;
	sf::RectangleShape bigLog;
	
	std::vector<sf::RectangleShape> logVector;
	
	sf::Texture small;
	sf::Texture big;

	
	
};

