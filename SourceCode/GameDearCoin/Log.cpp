#include "Log.h"

Log::Log(float speed)
{
	this->speed = speed;
	
	small.loadFromFile("prop/log1.png");
	smallLog.setSize(sf::Vector2f(94.0f, 110.0f));
	smallLog.setTexture(&small);
	smallLog.setPosition(sf::Vector2f(-188.0f, -1630.0f));
	
	big.loadFromFile("prop/log2.png");
	bigLog.setSize(sf::Vector2f(188.0f, 110.0f));
	bigLog.setTexture(&big);
	bigLog.setPosition(sf::Vector2f(-188.0f, -1630.0f));
	
}

Log::~Log()
{
	
}

void Log::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < logVector.size(); i++)
	{
		window.draw(logVector[i]);
	}
	
}

void Log::insertLog()
{
	srand(time(0));
	unsigned int random = (rand()%2)+1;
	if (random == 1)
	{	if(logVector.size()!=0)
			smallLog.setPosition(sf::Vector2f(-188.0f, logVector[0].getPosition().y));
		logVector.push_back(smallLog);
	}
	if (random == 2)
	{
		if (logVector.size() != 0)
			bigLog.setPosition(sf::Vector2f(-188.0f, logVector[0].getPosition().y));
		logVector.push_back(bigLog);
	}
}

void Log::update(float deltaTime)
{
	
	if (logVector.size() == 0 || logVector[logVector.size() - 1].getPosition().x >= 100.0f)
	{
		insertLog();
	}

	for (int i = 0; i < logVector.size(); i++)
	{
		movement = sf::Vector2f(0.0f, 0.0f);
		if (logVector[i].getPosition().x < 1600.0f)
		{
			movement.x += speed * deltaTime;
			logVector[i].move(movement);
		}
		else
		{
			logVector.erase(logVector.begin() + i);
		}

	}
}

size_t Log::HowMuch()
{
	return logVector.size();
}

sf::Vector2f Log::getPosition(int index)
{
	return logVector[index].getPosition();
}

void Log::setPosition(float x, float y, int index)
{
	logVector[index].setPosition(x, y);
}

sf::FloatRect Log::getGlobalBounds(int index)
{
	return logVector[index].getGlobalBounds();
}

void Log::clear(int state)
{
	logVector.clear();
	
	if (state == 2)
	{
		smallLog.setPosition(sf::Vector2f(-188.0f, -1650.0f));
		bigLog.setPosition(sf::Vector2f(-188.0f, -1650.0f));
	}
	else
	{
		smallLog.setPosition(sf::Vector2f(-188.0f, -1630.0f));
		bigLog.setPosition(sf::Vector2f(-188.0f, -1630.0f));
	}
}
