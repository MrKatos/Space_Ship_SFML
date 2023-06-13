#include "Menu.h"

Menu::Menu()
{
	this->initTextureMenu();

	this->initSpriteMenu();
}

Menu::~Menu()
{
	std::cout << "Usunieto Menu" << std::endl;
}

void Menu::renderMenu(sf::RenderTarget& target)
{
	target.draw(this->spriteGlowny);
	target.draw(this->spriteRetry);
	target.draw(this->spriteStart);
	target.draw(this->spriteClose);
}

sf::FloatRect Menu::getStartBounds()
{
	return this->spriteStart.getGlobalBounds();
}

sf::FloatRect Menu::getCloseBounds()
{
	return this->spriteClose.getGlobalBounds();
}

sf::FloatRect Menu::getReplayBounds()
{
	return this->spriteRetry.getGlobalBounds();
}

void Menu::setStartColor(sf::Color color)
{
	this->spriteStart.setColor(color);
}

void Menu::setCloseColor(sf::Color color)
{
	this->spriteClose.setColor(color);
}

void Menu::setReplayColor(sf::Color color)
{
	this->spriteRetry.setColor(color);
}

void Menu::initSpriteMenu()
{
	this->spriteGlowny.setTexture(this->textureGlowna);
	this->spriteGlowny.setOrigin(301.f, 301.f);
	this->spriteGlowny.setPosition(sf::Vector2f(555.f, 300.f));
	this->spriteGlowny.setScale(0.5f, 0.5f);

	this->spriteRetry.setTexture(this->textureRetry);
	this->spriteRetry.setOrigin(58.f, 58.f);
	this->spriteRetry.setPosition(sf::Vector2f(480.f, 470.f));
	this->spriteRetry.setScale(0.5f, 0.5f);
	this->spriteRetry.setColor(sf::Color(190, 190, 190, 255));

	this->spriteStart.setTexture(this->textureStart);
	this->spriteStart.setOrigin(58.f, 58.f);
	this->spriteStart.setPosition(sf::Vector2f(597.f, 470.f));
	this->spriteStart.setScale(0.5f, 0.5f);
	this->spriteStart.setColor(sf::Color(190, 190, 190, 255));

	this->spriteClose.setTexture(this->textureClose);
	this->spriteClose.setOrigin(58.f, 58.f);
	this->spriteClose.setPosition(sf::Vector2f(683.f, 199.f));
	this->spriteClose.setScale(0.55f, 0.55f);
	this->spriteClose.setColor(sf::Color(190, 190, 190, 255));
}

void Menu::initTextureMenu()
{
	if (!this->textureGlowna.loadFromFile("Textures/logo.png"))
	{
		std::cout << "Somthing went wrong  menu glowna" << "\n";
	}
	else
	{
		this->textureGlowna.setSmooth(true);
	}
	if (!this->textureRetry.loadFromFile("Textures/replay.png"))
	{
		std::cout << "Somthing went wrong menu retry" << "\n";
	}
	else
	{
		this->textureRetry.setSmooth(true);
	}
	if (!this->textureStart.loadFromFile("Textures/Play.png"))
	{
		std::cout << "Somthing went wrong menu start" << "\n";
	}
	else
	{
		this->textureStart.setSmooth(true);
	}
	if (!this->textureClose.loadFromFile("Textures/close.png"))
	{
		std::cout << "Somthing went wrong menu start" << "\n";
	}
	else
	{
		this->textureClose.setSmooth(true);
	}
}