#pragma once
#include "AllInclude.h" 
#include "player.h"
#include "Coin.h"
#include "Enemy.h"
#include "Door.h"
#include "Pit.h"
#include "Wall.h"
#include "Log.h"

class Map
{
public: 
	Map(int &state);
	~Map();

	void Update(Player* player, Coin* coin,Enemy* enemy, Door* door,Pit* pit, Wall* wall,Log* log);
	void move(float y);						
	void Draw(sf::RenderWindow& window);	
	void loadMap();

	int coinDistance;

private:
	int *state;
	sf::RectangleShape Background;	
	sf::RectangleShape background;
	sf::RectangleShape bonusBackground;
	float y;
	float oldPosition;		
	bool evenGo = false;			
	bool notEnd = true;			
	
	sf::Texture stateMainMenu;
	sf::Texture stateHighScore;
	sf::Texture stateOne;
	sf::Texture stateTwo;
	sf::Texture stateThree;
	sf::Texture stateBonus;
	sf::Texture stateYourScore;
	
	
};

