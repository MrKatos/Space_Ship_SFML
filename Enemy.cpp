#include "Enemy.h"
#include<iostream>

void Enemy::InitVariables()
{
	this->pointCount = rand() % 8 + 3; //masx 10 min 3
	this->speed = 1;// static_cast<float>(this->pointCount/2); tu krzyzcy pojeb
	this->hp = this->hpmax;
	this->hpmax = static_cast <int>(this->pointCount / 2);
	this->damage = this->pointCount;
	this->points = this->pointCount;
	this->type = 0;
}

Enemy::Enemy(float x, float y)
{


	this->InitVariables();
	this->InitShape();
	this->shape.setPosition(x, y);

}

Enemy::~Enemy()
{

}

void Enemy::InitShape()
{
	this->shape.setRadius(this->pointCount * 5); //this->pointCount
	this->shape.setPointCount(this->pointCount); //this->pointCount;
	this->shape.setFillColor(sf::Color(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255)));

	if (!this->enemyShape.loadFromFile("Textures/ufo.png"))
	{
		std::cout << "Somthing went wrong" << "\n";
	}
}

void Enemy::render(sf::RenderTarget* target)
{
	this->shape.setTexture(&this->enemyShape);
	target->draw(this->shape);
}

void Enemy::setSpeed(float speed_arg)
{
	this->speed = speed_arg;
}

void Enemy::setDeadStyle(DEAD::DeadStyle style_arg)
{
	this->style = style_arg;
}

const DEAD::DeadStyle Enemy::getDeadStyle() const
{
	return this->style;
}

void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints()const
{
	return this->points;
}

const int& Enemy::getDmg() const
{
	return this->damage;
}

const sf::Vector2f Enemy::getPossition() const
{
	return this->shape.getPosition();
}
