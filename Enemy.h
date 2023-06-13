#pragma once

namespace DEAD
{
	enum DeadStyle { FELL, SHOOT, UNKNOWN };
}

#include "RenderSystem.h"

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

class Enemy : public RenderSystem
{
private:
	sf::Texture enemyShape;/// wcz
	sf::CircleShape shape;

	unsigned pointCount;
	float speed;
	int hp;
	int hpmax;
	int damage;
	int points; //killing enemies
	int type;

	DEAD::DeadStyle style = DEAD::UNKNOWN;

	void InitVariables();

	void InitShape();

public:

	Enemy(float x, float y);
	~Enemy();

	const sf::FloatRect getBounds()const;
	const int& getPoints() const;
	const int& getDmg()const;
	const sf::Vector2f getPossition() const;

	virtual void update() override;
	virtual void render(sf::RenderTarget* target) override;
	virtual void render(sf::RenderTarget& target) {};

	void setSpeed(float speed_arg);
	void setDeadStyle(DEAD::DeadStyle style_arg);
	const DEAD::DeadStyle getDeadStyle()const;

	friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy) 
	{
		switch (enemy.getDeadStyle())
		{
		case DEAD::FELL:
			return os << "Enemy: ASTEROID; Killed by: OUT OF THE MAP; At possition: [" << enemy.getPossition().x << ", " << enemy.getPossition().y << "]";
			break;

		case DEAD::SHOOT:
			return os << "Enemy: ASTEROID; Killed by: SHOOT BY SHIP; At possition: [" << enemy.getPossition().x << ", " << enemy.getPossition().y << "]";
			break;

		case DEAD::UNKNOWN:
			return os << "Enemy: ASTEROID; Killed by: REASON UNKNOWN; At possition: [" << enemy.getPossition().x << ", " << enemy.getPossition().y << "]";
			break;
		default:
			return os << "ZOLTY_PAN_ZNECAL_SIE_NAD_MALYMI_DZIECMI";
			break;
		}
	}
};

