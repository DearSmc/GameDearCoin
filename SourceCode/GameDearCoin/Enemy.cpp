#include "Enemy.h"
#include "Animation.h"

Enemy::Enemy(sf::Texture* texture,sf::Vector2u imageCount, float switchTime, float speed)
	:animation(texture, imageCount, switchTime)
{ 
	
	enemyTexture0.loadFromFile("Sprite/enemy.png");
	enemyTexture1.loadFromFile("Sprite/Female24-1.png");
	enemyTexture2.loadFromFile("Sprite/Soldier02-4.png");
 	this->speed = speed;
	faceRight = true;	
	
	enemy.setSize(sf::Vector2f(94.f, 100.0f));
	//enemy.setOutlineThickness(1.0f);
	//enemy.setOutlineColor(sf::Color::Green);
	enemy.setOrigin(enemy.getSize().x / 2.0f, enemy.getSize().y / 2.0f);

}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	//walk(deltatime,index,mode);   
	for(int i = 0; i < enemyVector.size(); i++)
	{
		Walk(deltaTime, i, modeVector[i]);
		
	}
	
}

void Enemy::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < enemyVector.size(); i++)
	{
		window.draw(enemyVector[i]);
		//window.draw(hitBoxVector[i]);
	}
}

void Enemy::Walk(float deltaTime, int index, int mode)
{
	if (mode == 1)
	{
		if (secVector[index] == 0)//Down
		{
			//std::cout << "DOWN" << "\n";
			rowVector[index] = 0;
			movementVector[index].y += speed * deltaTime;
			if (distanceVector[index].y > 300)
			{
				secVector[index] = 1;
			}
		}
		else if (secVector[index] == 1)//stop to up
		{
			waitTime[index] += speed * deltaTime;
			rowVector[index] = 3;
			if (waitTime[index] >= 75)
			{
				secVector[index] = 2;
				waitTime[index] = 0.0f;
			}
		}
		else if(secVector[index]==2)//up
		{
			//std::cout << "Up" << "\n";
			movementVector[index].y -= speed * deltaTime;
			rowVector[index] = 3;
			if (distanceVector[index].y <= 0)
			{
				secVector[index] = 3;
			}
		}
		else if(secVector[index]==3)//stop to down
		{
			waitTime[index] += speed * deltaTime;
			rowVector[index] = 0;
			if (waitTime[index] >= 75)
			{
				secVector[index] = 0;
				waitTime[index] = 0.0f;
			}
		}
	}
	
	else if (mode == 2)
	{
		if (secVector[index] == 0)//Right
		{
			rowVector[index] = 2;
			movementVector[index].x += speed * deltaTime;
			if (distanceVector[index].x > 282)
			{
				secVector[index] = 1;
			}
		}
		else if (secVector[index] == 1)
		{
			waitTime[index] += speed * deltaTime;
			rowVector[index] = 1;
			if (waitTime[index]>= 75)
			{
				secVector[index] = 2;
				waitTime[index] = 0.0f;
			}
		}
		else if (secVector[index] == 2)//Left
		{
			movementVector[index].x -= speed * deltaTime;
			rowVector[index] = 1;
			if (distanceVector[index].x <= 0)
			{
				secVector[index] = 3;
			}
		}
		else if (secVector[index] == 3)
		{
			waitTime[index] += speed * deltaTime;
			rowVector[index] = 2;
			if (waitTime[index]>= 75)
			{
				secVector[index] = 0;
				waitTime[index] = 0.0f;
			}
		}
	}

	else if (mode == 3)//เดิน4เหลี่ยมวน 1 บล็อค
	{
		if (secVector[index] == 0)//Down
		{
			//std::cout << "DOWN" << "\n";
			rowVector[index] = 0;
			movementVector[index].y += speed * deltaTime;
			if (distanceVector[index].y > 120)
			{
				secVector[index] = 1;
			}
		}
		else if (secVector[index] == 1)//stop to up
		{
			waitTime[index] += speed * deltaTime;
			rowVector[index] = 1;
			if (waitTime[index] >= 75)
			{
				secVector[index] = 2;
				waitTime[index] = 0.0f;
			}
		}
		else if (secVector[index] == 2)//Left
		{
			movementVector[index].x -= speed * deltaTime;
			rowVector[index] = 1;
			if (distanceVector[index].x <= -150)
			{
				secVector[index] = 3;
			}
		}
		else if (secVector[index] == 3)
		{
			waitTime[index] += speed * deltaTime;
			rowVector[index] = 3;
			if (waitTime[index] >= 75)
			{
				secVector[index] = 4;
				waitTime[index] = 0.0f;
			}
		}
		else if (secVector[index] == 4)//up
		{
			//std::cout << "Up" << "\n";
			movementVector[index].y -= speed * deltaTime;
			rowVector[index] = 3;
			if (distanceVector[index].y <= 0)
			{
				secVector[index] = 5;
			}
		}
		else if (secVector[index] == 5)//stop to right
		{
			waitTime[index] += speed * deltaTime;
			rowVector[index] = 2;
			if (waitTime[index] >= 75)
			{
				secVector[index] = 6;
				waitTime[index] = 0.0f;
			}
		}
		else if (secVector[index] == 06)//Right
		{
			rowVector[index] = 2;
			movementVector[index].x += speed * deltaTime;
			if (distanceVector[index].x >= 0)
			{
				secVector[index] = 7;
			}
		}
		else if (secVector[index] == 7)
		{
			waitTime[index] += speed * deltaTime;
			rowVector[index] = 0;
			if (waitTime[index] >= 75)
			{
				secVector[index] = 0;
				waitTime[index] = 0.0f;
			}
		}
		
	}

	else if (mode == 4)//เดิน4เหลี่ยมวน 2 บล็อค
	{
	if (secVector[index] == 0)//Down
	{
		//std::cout << "DOWN" << "\n";
		rowVector[index] = 0;
		movementVector[index].y += speed * deltaTime;
		if (distanceVector[index].y > 160)
		{
			secVector[index] = 1;
		}
	}
	else if (secVector[index] == 1)//stop to up
	{
		waitTime[index] += speed * deltaTime;
		rowVector[index] = 1;
		if (waitTime[index] >= 75)
		{
			secVector[index] = 2;
			waitTime[index] = 0.0f;
		}
	}
	else if (secVector[index] == 2)//Left
	{
		movementVector[index].x -= speed * deltaTime;
		rowVector[index] = 1;
		if (distanceVector[index].x <= -260)
		{
			secVector[index] = 3;
		}
	}
	else if (secVector[index] == 3)
	{
		waitTime[index] += speed * deltaTime;
		rowVector[index] = 3;
		if (waitTime[index] >= 75)
		{
			secVector[index] = 4;
			waitTime[index] = 0.0f;
		}
	}
	else if (secVector[index] == 4)//up
	{
		//std::cout << "Up" << "\n";
		movementVector[index].y -= speed * deltaTime;
		rowVector[index] = 3;
		if (distanceVector[index].y <= 0)
		{
			secVector[index] = 5;
		}
	}
	else if (secVector[index] == 5)//stop to right
	{
		waitTime[index] += speed * deltaTime;
		rowVector[index] = 2;
		if (waitTime[index] >= 75)
		{
			secVector[index] = 6;
			waitTime[index] = 0.0f;
		}
	}
	else if (secVector[index] == 06)//Right
	{
		rowVector[index] = 2;
		movementVector[index].x += speed * deltaTime;
		if (distanceVector[index].x >= 0)
		{
			secVector[index] = 7;
		}
	}
	else if (secVector[index] == 7)
	{
		waitTime[index] += speed * deltaTime;
		rowVector[index] = 0;
		if (waitTime[index] >= 75)
		{
			secVector[index] = 0;
			waitTime[index] = 0.0f;
		}
	}

	}

	else if (mode == 5)
	{
		//std::cout << "moode 5" <<"\t"<<secVector[index]<< "\n";
		if (secVector[index] == 0)//up
		{
			//std::cout << "Up" << "\n";
			movementVector[index].y -= speed * deltaTime;
			rowVector[index] = 3;
			if (distanceVector[index].y <= -300)
			{
				secVector[index] = 1;
			}
		}
		else if (secVector[index] == 1)//stop to down
		{
			waitTime[index] += speed * deltaTime;
			rowVector[index] = 0;
			if (waitTime[index] >= 75)
			{
				secVector[index] = 2;
				waitTime[index] = 0.0f;
			}
		}
		else if (secVector[index] == 2)//Down
		{
			//std::cout << "DOWN" << "\n";
			rowVector[index] = 0;
			movementVector[index].y += speed * deltaTime;
			if (distanceVector[index].y >= 0)
			{
				secVector[index] = 3;
			}
		}
		else if (secVector[index] == 3)//stop to up
		{
			waitTime[index] += speed * deltaTime;
			rowVector[index] = 3;
			if (waitTime[index] >= 75)
			{
				secVector[index] = 0;
				waitTime[index] = 0.0f;
			}
		}
		
	}

	distanceVector[index].x += movementVector[index].x;
	distanceVector[index].y += movementVector[index].y;
	enemyVector[index].move(movementVector[index]);

	animation.Update(rowVector[index], deltaTime, faceRight);
	enemyVector[index].setTextureRect(animation.uvRect);
	for (int i = 0; i < enemyVector.size(); i++)
	{
		movementVector[i].x = 0.0f;
		movementVector[i].y = 0.0f;
		hitBoxVector[i].setPosition(enemyVector[i].getPosition().x, enemyVector[i].getPosition().y);
	}
}

