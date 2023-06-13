#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
class Menu
{
private:

	sf::Texture textureGlowna;
	sf::Sprite spriteGlowny;

	sf::Texture textureStart;
	sf::Sprite spriteStart;

	sf::Texture textureRetry;
	sf::Sprite spriteRetry;

	sf::Texture textureClose;
	sf::Sprite spriteClose;

	void initSpriteMenu();
	void initTextureMenu();

public:

	Menu();
	~Menu();
	void renderMenu(sf::RenderTarget& target);
	sf::FloatRect getStartBounds();
	sf::FloatRect getCloseBounds();
	sf::FloatRect getReplayBounds();
	void setStartColor(sf::Color color);
	void setCloseColor(sf::Color color);
	void setReplayColor(sf::Color color);
	virtual void render() = 0;
};

