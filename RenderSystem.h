#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

class RenderSystem
{
public:
	virtual void render(sf::RenderTarget* target) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
	virtual void update() = 0;
};

