#include "Pit.h"

Pit::Pit()
{
	block.setSize(sf::Vector2f(94.0f, 100.0f));
	block.setFillColor(sf::Color::Transparent);
	block.setOutlineThickness(2);
	block.setOutlineColor(sf::Color::Blue);
	
}

Pit::~Pit()
{
}

void Pit::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < nPit; i++)
	{
		window.draw(pit[i]);
	}
}

sf::FloatRect Pit::getGlobalBounds(int index)
{
	return pit[index].getGlobalBounds();
}

void Pit::setPosition(float x, float y, int index)
{
	pit[index].setPosition(x, y);
}

sf::Vector2f Pit::getPosition(int index)
{
	return pit[index].getPosition(); 
}

void Pit::loadPosition(int& state)
{	
	std::ifstream getPoint;
	
	pit.clear();
	if (state == 1)
	{
		nPit = 109;
		getPoint.open("File/PointOfPitS1.ini");
	//	std::cout << "After size " << pit.size() << "\n";
	}
	if (state == 2)
	{
		nPit = 101;
		getPoint.open("File/PointOfPitS2.ini");
		//	std::cout << "After size " << pit.size() << "\n";
	}

	for (int i = 0; i < nPit; i++)
	{
		pit.push_back(block);
	}
	
	if (getPoint.is_open())
	{
		std::string Si = "";
		std::string Sx = "";
		std::string Sy = "";

		while (getPoint >> Si >> Sx >> Sy)
		{
			float i = std::stof(Si);
			float x = std::stof(Sx);
			float y = std::stof(Sy);
			//std::cout << "[" << i << "]" << x << " " << y << "\n";
			pit[i].setPosition(x, y);		//notePad	
		}
		getPoint.close();
	
	}
	else
	{
		std::cout << "error to load file" << "\n";
	}
	//std::cout <<"pit size " << pit.size()<<"\n";
}

size_t Pit::HowMuch()
{
	return pit.size();
}
