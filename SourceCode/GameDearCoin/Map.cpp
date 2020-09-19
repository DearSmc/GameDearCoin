#include "Map.h"

Map::Map(int& state)
{	
	this->state = &state;
	this->coinDistance = 0;
	this->oldPosition = 800.0f;

	Background.setSize(sf::Vector2f(1600.0f, 2700.0f));
	Background.setPosition(0.0f, -1800.0f);

	background.setSize(sf::Vector2f(1600.0f, 900.0f));   
	background.setPosition(0.0f, 0.f);
	
	stateMainMenu.loadFromFile("BG/mainMenu.jpg");
	stateHighScore.loadFromFile("BG/HS.jpg");
	stateOne.loadFromFile("BG/map1.jpg");
	stateTwo.loadFromFile("BG/map2.jpg");
	stateBonus.loadFromFile("BG/Untitled-1.png");
	stateYourScore.loadFromFile("BG/yourScore.png");

}

Map::~Map()
{
}
					
void Map::Update(Player* player, Coin* coin, Enemy* enemy, Door* door, Pit* pit, Wall* wall, Log* log)
{
	if (*state == 3)
	{
		if (Background.getPosition().y == -910.f)
			notEnd = false;
	}
	else
	{
		if (Background.getPosition().y == 0.f)
			notEnd = false;
	}
	
	if (player->getPosition().y != oldPosition)
	{
		if (player->getPosition().y <= 450 && notEnd)
		{
			y += 1.f;
			evenGo = true;

			player->setPosition(player->getPosition().x, player->getPosition().y + 1);				//move player
			this->oldPosition = player->getPosition().y;

			move(y);
			for (int i = 0; i < wall->HowMuch(); i++)
				wall->setPosition(wall->getPosition(i).x, wall->getPosition(i).y + 1, i);			//move map

			for (int i = 0; i < coin->HowMuch(); i++)
				coin->setPosition(coin->getPosition(i).x, coin->getPosition(i).y + 1, i);			//move coin
			coin->setPositionClock(coin->getPositionClock().x, coin->getPositionClock().y + 1);
			coin->setPositionChest(coin->getPositionChest().x, coin->getPositionChest().y + 1);		//move chest

			for (int i = 0; i < enemy->HowMuch(); i++)
				enemy->setPosition(enemy->getPosition(i).x, enemy->getPosition(i).y + 1, i);
			for (int i = 0; i < pit->HowMuch(); i++)
				pit->setPosition(pit->getPosition(i).x, pit->getPosition(i).y + 1, i);
			for (int i = 0; i < log->HowMuch(); i++)
				log->setPosition(log->getPosition(i).x, log->getPosition(i).y + 1, i);

			for (int i = 0; i < door->HowMuch(); i++)
				door->setPosition(door->getPosition(i).x, door->getPosition(i).y + 1, i);		//move door
			this->coinDistance++;
		}
		/*-------------------·ÓãËé©Ò¡àÅ×èÍ¹¢Ö¹-----------------------------------*/
		else if (player->getPosition().y >= 600 && evenGo)
		{
			y -= 1.f;
			if (Background.getPosition().y == 900 - Background.getSize().y)
			{
				evenGo = false;
			}
			if (Background.getPosition().y != 0)
			{
				notEnd = true;
			}

			player->setPosition(player->getPosition().x, player->getPosition().y - 1);
			this->oldPosition = player->getPosition().y;

			move(y);
			for (int i = 0; i < wall->HowMuch(); i++)
				wall->setPosition(wall->getPosition(i).x, wall->getPosition(i).y - 1, i);

			for (int i = 0; i < coin->HowMuch(); i++)
				coin->setPosition(coin->getPosition(i).x, coin->getPosition(i).y - 1, i);
			coin->setPositionChest(coin->getPositionChest().x, coin->getPositionChest().y - 1);
			coin->setPositionClock(coin->getPositionClock().x, coin->getPositionClock().y - 1);

			for (int i = 0; i < enemy->HowMuch(); i++)
				enemy->setPosition(enemy->getPosition(i).x, enemy->getPosition(i).y - 1, i);
			for (int i = 0; i < pit->HowMuch(); i++)
				pit->setPosition(pit->getPosition(i).x, pit->getPosition(i).y - 1, i);
			for (int i = 0; i < log->HowMuch(); i++)
				log->setPosition(log->getPosition(i).x, log->getPosition(i).y - 1, i);
			for (int i = 0; i < door->HowMuch(); i++)
				door->setPosition(door->getPosition(i).x, door->getPosition(i).y - 1, i);

			this->coinDistance--;
		}
	}

	
	/*if (player->getPosition().y != oldPosition)
	{
		if (player->getPosition().y <= 450 && notEnd)
		{
			y += 1.f;
			evenGo = true;

			player->setPosition(player->getPosition().x, player->getPosition().y + 1);				//move player
			this->oldPosition = player->getPosition().y;

			move(y);
			for (int i = 0; i < wall->HowMuch(); i++)
				wall->setPosition(wall->getPosition(i).x, wall->getPosition(i).y + 1, i);//move map

			for (int i = 0; i < coin->HowMuch(); i++)
				coin->setPosition(coin->getPosition(i).x, coin->getPosition(i).y + 1, i);			//move coin
			coin->setPositionChest(coin->getPositionChest().x, coin->getPositionChest().y + 1);		//move chest

			for (int i = 0; i < door->HowMuch(); i++)
				door->setPosition(door->getPosition(i).x, door->getPosition(i).y + 1, i);		//move door
			this->coinDistance++;
		}*/
		/*-------------------·ÓãËé©Ò¡àÅ×èÍ¹¢Ö¹-----------------------------------
		else if (player->getPosition().y >= 600 && evenGo)
		{
			y -= 1.f;
			if (Background.getPosition().y == 900 - Background.getSize().y)
			{
				evenGo = false;
			}
			if (Background.getPosition().y != 0)
			{
				notEnd = true;
			}

			player->setPosition(player->getPosition().x, player->getPosition().y - 1);
			this->oldPosition = player->getPosition().y;

			move(y);
			for (int i = 0; i < wall->HowMuch(); i++)
				wall->setPosition(wall->getPosition(i).x, wall->getPosition(i).y - 1, i);

			for (int i = 0; i < coin->HowMuch(); i++)
				coin->setPosition(coin->getPosition(i).x, coin->getPosition(i).y - 1, i);
			coin->setPositionChest(coin->getPositionChest().x, coin->getPositionChest().y - 1);

			for (int i = 0; i < door->HowMuch(); i++)
				door->setPosition(door->getPosition(i).x, door->getPosition(i).y - 1, i);

			this->coinDistance--;
		}
	}*/
}

