#include "Score.h"

Score::Score()
{
}

Score::~Score()
{
}

void Score::updateScore(Player& player, Coin& coin)
{
	if (collis.checkCollision(&player, &coin))
	{
		score++;
	}
}


int Score::giveMeScore()
{
	return score;
}
