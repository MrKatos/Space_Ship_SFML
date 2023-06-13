#pragma once

#include <cstdlib>
#include <ctime>

#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#include<map>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include"Ship.h"
#include"Shoot.h"
#include"Enemy.h"
#include"Menu.h"

class Game : public Menu
{
private:

	sf::RenderWindow* window;

	//resorces
	std::map<std::string, sf::Texture*> textures;

	std::vector<Shoot*> bullets;

	//ship
	Ship* ship;

	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;
	//Enemy* enemy; //tu by³e enemies


	//GUI
	sf::Font font;
	sf::Text pointText;//pounkty w grze
	sf::Text HighestPoints;
	std::string highpoints;

	sf::Text GameOver;
	sf::Text HP;
	// map
	sf::Texture mapTexture;
	sf::Sprite map;


	//points

	bool Loose = false;

	unsigned points;

	void initMap();

	void initGui();

	void initWindow();
	void initTextures();


	void initShip();
	void initEnemies();

	//ship gui
	sf::RectangleShape hpbar;
	sf::RectangleShape hpbarback;

	//
	//Menu menu;
	bool InMenu = true;
	void initMenu();
	//

public:
	Game();
	~Game();

	void run();

	void BestScore();
	void initBestScore();

	//void updateEnemiesAndBullets();
	void updateEnemies();
	void updateCombat();

	void updateMap();
	void updateCollison();
	void renderMap();

	void resetGame();

	void initVariables(); //inint system

	void updateGui();
	void renderGui();


	void updatePollEvents();
	void Input();
	void updateBullets();

	void updateMenu();
	void update();
	virtual void render() override;

};

