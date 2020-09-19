#include "Collision.h"

Collision::Collision(int& state)
{
	this->scoreChange = true;
	this->score = 0;
	this->life = 3;
	this->clock = 0;
	this->state = &state;
	this->check = false;
	this->onLog = false;
	this->everload = &everload;
}

Collision::~Collision()
{

}

int Collision::checkCollision(Player* player, Coin* coin)
{
	for(int i=0; i < coin->HowMuch(); i++)
	{
		if (player->getGlobalBounds().intersects(coin->getGlobalBounds(i)))
		{
			return i;
		}
	}
	if (player->getGlobalBounds().intersects(coin->getGlobalBoundsChest()))
	{
		return -1;
	}
	if (player->getGlobalBounds().intersects(coin->getGlobalBoundsClock()))
	{
		return -2;
	}
	
	return -3;

}

bool Collision::checkCollision(Player* player, Enemy* enemy)
{
	for (int i = 0; i < enemy->HowMuch(); i++)
	{
		if (player->getGlobalBounds().intersects(enemy->getGlobalBounds(i)))
		{
			return true;
		}
	}
	return false;
}

int Collision::checkCollision(Player* player, Door* door)
{
	for (int i = 0; i < door->HowMuch(); i++)
	{
		if (player->getBaseGlobalBounds().intersects(door->getGlobalBounds(i)))
		{
			return i;
		}
	}
	return -1;
}

bool Collision::checkCollision(Player* player, Pit* pit)
{
	for (int i = 0; i < pit->HowMuch(); i++)
	{
		if (player->getBaseGlobalBounds().intersects(pit->getGlobalBounds(i)))
		{
			//std::cout << i;
			return true;
		}
	}
	return false;
}

int Collision::checkCollision(Player* player, Wall* wall)
{
	for (int i = 0; i < wall->HowMuch(); i++)
	{
		if (player->getGlobalBounds().intersects(wall->getGlobalBounds(i)))
		{
			return i;
		}
	}
	return -1;
}

bool Collision::checkCollision(Player* player, Log* log)
{
	for (int i = 0; i < log->HowMuch(); i++)
	{
		if (player->getBaseGlobalBounds().intersects(log->getGlobalBounds(i)))
		{
			onLog = true;
			return true;
		}
	}
	onLog = false;
	return false;
}

void Collision::Update(Player* player, Coin* coin, Enemy* enemy, Door* door, Pit* pit, Wall* wall, Log* log, Map* map, float deltaTime)
{
	if (*state != 3)
	{
		if (player->evermove)
		{
			if (checkCollision(player, coin) != -3)
			{
				collisCoin.openFromFile("sound/coin.wav");
				collisCoin.play();
				this->scoreChange = true;

				int index = checkCollision(player, coin);
				coin->erase(index);

				if (index == -1) { this->score = this->score + 5; }
				else if (index == -2) { this->clock = this->clock + 20; }
				else { this->score++; }

			}
			if (player->count == 0 && !onLog)
			{
				if (checkCollision(player, enemy) || checkCollision(player, pit))
				{
					if (!check)
					{
						//std::cout << " collision" << "\n";
						collisEnemy.openFromFile("sound/LaserShot.wav");
						collisEnemy.play();

						player->collisEnemy = true;
						check = true;
					}
				}
			}

			if (!onLog)
			{
				if (checkCollision(player, wall) != -1)
				{
					int index = checkCollision(player, wall);
					player->move(sf::Vector2f(wall->giveDirection(index) * deltaTime * 10.0f));
					player->collisWall = true;
				}
				else		player->collisWall = false;
			}

			if (check)
			{
				if (life <= 3 && life > 1)
					deadPlayer(player, coin, enemy, door, pit, wall, log, map);
				else
				{
					*state = 4;
					map->loadMap();
				}
			}
			if (player->count == 0)
			{
				if (checkCollision(player, door) != -1)
				{

					*state = *state + 1;
					map->move(-1800.f);
					map->loadMap();
					door->setOrigin(map->coinDistance);
					enemy->loadPosition(*state);
					player->setOrigin();
					coin->loadPosition(*state);
					log->clear(*state);
					pit->loadPosition(*state);
					wall->loadPosition(*state);
					map->coinDistance = 0;
				}
			}

			if (checkCollision(player, log) && player->count == 0)
			{
				//int index = checkCollision(player, log);
				player->move(sf::Vector2f(log->movement.x, 0.0f));
				if (player->getPosition().x > 1600.0f)
				{
					player->count = 4;
					deadPlayer(player, coin, enemy, door, pit, wall, log, map);
				}
			}


		}
	}
	else
	{
		if (player->evermove)
		{
			if (checkCollision(player, coin) != -3)
			{
				collisCoin.openFromFile("sound/coin.wav");
				collisCoin.play();
				this->scoreChange = true;

				int index = checkCollision(player, coin);
				coin->erase(index);

				if (index == -1) { this->score = this->score + 5; }
				else if (index == -2) { this->clock = this->clock + 20; }
				else { this->score++; }
			}
		
			if (checkCollision(player, wall) != -1)
			{
				int index = checkCollision(player, wall);
				player->move(sf::Vector2f(wall->giveDirection(index) * deltaTime * 10.0f));
				player->collisWall = true;
			}
			else		player->collisWall = false;

			if (checkCollision(player, door) != -1)
			{
				*state = *state + 1;
				map->move(-1800.f);
				map->loadMap();
				door->setOrigin(map->coinDistance);
				enemy->loadPosition(*state);
				player->setOrigin();
				coin->loadPosition(*state);
				wall->loadPosition(*state);
				pit->loadPosition(*state);
				log->clear(*state);
				map->coinDistance = 0;
			}

		}
	}
}
	

void Collision::gameReset(Player* player, Coin* coin, Enemy* enemy, Door* door, Pit* pit,Wall* wall,Log* log, Map* map)
{
	this->scoreChange = true;
	this->score = 0;
	this->life = 3;
	this->clock = 0;
	*state = 1;	
	player->collisWall = false;

	map->move(-1800.f);
	enemy->loadPosition(*state);
	pit->loadPosition(*state);
	wall->loadPosition(*state);
	coin->loadPosition(*state);
	log->clear(*state);
	map->coinDistance = 0;
	player->setOrigin();
	map->loadMap();

}

void Collision::deadPlayer(Player* player, Coin* coin, Enemy* enemy, Door* door, Pit* pit, Wall* wall, Log* log, Map* map)
{
	if (player->count == 4)
	{
		this->scoreChange = true;
		this->life--;

		map->move(-1800.f);
		enemy->loadPosition(*state);
		pit->loadPosition(*state);
		wall->loadPosition(*state);
		coin->setOrigin(map->coinDistance);
		door->setOrigin(map->coinDistance);
		player->setOrigin();
		log->clear(*state); 
	
		map->coinDistance = 0;
		check = false;
		onLog = false;
		player->count = 0;
		player->collisWall = false;
	}
}