void Map::move(float newY)
{
		if (Background.getPosition().y<=0) 
		{
			Background.setPosition(0.0f, newY);
			y = newY;
		}
}

void Map::Draw(sf::RenderWindow& window)
{	
	//std::cout << "I drawed"<<"\n";
	if (*state < 1 || *state == 4)
		window.draw(background);
	else
		window.draw(Background);
}

void Map::loadMap()
{
	//std::cout << "load state " << *state << "\n";
	switch (*state)
	{
	case -1: 
		
		background.setTexture(&stateHighScore);
		background.setSize(sf::Vector2f(1600.0f, 900.0f));
		background.setPosition(0.0f, 0.f);
		
		break;

	case 0:

		background.setTexture(&stateMainMenu);
		background.setPosition(0.0f,0.f);
		break;

	case 1:
		Background.setTexture(&stateOne);
		Background.setPosition(0.0f, -1800.f);
		y = -1800;
		break;

	case 2:
		Background.setTexture(&stateTwo);
		Background.setPosition(0.0f, -1800.f);
		y = -1800;
		break;


	case 3:

		Background.setTexture(&stateBonus);
		Background.setPosition(0.0f, -1800.f);
		y = -1800;
		break;

	case 4:
		background.setTexture(&stateYourScore);
		background.setPosition(0.0f, 0.f);
		break;
	}
	
}


