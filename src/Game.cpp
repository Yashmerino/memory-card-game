#include "../headers/Game.h"
#include <iostream>
#include <Windows.h>

Game::Game()
{
	backgroundsTextures[0].loadFromFile("img/background.png"); //Setting backgrounds
	backgroundsTextures[1].loadFromFile("img/toolbarBg.png");
	
	for (int i = 0; i < 2; i++)
	{
		backgrounds[i].setTexture(backgroundsTextures[i]);
		backgrounds[i].setOrigin(backgrounds[i].getLocalBounds().width / 2, backgrounds[i].getLocalBounds().height / 2);
	}

	backgrounds[0].setPosition(float(480 / 2), float(640 / 2 - backgrounds[1].getTexture()->getSize().y));
	backgrounds[1].setPosition(float(480 / 2), float(640 - backgrounds[1].getTexture()->getSize().y / 2));

	cardsTextures[0].loadFromFile("img/gamecardC++.png"); //Setting cards
	cardsTextures[1].loadFromFile("img/gamecardJava.png");
	cardsTextures[2].loadFromFile("img/gamecardJS.png");
	cardsTextures[3].loadFromFile("img/gamecardPHP.png");
	cardsTextures[4].loadFromFile("img/gamecardPy.png");
	cardsTextures[5].loadFromFile("img/gamecardRy.png");
	cardsTextures[6].loadFromFile("img/gamecardDefault.png");
	cardsTextures[7].loadFromFile("img/gamecardHover.png");

	for (int i = 0; i < 6; i++)
	{
		cards[i].setTexture(&cardsTextures[6]);
		cards[11 - i].setTexture(&cardsTextures[6]);

		cards[i].setSize(sf::Vector2f(115.f, 115.f));
		cards[11 - i].setSize(sf::Vector2f(115.f, 115.f));
	}

	cards[0].setPosition(45.f, 15.f);
	cards[1].setPosition(180.f, 15.f);
	cards[2].setPosition(315.f, 15.f);
	cards[3].setPosition(45.f, 145.f);
	cards[4].setPosition(180.f, 145.f);
	cards[5].setPosition(315.f, 145.f);
	cards[6].setPosition(45.f, 275.f);
	cards[7].setPosition(180.f, 275.f);
	cards[8].setPosition(315.f, 275.f);
	cards[9].setPosition(45.f, 405.f);
	cards[10].setPosition(180.f, 405.f);
	cards[11].setPosition(315.f, 405.f);

	buttonsTextures[0].loadFromFile("img/toolbarClose.png"); //Setting buttons
	buttonsTextures[1].loadFromFile("img/toolbarCloseHover.png");
	buttonsTextures[2].loadFromFile("img/toolbarNew.png");
	buttonsTextures[3].loadFromFile("img/toolbarNewHover.png");

	buttons[0].setTexture(&buttonsTextures[0]);
	buttons[1].setTexture(&buttonsTextures[2]);

	buttons[0].setSize(sf::Vector2f(60.f, 60.f));
	buttons[1].setSize(sf::Vector2f(130.f, 70.f));

	for (int i = 0; i < 2; i++)
		buttons[i].setOrigin(buttons[i].getLocalBounds().width / 2, buttons[i].getLocalBounds().height / 2);

	buttons[0].setPosition(420.f, 585.f);
	buttons[1].setPosition(240.f, 585.f);

	shuffleCards(); //Preparing cards

	for (int i = 0; i < 12; i++)
	{
		cardsCorrect[i] = -1;
	}

	turns = -1;

	font.loadFromFile("fonts/ac.ttf");
	
	turnsString = "Turns: 0";

	turnsText.setFont(font);
	turnsText.setString(turnsString);
	turnsText.setColor(sf::Color::White);
	turnsText.setCharacterSize(36);
	turnsText.setOrigin(turnsText.getLocalBounds().width / 2, turnsText.getLocalBounds().height / 2);
	turnsText.setPosition(80.f, 575.f);

	sounds[0].loadFromFile("audio/win.wav");
	sounds[1].loadFromFile("audio/new.wav");
	sounds[2].loadFromFile("audio/correctPair.wav");
	sounds[3].loadFromFile("audio/incorrectPair.wav");

	temp = 0;
}

Game::~Game()
{

}

bool Game::isHovered(sf::RectangleShape& shape, sf::RenderWindow& window)
{
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	sf::FloatRect bounds = shape.getGlobalBounds();

	return bounds.contains(mousePos);
}

void Game::restartGame()
{
	audio.setBuffer(sounds[1]);
	audio.play();

	for (int i = 0; i < 12; i++)
	{
		cardsCorrect[i] = -1;
		cards[i].setTexture(&cardsTextures[6]);
	}

	cardsSelected[0] = -1;
	cardsSelected[1] = -1;

	turnsString = "Turns: 0";
	turnsText.setString(turnsString);

	temp = 0;
}

