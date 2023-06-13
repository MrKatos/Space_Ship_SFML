#include "Game.h"
#include"Ship.h"
#include"Shoot.h"
#include"Enemy.h"
#include<iostream>

Game::Game()
{
	this->initWindow();
	/// <summary>
	//this->initMenu();
	/// </summary>
	this->initTextures();
	this->initBestScore();
	this->initGui();
	this->initMap();
	this->initVariables();
	this->initShip();
	this->initEnemies();

}

void Game::initMenu()
{

}



Game::~Game()
{
	delete this->window;
	delete this->ship;

	for (auto& i : this->textures)
	{
		delete i.second;
	}

	for (auto* i : this->bullets)
	{
		delete i;
	}

	for (auto* i : this->enemies)
	{
		delete i;
	}
}

void Game::run()
{

	while (this->window->isOpen())
	{
		this->updatePollEvents();
		//this->updateMenu();
		if (this->ship->getHp() > 0)
		{
			this->BestScore();
			if (!this->InMenu)
			{
				this->update();
			}
		}
		this->render();
	}

}
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1080, 720), "Galactic Atack 5", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

/// /////////////////////////////////////////////

void Game::render()
{
	this->window->clear();



	this->renderMap();

	this->ship->render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	//this->enemies->render(this->window);
	//std::cout << "sadasdasdas";
	//this->window->draw(*this->enemy);
	this->renderGui();

	//game over

	if (this->ship->getHp() <= 0)
	{
		this->Loose = true;
		this->InMenu = true;
	}
	if (this->InMenu)
	{
		this->renderMenu(*this->window);
		if (this->Loose)
		{
			this->window->draw(this->GameOver);
		}
	}
	this->window->display();
}

///////////////////////////////////////////

void Game::updateMenu()
{
}

void Game::update()
{

	//move ship

	//this->updatePollEvents();

	this->Input();

	this->ship->update();

	this->updateCollison();

	this->updateBullets();

	this->updateEnemies();

	this->updateCombat();

	this->updateGui();

	this->updateMap();
}

////////////////////////////////////////////////////

void Game::initShip()
{
	this->ship = new Ship();
	this->ship->setPosition(500.f, 500.f);
}

void Game::Input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->ship->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->ship->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->ship->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->ship->move(0.f, 1.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->ship->attack())
		//sf::Keyboard::isKeyPressed(sf::Keyboard::Space || sf::Mouse::isButtonPressed(sf::Mouse::Left)
	{
		this->bullets.push_back(new Shoot(this->textures["pocisk"], this->ship->getPos().x + this->ship->getBounds().width / 2.f, this->ship->getPos().y, 0.f, -1.f, 5.f));//+ this->ship->getBounds().width/2.f
	}
}

void Game::updatePollEvents()
{
	sf::Event e;

	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed || e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
		{
			this->InMenu = true;
		}

		if (this->InMenu)
		{
			if (this->getCloseBounds().contains(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window))) && e.type == sf::Event::MouseButtonPressed)
			{
				this->window->close();
			}
			if (this->getStartBounds().contains(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window))) && e.type == sf::Event::MouseButtonPressed)
			{
				this->InMenu = false;
			}
			if (this->getReplayBounds().contains(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window))) && e.type == sf::Event::MouseButtonPressed)
			{
				this->resetGame();
			}

			// jasniej ciemniej
			if (this->getCloseBounds().contains(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window))))
			{
				this->setCloseColor(sf::Color(255, 255, 255, 255));
			}
			else
			{
				this->setCloseColor(sf::Color(190, 190, 190, 255));
			}

			if (this->getStartBounds().contains(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window))))
			{
				this->setStartColor(sf::Color(255, 255, 255, 255));
			}
			else
			{
				this->setStartColor(sf::Color(190, 190, 190, 255));
			}

			if (this->getReplayBounds().contains(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window))))
			{
				this->setReplayColor(sf::Color(255, 255, 255, 255));
			}
			else
			{
				this->setReplayColor(sf::Color(190, 190, 190, 255));
			}
		}
	}
}
void Game::initTextures()
{
	this->textures["pocisk"] = new sf::Texture();
	this->textures["pocisk"]->loadFromFile("Textures/Sprite.png");
}

void Game::updateBullets()
{
	unsigned counder = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			delete this->bullets.at(counder);
			this->bullets.erase(this->bullets.begin() + counder);
			--counder;

			//std::cout << this->bullets.size() <<"\n";
		}
		++counder;
	}
}



