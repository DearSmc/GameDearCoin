#include "Button.h"

Button::Button(float x, float y, float width, float hight, sf::Texture* texture)
{
	this->buttonState = BTN_IDLE;
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, hight));
	this->shape.setTexture(texture);

	cursorHand.loadFromSystem(sf::Cursor::Hand);
	cursorArrow.loadFromSystem(sf::Cursor::Arrow);
}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_PRESSED)
		return true;
	return false;
}

void Button::update(sf::Vector2i& mousePos,sf::RenderWindow& window)
{
	this->buttonState = BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		this->buttonState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_PRESSED;
		}
	}

	switch (this->buttonState)
	{
		case BTN_IDLE:			window.setMouseCursor(cursorArrow);		break;
		case BTN_HOVER:			window.setMouseCursor(cursorHand);		break;
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
