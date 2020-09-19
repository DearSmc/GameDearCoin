#include "player.h"
#include "Animation.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed):
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;
	this->collisWall = false;
	this->collisEnemy = false;
	this->count = 0;
	this->evermove = false;
	
	body.setSize(sf::Vector2f(94.f, 100.0f));
	body.setOrigin(body.getSize().x/2.0f, body.getSize().y / 2.0f);
	body.setPosition(800.0f, 850.0f);
	//body.setOutlineThickness(1.0f);
	//body.setOutlineColor(sf::Color::Red);
	body.setTexture(texture);

	hitBox.setSize(sf::Vector2f(body.getGlobalBounds().width-32,body.getGlobalBounds().height/2));
	hitBox.setOrigin(hitBox.getSize().x / 2.0f, hitBox.getSize().y / 2.0f);

	//hitBox.setOutlineThickness(1.0f);
	//hitBox.setOutlineColor(sf::Color::Blue);
	
	basePlayer.setSize(sf::Vector2f((body.getGlobalBounds().width - 32)/2, body.getGlobalBounds().height/5));
	basePlayer.setOrigin(basePlayer.getSize().x/2.0f,0.0f);
	basePlayer.setPosition(body.getPosition().x, body.getPosition().y+ body.getGlobalBounds().height /3);
	//basePlayer.setPosition(body.getPosition().x+32, body.getPosition().y+ body.getGlobalBounds().height / 4);
	basePlayer.setOutlineThickness(1.0f);
	basePlayer.setOutlineColor(sf::Color::Blue);
}

Player::~Player()
{
}


void Player::Update(float deltaTime)
{
	movement=sf::Vector2f (0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		if (body.getPosition().x - 45.0f > 0)
		{
			movement.x -= speed * deltaTime;
			row = 1;
			faceRight = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		if (body.getPosition().x + 45.0f < 1600)
		{
			movement.x += speed * deltaTime;
			row = 2;
			faceRight = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		if (body.getPosition().y - 50.0f > 0)
		{
			movement.y -= speed * deltaTime;
			row = 3;
			faceRight = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		if (body.getPosition().y + 50.0f < 900)
		{
			movement.y += speed * deltaTime;
			row = 0;
			faceRight = true;
		}
	}
	if (movement.x != 0 || movement.y != 0)		this->evermove = true;

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	//std::cout << collisWall << std::endl;
	if (!collisWall)
	{
		body.move(movement);
		hitBox.setPosition(body.getPosition().x, body.getPosition().y+body.getSize().y/4);
		basePlayer.setPosition(body.getPosition().x, body.getPosition().y + body.getGlobalBounds().height / 3);
	}
	
}  

void Player::Draw(sf::RenderWindow& window)
{
	//std::cout << time.asSeconds() << "\n ";
	if (!collisEnemy)
	{
		//window.draw(hitBox);
		//window.draw(basePlayer);
		window.draw(body);

		if (count != 0)
		{
			sf::Time time = timer.getElapsedTime();
			if (time.asSeconds() >= 0.1)
			{
			//	std::cout << "done " << count << std::endl;
				timer.restart().asSeconds();
				collisEnemy = !collisEnemy;
				
			}
		}
	}
	else
	{
		sf::Time time = timer.getElapsedTime();
		if (time.asSeconds() >= 0.1)
		{	
		//	std::cout << "done "<<count << std::endl;
			timer.restart().asSeconds();
			collisEnemy = !collisEnemy;
			count++;
		}
		
	}
	if (count == 4)
	{
		row = 4;
		collisEnemy = false;
	}
}

sf::FloatRect Player::getGlobalBounds()
{
	return hitBox.getGlobalBounds();
}

sf::FloatRect Player::getBaseGlobalBounds()
{
	return basePlayer.getGlobalBounds();
}

void Player::setPosition(float x, float y)
{
	body.setPosition(x, y);
}

sf::Vector2f Player::getPosition()
{
	return sf::Vector2f(body.getPosition());
}

void Player::setOrigin()
{
	body.setPosition(800.0f, 850.0f);
}

void Player::move(sf::Vector2f direction)
{
	body.move(direction);
	hitBox.move(direction);
	basePlayer.move(direction);
}
