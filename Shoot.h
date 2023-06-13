#pragma once

#include "RenderSystem.h"

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

class Shoot : public RenderSystem
{
private:

	sf::Sprite bullet;

	sf::Vector2f direction;
	float bulletspeed;

public:
	Shoot();
	Shoot(sf::Texture* texture, float xx, float yy, float x, float y, float bulletspeed);
	~Shoot();


	const sf::FloatRect getBounds()const;

	virtual void update() override;
	virtual void render(sf::RenderTarget* target) override;
	virtual void render(sf::RenderTarget& target) {};



};

