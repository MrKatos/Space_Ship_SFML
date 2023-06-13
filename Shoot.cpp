#include"Shoot.h"

Shoot::Shoot()
{

}


Shoot::Shoot(sf::Texture* texture, float xx, float yy, float x, float y, float bulletspeed)
{
	this->bullet.setTexture(*texture);

	this->bullet.setPosition(xx, yy);
	this->direction.x = x;
	this->direction.y = y;
	this->bulletspeed = bulletspeed;

}

const sf::FloatRect Shoot::getBounds() const
{
	return this->bullet.getGlobalBounds();
}

Shoot::~Shoot()
{

}
void Shoot::update()
{
	this->bullet.move(this->bulletspeed * this->direction);
}

void Shoot::render(sf::RenderTarget* target)
{
	target->draw(this->bullet);
}