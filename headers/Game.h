#ifndef _GAME_H_
#define _GAME_H_
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();

	~Game();

	bool checkHover(sf::RectangleShape& shape, sf::RenderWindow& window);

	void shuffleCards();

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
	int cardsTexturesBounds[12];

};

#endif