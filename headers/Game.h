#ifndef _GAME_H_
#define _GAME_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game
{
public:
	Game();

	~Game();

	bool isHovered(sf::RectangleShape& shape, sf::RenderWindow& window);

	void restartGame();

	void shuffleCards();

	bool isCorrect();

	bool inCorrect(int n);

	bool isOver();

	void run();

private:
	sf::Sprite backgrounds[2];
	sf::Texture backgroundsTextures[2];

private:
	sf::RectangleShape buttons[2];
	sf::Texture buttonsTextures[4];

private:
	sf::RectangleShape cards[12];
	sf::Texture cardsTextures[8];

private:
	unsigned short cardsTexturesBounds[12];
	short cardsSelected[2];
	short cardsCorrect[12];
	int turns;

private:
	sf::Font font;
	sf::Text turnsText;
	sf::String turnsString;
	int temp;

private:
	sf::Sound audio;
	sf::SoundBuffer sounds[4];
};

#endif