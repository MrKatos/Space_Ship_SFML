#include "Ship.h"
#include <iostream>

Ship::Ship()
{
	this->initVariables();

	this->initTexture();

	this->initSprite();

}

Ship::~Ship()
{

}

void Ship::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
void Ship::update()
{
	this->updateCooldown();
}

void Ship::initSprite()
{
	this->sprite.setTexture(this->texture);

	//resize

	this->sprite.scale(0.5f, 0.5f);
}

void Ship::initTexture()
{
	//Load texture 

	if (!this->texture.loadFromFile("Textures/statek1.png"))
	{
		std::cout << "Somthing went wrong" << "\n";
	}

}

void Ship::move(const float x, const float y)
{
	this->sprite.move(this->speed * x, this->speed * y);
}

const sf::Vector2f& Ship::getPos() const
{
	return this->sprite.getPosition();
}

void Ship::updateCooldown()
{
	if (this->cooldowan < this->cooldownMax)
	{
		this->cooldowan += 0.5f;
	}
}

const bool Ship::attack()
{
	if (this->cooldowan >= this->cooldownMax)
	{
		this->cooldowan = 0.f;
		return true;
	}
	return false;
}
void Ship::initVariables()
{
	this->speed = 4.f;
	this->cooldownMax = 14.f;
	this->cooldowan = this->cooldownMax;
	this->hpmax = 20;
	this->hp = this->hpmax;

}
const sf::FloatRect Ship::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

//void Ship::setPosition(const sf::Vector2f x)
//{
//	this->sprite.setPosition(x);
//}

void Ship::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

const int& Ship::getHp() const
{
	return this->hp;
}

const int& Ship::getHpmax() const
{
	return this->hpmax;
}

void Ship::losehp(const int hp)
{
	this->hp -= hp;
	if (this->hp < 0)
	{
		this->hp = 0;
	}
}
void Ship::setHp(const int hp)
{
	this->hp = hp;
}