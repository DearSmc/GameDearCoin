#include "Collision.h"
#include "Button.h"
#include "menuBar.h"

void readTextHS(sf::RenderWindow& window)
{
	sf::Font font;
	font.loadFromFile("font/Game Played.otf");
	
	sf::Text rankText;
	sf::Text nameText;
	sf::Text scoreText;
	
	rankText.setFont(font);
	nameText.setFont(font);
	scoreText.setFont(font);
	
	std::ifstream f("File/HighScore.ini");
	if (f)
	{
		std::string r = "";
		std::string n = "";
		std::string s = "";

		while (f >> r >> n >> s)
		{
			unsigned int rank = std::stoi(r);
		/*--------------------------- แก้เป็น 5 คน -----------------------*/
			rankText.setPosition(520.f, 340.f+(83*(rank-1)));
			nameText.setPosition(670.f, 340.f + (83 *( rank-1)));
			scoreText.setPosition(1040.f, 337.f + (83 * (rank-1)));

			rankText.setString(r);
			nameText.setString(n);
			scoreText.setString(s);

			//std::cout << "[" << r << "]" << n << " " << s << "\n";
			window.draw(rankText);
			window.draw(nameText);
			window.draw(scoreText);
		}
	}
	else
		std::cout << "Unable to load File" << "\n";
	
	f.close();
}