size_t Enemy::HowMuch()
{
	return enemyVector.size();
}

sf::Vector2f Enemy::getPosition(int index)
{
	return enemyVector[index].getPosition();
}

void Enemy::setPosition(float x, float y, int index)
{
	enemyVector[index].setPosition(x, y);
}

sf::FloatRect Enemy::getGlobalBounds(int index)
{
	return hitBoxVector[index].getGlobalBounds();
}

void Enemy::loadPosition(int state)
{
	std::ifstream getEnemyPoint;
	enemyVector.clear();
	modeVector.clear();
	if (state == 1)
	{
		nEnemy = 7;
		getEnemyPoint.open("File/PointOfEnemyS1.ini");
	}

	else if (state == 2)
	{
		nEnemy = 6;
		getEnemyPoint.open("File/PointOfEnemyS2.ini");
	}

	for (int i = 0; i < nEnemy; i++)
	{
		enemyVector.push_back(enemy);
		ran = random();
		if(ran == past)
		{
			ran =random();
			//std::cout << "in loop" << std::endl;
		}	
		else
		{
			past = ran;
		}
		
		
		if (ran == 0)
		{
			enemyVector[i].setTexture(&enemyTexture0);
		}
		else if (ran == 1)
		{
			enemyVector[i].setTexture(&enemyTexture1);
		}
		else
		{
			enemyVector[i].setTexture(&enemyTexture2);
		}
	
		movementVector.push_back(movement);

		rowVector.push_back(row);
		rowVector[i] = 0;

		waitTime.push_back(0.0f);

		distanceVector.push_back(distance);
		distanceVector[i].x = 0.0f;
		distanceVector[i].y = 0.0f;

		secVector.push_back(sec);
		secVector[i] = 0;

		hitBoxVector.push_back(hitBox);
		hitBoxVector[i].setSize(sf::Vector2f(enemyVector[i].getGlobalBounds().width - 32, enemyVector[i].getGlobalBounds().height));
		hitBoxVector[i].setOrigin(hitBoxVector[i].getSize().x / 2.0f, hitBoxVector[i].getSize().y / 2.0f);
		
	//	hitBoxVector[i].setOutlineThickness(1.0f);
	//	hitBoxVector[i].setOutlineColor(sf::Color::Blue);

	}

	if (getEnemyPoint.is_open())
	{
		std::string Si = "";
		std::string Sx = "";
		std::string Sy = "";
		std::string Sm = "";

		while (getEnemyPoint >> Si >> Sx >> Sy >> Sm)
		{
			float i = std::stof(Si);
			float x = std::stof(Sx);
			float y = std::stof(Sy);
			int m = std::stoi(Sm);

			enemyVector[i].setPosition(x, y);	//notePad	
			hitBoxVector[i].setPosition(enemyVector[i].getPosition().x, enemyVector[i].getPosition().y);
			modeVector.push_back(m);
		}
		getEnemyPoint.close();

	}
	else
	{
		std::cout << "error to load file" << "\n";
	}
}

int Enemy::random()
{
	srand(time(0)+rand());
	return rand()%3;
}
