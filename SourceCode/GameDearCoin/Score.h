#pragma once
#include "AllInclude.h"
#include "Collision.h"
#include "player.h"
#include "Coin.h"

class Score
{
public:
	Score();
	~Score();
	void updateScore(Player& player, Coin& coin);
	int giveMeScore();

private:
	unsigned int score = 0;
	Collision collis;
};

