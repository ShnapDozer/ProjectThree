#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <ctime>
#include <memory>
#include <String>
#include <vector>
#include <Windows.h>
#include <utility>

#include "ImGui_Mg.h"
#include "Anim.h"
#include "Scripts_Mg.h"
#include "Entity.h"
#include "Entity_Mg.h"
#include "TMXLevel.h"
#include "Explover.h" 



class Game
{

public:

	Game(int x, int y);

	void processing();

private:

	void update();

	void draw();
	
	//Main ptr:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<sf::View> view;

	std::shared_ptr<Level_Manager>     Levels_M;
	std::shared_ptr<Entity_Manager>    Entity_M;
	std::shared_ptr<Scripts_Manager>  Scripts_M;
	std::shared_ptr<IMG_Manager>            GUI;

	std::shared_ptr<Hero> hero;

	std::shared_ptr<Ex>       Anim_EX;
	std::shared_ptr<Ex> Iso_Levels_EX;
	std::shared_ptr<Ex> Hex_Levels_EX;
	std::shared_ptr<Ex> Ort_Levels_EX;
	std::shared_ptr<Ex>    Scripts_EX;

	//Main objects:
	sf::Image icon;

	std::map <std::string, std::string> ALL_TMX_Level;

	sf::Vector2i Pos_M;
	sf::Vector2f MapPos;

	sf::Clock deltaClock;
	sf::Clock clock;

	//Support variables:
	bool TmxLev = true;
	bool LoadTmxLev = false;
	bool WindowFocus = true;
	int SelectLev = 0;

	int Wy;
	int Wx;
};

