#include "Coin.h"
#include "player.h"
#include "Animation.h"

Coin::Coin(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed):
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;
	this->texture = *texture;

	chestTexture.loadFromFile("prop/Untitled-1-giga.png");
	chest.setTexture(&chestTexture);
	chest.setSize(sf::Vector2f(60.f, 60.f));
	chest.setOrigin(chest.getSize().x / 2.f, chest.getSize().y / 2.f);

	clockTexture.loadFromFile("prop/clock.png");
	clock.setTexture(&clockTexture);
	clock.setSize(sf::Vector2f(57.f, 64.5f));
//	clock.setOutlineThickness(1.0f);
//	clock.setOutlineColor(sf::Color::Red);

}

Coin::~Coin()
{
}

void Coin::Update(float deltaTime)
{
	animation.Update(row, deltaTime, faceRight);
	for(int i=0; i < coinVector.size(); i++)
		coinVector[i].setTextureRect(animation.uvRect);
}

void Coin::Draw(sf::RenderWindow& window)
{
	if(this->stateNow!=3)
		window.draw(clock);
	
	window.draw(chest);
	for (int i = 0; i < coinVector.size(); i++)
	{
		window.draw(coinVector[i]);
	}
}

sf::FloatRect Coin::getGlobalBounds(int index)
{
	return coinVector[index].getGlobalBounds();
}

void Coin::setPosition(float x, float y,int index)
{
	coinVector[index].setPosition(x, y);
}

sf::Vector2f Coin::getPosition(int index)
{
	return coinVector[index].getPosition();
}

size_t Coin::HowMuch()
{
	return coinVector.size();
}

void Coin::erase(int index)
{
	if (index >= 0)	coinVector.erase(coinVector.begin() + index);
	else if (index == -2)	clock.setPosition(-100, 100);
	else chest.setPosition(-100, 100);
}

void Coin::loadPosition(int state)
{	
	this->stateNow = state;
	std::ifstream getCoinPoint;
	coinVector.clear();
	if (state == 1)
	{	
		
		nCoin = 25;
		chest.setPosition(sf::Vector2f(505.f, 650.f));
		clock.setPosition(sf::Vector2f(80.f, -870.f));
		getCoinPoint.open("File/PointOfCoinS1.ini");	
	}
	else if (state == 2)
	{
		nCoin = 25;
		chest.setPosition(sf::Vector2f(1010.f, -850.f));
		clock.setPosition(sf::Vector2f(1453.f, 205.f));
		getCoinPoint.open("File/PointOfCoinS2.ini");
	}
	else if (state == 3)
	{
		nCoin = 35;
		chest.setPosition(sf::Vector2f(1470.f, -105.f));
	//	clock.setPosition(sf::Vector2f(80.f, -870.f));
		getCoinPoint.open("File/PointOfCoinBonus.ini");
	}


	for (int i = 0; i < nCoin; i++)
	{
		coinVector.push_back(coin);
		coinVector[i].setRadius(20.0f);
		coinVector[i].setTexture(&texture);

		if(state==1)	
			coinVector[i].setOrigin(coinVector[i].getRadius(), coinVector[i].getRadius());
	}

	if (getCoinPoint.is_open())
	{
		std::cout << "done" << std::endl;
		std::string Si = "";
		std::string Sx = "";
		std::string Sy = "";
		
		while (getCoinPoint >> Si >> Sx >> Sy)
		{
			float i = std::stof(Si);
			float x = std::stof(Sx);
			float y = std::stof(Sy);
			//std::cout << "[" << i << "]" << x << " " << y << "\n";
			coinVector[i].setPosition(x, y);		//notePad	
		}
		getCoinPoint.close();
	}
	else
	{
		std::cout << "error to load file" << "\n";
	}

}

sf::FloatRect Coin::getGlobalBoundsChest()
{
	return chest.getGlobalBounds();
}

void Coin::setPositionChest(float x, float y)
{
	chest.setPosition(x, y);
}

sf::Vector2f Coin::getPositionChest()
{
	return chest.getPosition();
}

sf::FloatRect Coin::getGlobalBoundsClock()
{
	return clock.getGlobalBounds();
}

void Coin::setPositionClock(float x, float y)
{
	clock.setPosition(x, y);
}

sf::Vector2f Coin::getPositionClock()
{
	return clock.getPosition();
}

void Coin::setOrigin(int distance)
{
	chest.setPosition(chest.getPosition().x, chest.getPosition().y - distance);
	clock.setPosition(clock.getPosition().x, clock.getPosition().y - distance);
	for(int i=0;i<coinVector.size();i++)
	{
		coinVector[i].setPosition(coinVector[i].getPosition().x, coinVector[i].getPosition().y - distance);
	}
}
