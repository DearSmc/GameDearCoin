#pragma 
#include "AllInclude.h"
class Pit
{
public:
	Pit();
	~Pit();
	void draw(sf::RenderWindow& window);
	
	sf::FloatRect getGlobalBounds(int index);
	void setPosition(float x, float y, int index);
	sf::Vector2f getPosition(int index);
	void loadPosition(int& state);
	size_t  HowMuch();
	
private:
	unsigned int nPit;
	sf::RectangleShape block;
	std::vector<sf::RectangleShape> pit;

};