void Game::shuffleCards()
{
	srand(time(NULL));

	int randomNumber;

	for (int i = 0; i < 12; )
	{
		bool alreadyThere = false;
		randomNumber = rand() % 6;

		for (int j = 0; j < i; j++)
		{
			if (randomNumber == cardsTexturesBounds[j])
			{
				for (int h = j + 1; h < i; h++)
				{
					if (randomNumber == cardsTexturesBounds[h])
					{
						alreadyThere = true;
						break;
					}
				}
			}
		}

		if (!alreadyThere)
		{
			cardsTexturesBounds[i] = randomNumber;
			i++;
		}
	}
}

bool Game::isCorrect()
{
	temp += 1;

	turnsString = "Turns: " + std::to_string(temp);

	if (cards[cardsSelected[0]].getTexture() == cards[cardsSelected[1]].getTexture())
	{
		for (int i = 0; i < 12; i++)
		{
			if (cardsCorrect[i] == -1)
			{
				cardsCorrect[i] = cardsSelected[0];
				cardsCorrect[i + 1] = cardsSelected[1];
				break;
			}
		}

		audio.setBuffer(sounds[2]);
		audio.play();

		return true;
	}
	else
	{
		audio.setBuffer(sounds[3]);
		audio.play();

		return false;
	}
}

bool Game::inCorrect(int n)
{
	for (int i = 0; i < 12; i++)
	{
		if(cardsCorrect[i] == n)
		{
			return true;
		}
	}

	return false;
}

bool Game::isOver()
{
	for (int i = 0; i < 12; i++)
	{
		if(cardsCorrect[i] == -1)
		{
			return false;
		}
	}

	return true;
}

void Game::run()
{
	sf::RenderWindow window(sf::VideoMode(480, 640), "Memory Card Game");

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(0);
			}

			for (int i = 0; i < 12; i++)
			{
				if (event.type == sf::Event::MouseButtonPressed && isHovered(cards[i], window) && !(inCorrect(i)))
				{
					turns++;

					cardsSelected[turns] = i;

					if (turns >= 1 && cardsSelected[0] == cardsSelected[1])
					{
						turns = 0;
						continue;
					}
					else if (turns >= 1)
					{
						cards[i].setTexture(&cardsTextures[cardsTexturesBounds[i]]);

						{ //Showing 2 last cards
							for (int i = 0; i < 12; i++)
								window.draw(cards[i]);
							window.display();
							event.type = sf::Event::MouseEntered;
							Sleep(700);
						}

						turns = -1;

						if (!isCorrect())
						{
							for (int i = 0; i < 2; i++)
							{
								cards[cardsSelected[i]].setTexture(&cardsTextures[6]);
							}
						}
						else
						{
							if(isOver())
							{
								audio.setBuffer(sounds[0]);
								audio.play();
							}
						}

						continue;
					}

					cardsSelected[turns] = i;

					cards[i].setTexture(&cardsTextures[cardsTexturesBounds[i]]);
				}
				else if (event.type == sf::Event::MouseMoved && isHovered(cards[i], window))
				{
					bool allowChange = true;

					if (cardsSelected[0] == i || cardsSelected[1] == i)
						allowChange = false;

					for (int j = 0; j < 12; j++)
						if (cardsCorrect[j] == i)
							allowChange = false;

					if(allowChange)
					cards[i].setTexture(&cardsTextures[7]);
				}
				else
				{
					bool allowChange = true;

					if (cardsSelected[0] == i || cardsSelected[1] == i)
						allowChange = false;

					for (int j = 0; j < 12; j++)
						if (cardsCorrect[j] == i)
							allowChange = false;

					if (allowChange)
					cards[i].setTexture(&cardsTextures[6]);
				}
			}

			for (int i = 0; i < 2; i++)
			{
				if (event.type == sf::Event::MouseMoved && isHovered(buttons[i], window))
				{
					buttons[i].setTexture(&buttonsTextures[i * 2 + 1]);
				}
				else if(event.type == sf::Event::MouseButtonPressed && isHovered(buttons[0], window))
				{
					window.close();
					exit(0);
				}
				else if (event.type == sf::Event::MouseButtonPressed && isHovered(buttons[1], window))
				{
					restartGame();
				}
				else
				{
					buttons[i].setTexture(&buttonsTextures[i * 2]);
				}
			}
		}

		turnsText.setString(turnsString);

		window.clear(sf::Color::White);
		for (int i = 0; i < 2; i++)
			window.draw(backgrounds[i]);
		for (int i = 0; i < 12; i++)
			window.draw(cards[i]);
		for (int i = 0; i < 2; i++)
			window.draw(buttons[i]);
		window.draw(turnsText);
		window.display();
	}
}
