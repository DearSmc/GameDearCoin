#pragma once
#include "AllInclude.h"
#include "Animation.h"
class Enemy
{
public:
	Enemy(sf::Texture* texture,sf::Vector2u imageCount, float switchTime, float speed);
	~Enemy();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void Walk(float deltaTime, int index, int mode);

	size_t HowMuch();
	
	sf::Vector2f getPosition(int index);
	void setPosition(float x,float y,int index);
	sf::FloatRect getGlobalBounds(int index);
	void loadPosition(int state);

private:
	
	sf::RectangleShape enemy;
	std::vector<sf::RectangleShape> enemyVector;
	std::vector<sf::Vector2f> distanceVector;
	std::vector<sf::Vector2f> movementVector;
	std::vector< unsigned int > secVector;
	std::vector<unsigned int> rowVector;
	std::vector<float> waitTime;
	std::vector<unsigned int> modeVector;

	sf::RectangleShape hitBox;
	std::vector<sf::RectangleShape> hitBoxVector;
	//std::vector<sf::RectangleShape> enemyVector;

	//std::vector<std::vector<sf::RectangleShape>> enemyVector;
	unsigned int nEnemy;

	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
	sf::Vector2u imageCount;

	sf::Vector2f movement;
	sf::Vector2f distance;
	//float distance = 0.0;
	bool down = true;
	unsigned int sec;

	int random();
	sf::Texture enemyTexture0;
	sf::Texture enemyTexture1;
	sf::Texture enemyTexture2;
	int past;
	int ran;
};