void sort(std::string name,int score)
{
	std::vector<std::string> rankVector;
	std::vector<std::string> nameVector;
	std::vector<int> scoreVector;

	std::ifstream f("File/HighScore.ini");
	if (f)
	{
		std::string r = "";
		std::string n = "";
		std::string s = "";

		while (f >> r >> n >> s)
		{
			unsigned int scor = std::stoi(s);

			rankVector.push_back(r);
			nameVector.push_back(n);
			scoreVector.push_back(scor);	
		}
	}
	else
		std::cout << "Unable to load File" << "\n";

	f.close();

	for (int i = 0; i < 5; i++)
	{
		if (score > scoreVector[i])
		{
			scoreVector.insert(scoreVector.begin() + i, score);
			nameVector.insert(nameVector.begin() + i, name);
			break;
		}
		else if (score == scoreVector[i])
		{ 
			scoreVector.insert(scoreVector.begin() + i + 1, score);
			nameVector.insert(nameVector.begin() + i + 1, name);
			break;
		}
	}

	if (scoreVector.size() == 6)
	{
		scoreVector.erase(scoreVector.begin() + 5);
		nameVector.erase(nameVector.begin() + 5);
	}

	std::ofstream fo("File/HighScore.ini");
	if (fo)
	{
		for (int i = 0; i < 5; i++)
		{
			fo << rankVector[i] <<" " << nameVector[i] <<" "<< scoreVector[i] << std::endl;
		}
	}
	else
		std::cout << "Unable to load File" << "\n";
	fo.close();
	
	rankVector.clear();
	nameVector.clear();
	scoreVector.clear();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "DearCoin", sf::Style::Default);
	window.setFramerateLimit(180);
	sf::Vector2i mousePosWindow;

	int state = 0;

	/*--------------- player ------------------*/
	sf::Texture playerTexture;
	playerTexture.loadFromFile("Sprite/Player-gigapixel.png");
	Player player(&playerTexture, sf::Vector2u(3, 5), 0.3f, 150.0f);

	bool everLoad;

	/*--------------- coin ------------------*/
	sf::Texture coinTexture;
	coinTexture.loadFromFile("prop/MonedaD-gigapixel.png");
	Coin coin(&coinTexture, sf::Vector2u(5, 1), 0.1f, 150.0f);

	/*---------------- enemy ---------------*/
	sf::Texture enemyTexture;
	enemyTexture.loadFromFile("Sprite/enemy.png");
	Enemy enemy(&enemyTexture,sf::Vector2u(3, 4), 1.0f, 80.0f);

	Map map(state);

	Collision collis(state);

	float deltaTime = 0.0f;
	sf::Clock clock;

	sf::Font font;
	font.loadFromFile("font/Game Played.otf");
	
	//sound buffer
	/*
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("sound/admiralbob77_-_All_the_Lines_2.wav"))
	{
		std::cout << "ERROR from sound";
	}
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	*/

	/*------------- Music ------------*/
	sf::Music music;
	music.openFromFile("sound/CG_D.wav");
	music.setLoop(true);
	music.play();

	/*------------ button ----------------*/
	std::map<std::string, Button*> buttons;

	sf::Texture startTexture;
	sf::Texture HSTexture;
	sf::Texture quitTexture;
	startTexture.loadFromFile("button/starBTNt.png");
	buttons["START"] = new Button(340.0f, 565.0f, 379.0f, 111.0f, &startTexture);
	HSTexture.loadFromFile("button/highScoreBTN.png");
	buttons["HIGH_SCORE"] = new Button(340.0f, 700.0f, 379.0f, 111.0f, &HSTexture);
	quitTexture.loadFromFile("button/quitBTN.png");
	buttons["QUIT"] = new Button(1280.0f, 800.0f, 295.0f, 90.0f, &quitTexture);

	sf::Texture homeTexture;
	homeTexture.loadFromFile("button/homeBTN.png");
	buttons["HOME"] = new Button(630.0f, 745.0f, 295.0f, 90.0f, &homeTexture);

	/*--------- button on gemestate ---------*/
	buttons["MENU"] = new Button(1400.0f, 0.0f, 200.0f, 60.0f, &homeTexture);
	
	/*---------- page your score ----------*/
	sf::RectangleShape block;
	sf::Texture blockTexture;
	blockTexture.loadFromFile("button/button-05.png");
	block.setTexture(&blockTexture);
	block.setSize(sf::Vector2f(330.0f,110.0f));
	block.setPosition(635, 545.0f);
	
	sf::RectangleShape cursor;
	cursor.setFillColor(sf::Color::Yellow);
	cursor.setSize(sf::Vector2f(4.0f, 50.0f));
	cursor.setPosition(673, 578.0f);

	sf::Event enterName;
	char lastChar = ' ';
	std::string name;
	sf::Text playerName;
	playerName.setFont(font);
	playerName.setCharacterSize(40);
	playerName.setPosition(673, 578.0f);
	
	float totalTime = 0;
	bool showCursor = false;
	float total = 0;
	
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setPosition(815.0f, 410.0f);
	
	sf::Texture cancelTexture;
	sf::Texture enterTexture;
	cancelTexture.loadFromFile("button/button-06.png");
	enterTexture.loadFromFile("button/button-07.png");
	buttons["CANCEL"] = new Button(800.0f, 650.0f, 295.0f, 90.0f, &cancelTexture);
	buttons["ENTER"] = new Button(530.0f, 650.0f, 295.0f, 90.0f, &enterTexture);

	/*-------------------------------------------*/

	float bonusTime=0.0f;

	menuBar menubar;

 	Door door(state);
	Pit pit;
	Wall wall;
	Log log(80.0f);

	everLoad = false;
	sf::Text myName;
	sf::Text myId;
	myName.setFont(font);
	myId.setFont(font);
	myName.setString("Sumincha Chalowong");
	myId.setString("62010978");
	myName.setPosition(sf::Vector2f(1240,40));
	myId.setPosition(sf::Vector2f(1350, 10));
	sf::Event TEvet;
	while (window.isOpen())
	{
		while(window.pollEvent(TEvet))
		{
			if (TEvet.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		//std::cout << deltaTime << std::endl;
		//std::cout << state << std::endl;
		//std::cout<<state<< "  ever load? "<< everLoad<<"\n";
		mousePosWindow = sf::Mouse::getPosition(window);
		//std::cout << mousePosWindow.x << "  " << mousePosWindow.y << std::endl;
		switch (state)
		{
		case -1:

			if (!everLoad)
			{
				deltaTime = clock.restart().asSeconds();
				//std::cout << "everload" << std::endl;
				map.loadMap();
				everLoad = true;
			}
			deltaTime = clock.getElapsedTime().asSeconds();
			map.Draw(window);
			//window.draw(HSbackground);
			readTextHS(window);
			buttons["HOME"]->update(mousePosWindow, window);
			buttons["HOME"]->render(window);

			window.display();
			if (deltaTime >= 0.5f)
			{
				if (buttons["HOME"]->isPressed())
				{
					state = 0;
					everLoad = false;
				}
			}
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || sf::Event::Closed)
				window.close();

			window.clear();
			break;

		case 0:
			
			if (!everLoad)
			{
				map.loadMap();
				everLoad = true;
			}
			map.Draw(window);
			window.draw(myName);
			window.draw(myId);
			buttons["START"]->update(mousePosWindow, window);
			buttons["HIGH_SCORE"]->update(mousePosWindow, window);
			buttons["QUIT"]->update(mousePosWindow, window);

			buttons["START"]->render(window);
			buttons["HIGH_SCORE"]->render(window);
			buttons["QUIT"]->render(window);

			window.display();

			if (buttons["START"]->isPressed())
			{
				state = 1;
				collis.gameReset(&player, &coin, &enemy, &door, &pit, &wall, &log, &map);
				everLoad = false;
			}
			if (buttons["HIGH_SCORE"]->isPressed())
			{
				state = -1;
				everLoad = false;
			}

			if (buttons["QUIT"]->isPressed())
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || sf::Event::Closed)
				window.close();

			window.clear();
			break;

		case 1:
			//	window.setMouseCursorVisible(false);

			if (!everLoad)	// ถ้ายังไม่เคยโหลดตำแหน่งเหรียญให้โหลด
			{
				deltaTime = clock.restart().asSeconds();
				map.loadMap();
				enemy.loadPosition(state);
				coin.loadPosition(state);
				pit.loadPosition(state);
				wall.loadPosition(state);
				everLoad = true;
			}
		
			//door.draw(window);
			//pit.draw(window);
			//wall.draw(window);
			map.Draw(window);
			log.draw(window);
			enemy.Draw(window);
			coin.Draw(window);
			player.Draw(window);

			buttons["MENU"]->render(window);
			menubar.draw(window);

			window.display();

			if (buttons["MENU"]->isPressed())
			{
				state = 0;
				everLoad = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)|| sf::Event::Closed)
				window.close();
	
			window.clear();

			buttons["MENU"]->update(mousePosWindow, window);
			collis.Update(&player, &coin, &enemy, &door, &pit, &wall, &log, &map, deltaTime);

			if (collis.scoreChange)
			{
				//std::cout << collis.score << "\n";
				menubar.update(collis.score, collis.life, collis.clock);
				collis.scoreChange = false;
			}
			deltaTime = clock.restart().asSeconds();
			player.Update(deltaTime);
			enemy.Update(deltaTime);
			coin.Update(deltaTime);
			wall.update(&player);

			map.Update(&player, &coin, &enemy, &door, &pit, &wall, &log);
			log.update(deltaTime);

			break;
		case 2:
		
			if (!everLoad)
			{
				deltaTime = clock.restart().asSeconds();
				map.loadMap();
				enemy.loadPosition(state);
				coin.loadPosition(state);
				pit.loadPosition(state);
				wall.loadPosition(state);
				log.clear(state);
				everLoad = true;
			}
			
			//pit.draw(window);
			//wall.draw(window);
			//door.draw(window);
			map.Draw(window);
			log.draw(window);
			coin.Draw(window);
			enemy.Draw(window);
			player.Draw(window);
			
			buttons["MENU"]->render(window);
			menubar.draw(window);

			window.display();

			if (buttons["MENU"]->isPressed())
			{
				state = 0;
				everLoad = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
				window.close();

			window.clear();

			buttons["MENU"]->update(mousePosWindow, window);
			collis.Update(&player, &coin, &enemy, &door, &pit, &wall, &log, &map, deltaTime);
			if (collis.scoreChange)
			{
				//std::cout << collis.score << "\n";
				menubar.update(collis.score, collis.life, collis.clock);
				collis.scoreChange = false;
			}
			deltaTime = clock.restart().asSeconds();
			player.Update(deltaTime);
			enemy.Update(deltaTime);
			coin.Update(deltaTime);
			wall.update(&player);

			map.Update(&player, &coin, &enemy, &door, &pit, &wall, &log);
			log.update(deltaTime);

			break;
		case 3:
			if (!everLoad)	// ถ้ายังไม่เคยโหลดตำแหน่งเหรียญให้โหลด
			{
				deltaTime = clock.restart().asSeconds();
				coin.loadPosition(state);
				wall.loadPosition(state);
				map.loadMap();
				everLoad = true;
			}
			bonusTime += deltaTime;
			
			map.Draw(window);
			//door.draw(window);
			//wall.draw(window);
			coin.Draw(window);
			player.Draw(window);

			buttons["MENU"]->render(window);
			menubar.bonusTime(collis.clock,bonusTime);
			menubar.draw(window);
			
			window.display();

			if (buttons["MENU"]->isPressed())
			{
				state = 0;
				everLoad = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || sf::Event::Closed)
				window.close();

			window.clear();

			buttons["MENU"]->update(mousePosWindow, window);

			collis.Update(&player, &coin, &enemy, &door, &pit, &wall, &log, &map, deltaTime);
			if (collis.scoreChange)
			{
				menubar.update(collis.score, collis.life, collis.clock);
				collis.scoreChange = false;
			}
			if (bonusTime >= collis.clock)
			{
				bonusTime = 0.0f;
				state++;
				everLoad = false;
			}
			deltaTime = clock.restart().asSeconds();
			player.Update(deltaTime);
			coin.Update(deltaTime);
			wall.update(&player);
			map.Update(&player, &coin, &enemy, &door, &pit, &wall, &log);
			break;

		case 4:
			if (!everLoad)	// ถ้ายังไม่เคยโหลดตำแหน่งเหรียญให้โหลด
			{
				map.loadMap();
				name.erase();
				everLoad = true;
			}
			deltaTime = clock.restart().asSeconds();
			totalTime += deltaTime;
			total += deltaTime;
			map.Draw(window);

			buttons["CANCEL"]->update(mousePosWindow, window);
			buttons["CANCEL"]->render(window);

			buttons["ENTER"]->update(mousePosWindow, window);
			buttons["ENTER"]->render(window);

			std::stringstream score;
			score << collis.score;
			scoreText.setString(score.str());
			window.draw(scoreText);
			window.draw(block);
			while (window.pollEvent(enterName) && total>=3.0f)
			{
				
				switch (enterName.type)
				{
				case sf::Event::Closed:	
					window.close();
					break;

				case sf::Event::TextEntered: 
					if (enterName.text.unicode != lastChar && ((enterName.text.unicode >= 65 && enterName.text.unicode <= 122) || (enterName.text.unicode >= 48 && enterName.text.unicode <= 57)) && name.length() <= 9)
					{	
						name += enterName.text.unicode;
					}
					else if (enterName.text.unicode == 8 && name.length() > 0 )
					{
						name.erase(name.length() - 1);
					}
					break;
				
				}
			}
			cursor.setPosition(673 + playerName.getGlobalBounds().width + 5, 578.0f);
			playerName.setString(name);
			window.draw(playerName);
			
			
			if (totalTime >= 0.5)
			{
				totalTime = 0;
				showCursor = !showCursor;
			}
			if (showCursor)
			{
				window.draw(cursor);
			}

			window.display();

			if (buttons["CANCEL"]->isPressed())
			{
				name.erase();
				everLoad = false;
				state = 0;
			}
			if (buttons["ENTER"]->isPressed()||sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
			{
				sort(name, collis.score);
				name.erase();
				everLoad = false;
				state = -1;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
				window.close();

			window.clear();
			break;
		}
		
	}

	return 0;         
	 
}