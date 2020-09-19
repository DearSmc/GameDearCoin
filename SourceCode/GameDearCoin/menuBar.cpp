#include "menuBar.h"

menuBar::menuBar()
{
	check = false;
	state = true;

	font.loadFromFile("font/Game Played.otf");
	scoreText.setFont(font);
	lifeText.setFont(font);
	timeText.setFont(font);
	TimetoEnd.setFont(font);

	
	TimeTexture.loadFromFile("prop/time-01.png");
	Time.setTexture(&TimeTexture);
	Time.setSize(sf::Vector2f(170, 170));
	Time.setPosition(715, 20);
	
	TimetoEnd.setPosition(790.0f, 100.0f);

	scoreText.setPosition(115.f, 15.f);
	scoreBar.setSize(sf::Vector2f(150.0f, 50.0f));
	scoreBar.setPosition(30.f,10.f);
	scoreTexture.loadFromFile("prop/scoreBar.png");
	scoreBar.setTexture(&scoreTexture);
	
	lifeText.setPosition(315.f, 15.f);
	lifeBar.setSize(sf::Vector2f(150.0f, 50.0f));
	lifeBar.setPosition(230.f, 10.f);
	lifeTexture.loadFromFile("prop/lifeBar.png");
	lifeBar.setTexture(&lifeTexture);

	timeText.setPosition(507.f, 15.f);
	timeBar.setSize(sf::Vector2f(150.0f, 50.0f));
	timeBar.setPosition(430.f, 10.f);
	timeTexture.loadFromFile("prop/timeBar.png");
	timeBar.setTexture(&timeTexture);

}

void menuBar::update(int intScore, int intLife, int intTime)
{
	std::stringstream score;
	score << intScore;
	scoreText.setString(score.str());	

	std::stringstream life;
	life << intLife; 
	lifeText.setString(life.str());

	std::stringstream time;
	time << intTime;
	timeText.setString(time.str());

}

void menuBar::draw(sf::RenderWindow& window)
{
	window.draw(scoreBar);
	window.draw(scoreText);

	window.draw(lifeBar);
	window.draw(lifeText);

	window.draw(timeBar);
	window.draw(timeText);

	if (check && state)
	{
		window.draw(Time);
		window.draw(TimetoEnd);
	}
}

void menuBar::bonusTime(int intTime,float bonusTime)
{
	if (bonusTime != 0.0)
	{
		state = true;
		intBonusTime = intTime - (int)bonusTime;
		std::stringstream ssTime;
		ssTime << intBonusTime;
		TimetoEnd.setString(ssTime.str());
		check = true;
		if (intBonusTime <= 0)	state = false;
	}
}


