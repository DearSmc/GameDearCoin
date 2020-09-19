#include "Door.h"

Door::Door(int &state)
{
	this->nowState = &state;
	door.setSize(sf::Vector2f(90.f,100.f));
	door.setFillColor(sf::Color::Cyan);
	for (int i = 0; i < ndoor; i++)
	{
		doorVector.push_back(door);	
	}
	doorVector[0].setPosition(94 * 2-3, -1730);
	doorVector[1].setPosition(94 * 8-8, -1730);
	doorVector[2].setPosition(94 * 14+5, -1730);
}

Door::~Door()
{
}

void Door::draw(sf::RenderWindow& window)
{
	if (ever)
	{
		if (*nowState == 3)
		{
			doorVector[0].setPosition(710, -800);
			doorVector[1].setPosition(790, -800);
			doorVector[2].setPosition(794, -800);
			ever = false;
		}
	}
	else
	{
		doorVector[0].setPosition(94 * 2 - 3, -1730);
		doorVector[1].setPosition(94 * 8 - 8, -1730);
		doorVector[2].setPosition(94 * 14 + 5, -1730);
		ever = true;
	}

	for(int i = 0; i < ndoor; i++)
		window.draw(doorVector[i]);
}

void Door::setOrigin(int distance)
{
	for (int i = 0; i < ndoor; i++)
	{
		doorVector[i].setPosition(doorVector[i].getPosition().x, doorVector
			[i].getPosition().y - distance);
	}
}

sf::FloatRect Door::getGlobalBounds(int index)
{
	return doorVector[index].getGlobalBounds();
}

void Door::setPosition(float x, float y, int index)
{
	doorVector[index].setPosition(x, y);
}

sf::Vector2f Door::getPosition(int index)
{
	return doorVector[index].getPosition();
}

size_t Door::HowMuch()
{
	return doorVector.size();
}