void Game::initEnemies()
{

	this->spawnTimerMax = 20.f;
	this->spawnTimer = this->spawnTimerMax;
}
void Game::initGui()
{
	//load fonts
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		std::cout << "Failed to load fonts" << "\n";
	}


	//init text

	//this->pointText.setPosition(10.f, 25.f);////////////////////////////////////////////
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(24);
	//this->pointText.getOutlineThickness();
	this->pointText.setOutlineColor(sf::Color::White);
	this->pointText.setOutlineThickness(0.5f);
	this->pointText.setFillColor(sf::Color::White);

	this->HighestPoints.setFont(this->font);
	this->HighestPoints.setCharacterSize(24);
	this->HighestPoints.setFillColor(sf::Color::White);
	this->HighestPoints.setOutlineColor(sf::Color::White);
	this->HighestPoints.setOutlineThickness(0.5f);
	this->HighestPoints.setPosition(sf::Vector2f(0.f, 20.f));


	//this->GameOver.setPosition(100.f, 205.f);// tu sie zjebao !!!!!!!!!!!!!!!!!!!!

	this->GameOver.setFont(this->font);
	this->GameOver.setCharacterSize(64);
	this->GameOver.setFillColor(sf::Color::Red);
	this->GameOver.setString("Game Over");
	this->GameOver.setPosition(
		this->window->getSize().x / 2.f - this->GameOver.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->GameOver.getGlobalBounds().height / 2.f);

	//hp bar

	this->hpbar.setPosition(850.f, 650);///////////////////////////////
	this->hpbar.setSize(sf::Vector2f(200, 30));
	this->hpbar.setFillColor(sf::Color::Red);
	//this->hpbar.setPosition(sf::Vector2f(20.f, 20.f));

	this->hpbarback = this->hpbar;
	this->hpbarback.setFillColor(sf::Color(20, 25, 25, 150));

	this->HP.setFont(this->font);
	this->HP.setCharacterSize(20);
	this->HP.setFillColor(sf::Color::Red);
	this->HP.setString("Health Points");
	this->HP.setPosition(930.f, 620.f);



}

void Game::renderGui()
{
	this->window->draw(this->pointText);
	this->window->draw(this->HighestPoints);
	this->window->draw(this->HP);
	this->window->draw(this->hpbarback);
	this->window->draw(this->hpbar);
}

void Game::updateGui()
{
	std::stringstream ss;
	ss << "POINTS :  " << this->points;
	this->pointText.setString(ss.str());
	std::stringstream hs;
	hs << "HIGHEST RESULT : " << this->highpoints;
	this->HighestPoints.setString(hs.str());

	// movment bar
	//this->ship->setHp(5);
	float hpPercent = static_cast<float>(this->ship->getHp()) / this->ship->getHpmax();
	this->hpbar.setSize(sf::Vector2f(200.f * hpPercent, this->hpbar.getSize().y));
}

void Game::initMap()
{
	if (!this->mapTexture.loadFromFile("Textures/aaaa.jpg"))
	{
		std::cout << "Problem with map" << "\n";
	}
	this->map.setTexture(this->mapTexture);
}

void Game::renderMap()
{
	this->window->draw(this->map);
}

void Game::resetGame()
{
	for (auto* bullet : this->bullets)
	{
		delete bullet;
	}
	this->bullets.clear();

	for (auto* enemy : this->enemies)
	{
		delete enemy;
	}
	this->enemies.clear();

	this->points = 0;
	this->ship->setHp(20);
	this->ship->setPosition(500.f, 500.f);
	this->BestScore();
	this->initBestScore();
	this->InMenu = false;
}

void Game::updateMap()
{

}

void Game::updateCollison()
{
	if (this->ship->getBounds().left < 0.f)
	{
		this->ship->setPosition(0.f, this->ship->getBounds().top);//left
	}
	if (this->ship->getBounds().top < 0.f)
	{
		this->ship->setPosition(this->ship->getBounds().left, 0.f);//top
	}
	if (this->ship->getBounds().left + this->ship->getBounds().width >= this->window->getSize().x)
	{
		this->ship->setPosition(this->window->getSize().x - this->ship->getBounds().width, this->ship->getBounds().top);//right
	}
	if (this->ship->getBounds().top + this->ship->getBounds().height >= this->window->getSize().y)
	{
		this->ship->setPosition(this->ship->getBounds().left, this->window->getSize().y - this->ship->getBounds().height);//bot
	}
}
void Game::initVariables()
{
	this->points = 0;
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();

				this->enemies[i]->setDeadStyle(DEAD::SHOOT);

				std::cout << *this->enemies[i] << "\n";

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}


void Game::updateEnemies()
{
	//Spawning
	if (this->points <= 80)
	{
		this->spawnTimer += 0.1f;
	}
	else
	{
		this->spawnTimer += this->points / 600.f; //0.5f
	}
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();
		if (this->points >= 80)
		{
			enemy->setSpeed(this->points / 80.f);
		}
		//Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy;
			enemy->setDeadStyle(DEAD::FELL);

			std::cout << *enemy << "\n";

			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		//Enemy player collision
		else if (enemy->getBounds().intersects(this->ship->getBounds()))
		{
			this->ship->losehp(this->enemies.at(counter)->getDmg());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}

		++counter;
	}
}

void Game::BestScore()
{
	//int score = 0;
	if (std::stoi(highpoints) <= points)
	{
		std::ofstream out("Save/best_score.txt", std::ios::trunc);
		out << std::to_string(points);
		out.close();
	}
}

void Game::initBestScore()
{
	std::ifstream input("Save/best_score.txt");
	std::getline(input, this->highpoints);
	input.close();
}