#pragma once
#include "AllInclude.h"
enum button_State{BTN_IDLE=0,BTN_HOVER,BTN_PRESSED};

class Button
{
public: 
	Button(float x, float y, float width, float hight, sf::Texture* texture);
	~Button();

	const bool isPressed() const;

	void update(sf::Vector2i& mousePos, sf::RenderWindow& window);
	void render(sf::RenderTarget& target);

private:
	short unsigned buttonState;

	sf::RectangleShape shape;

	sf::Cursor cursorHand; 
	sf::Cursor cursorArrow;


	

};

