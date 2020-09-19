#include "Wall.h"

Wall::Wall()
{
	this->direction =sf::Vector2f(0.0f,0.0f);
	block.setSize(sf::Vector2f(94.0f-20.0f, 100.0f-20.0f));
	block.setFillColor(sf::Color::Transparent);
	block.setOutlineThickness(2.0f);
	block.setOutlineColor(sf::Color::Red);
	block.setOrigin(sf::Vector2f(block.getSize().x / 2.0f, block.getSize().y / 2.0f));
}

Wall::~Wall()
{
}

void Wall::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < nWall; i++)
	{
		window.draw(wall[i]);
	}
}

sf::FloatRect Wall::getGlobalBounds(int index)
{
	return wall[index].getGlobalBounds();
}

void Wall::setPosition(float x, float y, int index)
{
	wall[index].setPosition(x, y);
}

sf::Vector2f Wall::getPosition(int index)
{
	return wall[index].getPosition();
}

void Wall::loadPosition(int& state)
{
	std::ifstream getPoint;

	wall.clear();
	if (state == 1)
	{
		nWall = 93;
		getPoint.open("File/PointOfWallS1.ini");
		//	std::cout << "After size " << pit.size() << "\n";
	}
	else if (state == 2)
	{
		nWall = 114;
		getPoint.open("File/PointOfWallS2.ini");
	}
	else if (state == 3)
	{ 
		nWall = 133;
		getPoint.open("File/PointOfWallBonus.ini");
	}

	for (int i = 0; i < nWall; i++)
	{
		wall.push_back(block);
		distance.push_back(direction);
		dirVector.push_back(direction);
	}

	if (getPoint.is_open())
	{
		std::string Si = "";
		std::string Sx = "";
		std::string Sy = "";
		std::string St = "";

		while (getPoint >> Si >> Sx >> Sy >> St)
		{
			float i = std::stof(Si);
			float x = std::stof(Sx);
			float y = std::stof(Sy);
			int t = std::stoi(St);
			if (t == 1)//small block
			{
				wall[i].setSize(sf::Vector2f(94.0f, 100.0f));
				wall[i].setPosition(x + wall[i].getSize().x / 2.0f, y + wall[i].getSize().y / 2.0f);
			}
			if (t == 2)//normal block
			{		
				wall[i].setSize(sf::Vector2f(94.0f - 18.8f, 100.0f - 20.0f));
				wall[i].setPosition(x + wall[i].getSize().x / 2.0f + 9.4f, y + wall[i].getSize().y / 2.0f + 10.0f);
			}
			if (t == 3)//high block
			{
				wall[i].setSize(sf::Vector2f(47.0f, 100.0f));	
				wall[i].setPosition(x + wall[i].getSize().x / 2.0f+23.5f, y + wall[i].getSize().y / 2.0f);
			}
			if (t == 4)//long block
			{
				wall[i].setSize(sf::Vector2f(94.0f, 50.0f));
				wall[i].setPosition(x + wall[i].getSize().x / 2.0f, y + wall[i].getSize().y / 2.0f+25.0f);
			}
			if (t == 5)//smaller block
			{
				wall[i].setSize(sf::Vector2f(85.0f,70.0f));
				wall[i].setPosition(x + wall[i].getSize().x / 2.0f  , y + wall[i].getSize().y / 2.0f );
			}
			//std::cout << "[" << i << "]" << x << " " << y << "\n";
				
		}
		getPoint.close();
	}
	else
	{
		std::cout << "error to load file" << "\n";
	}
}

size_t Wall::HowMuch()
{
	return wall.size();
}

void Wall::update(Player* player)
{
	for (int i = 0; i < wall.size(); i++)
	{
		distance[i] =  player->getPosition()-getPosition(i);
		dirVector[i] = distance[i] / (sqrt(pow(distance[i].x, 2.0f) + pow(distance[i].y, 2.0f)));
	}
}

sf::Vector2f Wall::giveDirection(int index)
{
	return dirVector[index];
}
