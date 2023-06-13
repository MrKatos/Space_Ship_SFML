#pragma once

#include "RenderSystem.h"

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

class Ship : public RenderSystem
{
private:

	sf::Texture texture;
	sf::Sprite sprite;

	float speed;
	int hp;
	int hpmax;

	float cooldowan;
	float cooldownMax;

	void initVariables();
	void initTexture();
	void initSprite();
	//void initGui();


public:
	Ship();
	~Ship();

	const sf::Vector2f& getPos() const;

	const sf::FloatRect getBounds() const;

	const int& getHp()const;
	const int& getHpmax()const;
	void setHp(const int hp);
	void losehp(const int hp);


	//void setPosition(const sf::Vector2f x);
	void setPosition(const float x, const float y);


	void move(const float x, const float y);

	const bool attack();

	void updateCooldown();

	virtual void render(sf::RenderTarget* target) {};
	virtual void render(sf::RenderTarget& target) override;
	virtual void update() override;


};

