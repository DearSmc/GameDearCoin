#pragma once
#include "AllInclude.h"
#include "Map.h"

class Collision
{
public:
	Collision(int &state);
	~Collision();

	int checkCollision(Player* player, Coin* coin);
	bool checkCollision(Player* player, Enemy* enemy);
	int checkCollision(Player* player, Door* door);
	bool checkCollision(Player* player, Pit* pit);
	int checkCollision(Player* player, Wall* wall);
	bool checkCollision(Player* player, Log* log);
	void Update(Player* player, Coin* coin, Enemy* enemy, Door* door, Pit* pit, Wall* wall,Log* log, Map* map,float deltaTime);
	void gameReset(Player* player, Coin* coin, Enemy* enemy, Door* door, Pit* pit, Wall* wall, Log* log, Map* map);

	bool scoreChange;
	unsigned int score;
	unsigned int life;
	unsigned int clock;
	
private:

	sf::Music collisCoin;
	sf::Music collisEnemy;
	int *state;
	bool check;
	void deadPlayer(Player* player, Coin* coin, Enemy* enemy, Door* door, Pit* pit, Wall* wall, Log* log, Map* map);
	bool onLog;
	bool everload;
};
