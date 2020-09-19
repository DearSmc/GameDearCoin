#pragma once
#include "AllInclude.h"
#include "Animation.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	void setPosition(float x,float y);

	sf::FloatRect getGlobalBounds();
	sf::FloatRect getBaseGlobalBounds();
	sf::Vector2f getPosition();

	void setOrigin();

	bool collisWall;
	bool collisEnemy;
	unsigned int count;
	bool evermove;
	void move(sf::Vector2f direction);

	sf::Vector2f movement;

private:
	
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;

	sf::RectangleShape hitBox;
	sf::RectangleShape basePlayer;

	sf::Clock timer;
	

};



