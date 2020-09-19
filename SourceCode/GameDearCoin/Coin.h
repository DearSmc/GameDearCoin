#pragma once
#include "AllInclude.h"
#include "Animation.h"


class Coin
{
public:
	Coin(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Coin();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void setOrigin(int distance);
	void erase(int index);
	void loadPosition(int state);

	sf::FloatRect getGlobalBounds(int index);
	void setPosition(float x, float y, int index);
	sf::Vector2f getPosition(int index);
	size_t  HowMuch();

	sf::FloatRect getGlobalBoundsChest();
	void setPositionChest(float x,float y);
	sf::Vector2f getPositionChest();

	sf::FloatRect getGlobalBoundsClock();
	void setPositionClock(float x, float y);
	sf::Vector2f getPositionClock();

private:
	
	sf::CircleShape coin;
	std::vector<sf::CircleShape> coinVector;
	unsigned int nCoin;

	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
	sf::Texture texture;

	sf::RectangleShape chest;
	sf::Texture chestTexture;

	sf::RectangleShape clock;
	sf::Texture clockTexture;

	int stateNow;
};

