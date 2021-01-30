#pragma once

#include <iostream>
#include <String> 
#include <vector>
#include <ctime>


#include <SFML/Graphics.hpp>

#include "Anim.h"


class Entity 
{
protected:
	sf::Vector2f posA;
	bool life, isMove;
	AnimManager Main;
	static std::map <std::string, AnimManager*> Members;
public:
	
	Entity(sf::Vector2f posS = { 0,0 })
	{
		life = 1;
		isMove = 0;
		posA = posS;
	}

	static std::map <std::string, AnimManager*> GetMembers() { return Members; }

	void AddAnim(std::string name, std::string file, float speed, int frames, bool loading = false)
	{
		Main.create(name, file, speed, frames, loading);
	}

	sf::Vector2f GetPoss() { return posA; }

	void Draw(sf::RenderTarget& target)
	{
		Main.draw(target, posA);
	}

	void ChoiseAnim(std::string Name)
	{
		Main.set(Name);
	}

	std::map<std::string, float> GetAllState()
	{
		std::map<std::string, float> AllState;

		AllState["X"] = posA.x;
		AllState["Y"] = posA.y;
		AllState["is_Life"] = life;

		return AllState;
	}
};

class Hero : public Entity
{
private:
	float vector = 0;
	float dx = 0;
	float dy = 0;
	float rotation_rad = 0;
	float rotation_grad = 0;
	enum state 
	{ 
		left, 
		right,
		up, 
		down, 
		up_left, 
		up_right, 
		down_left, 
		down_right, 
		stay 
	};
	state State = stay;

public:
	
	Hero(sf::Vector2f posS = { 0,0 }) :Entity(posS) 
	{
		Members["Hero"] =  &Main;
	}

	void Upd(float time, sf::Vector2f MapPos)
	{

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{

			rotation_rad = std::atan2(MapPos.y - posA.y, MapPos.x - posA.x);
			rotation_grad = rotation_rad * 180 / 3.14159265;
			vector = std::sqrt((pow(MapPos.y - posA.y, 2))+(pow(MapPos.x - posA.x, 2)));

			if (false)
			{
				State = up_left;

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				State = state::up_right;

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				State = state::down_left;

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				State = state::down_right;

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				State = state::left;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				State = state::right;

			}
			else if (rotation_grad <= -80 && rotation_grad >= -100) {
				State = state::up;

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				State = state::down;

			}
			else State = state::stay;

			if(vector < 100)
			{
				dx = 0.05 * std::cos(std::atan2(MapPos.y - posA.y, MapPos.x - posA.x));
				dy = 0.05 * std::sin(std::atan2(MapPos.y - posA.y, MapPos.x - posA.x));
			}
			else 
			{
				dx = 0.1 * std::cos(std::atan2(MapPos.y - posA.y, MapPos.x - posA.x));
				dy = 0.1 * std::sin(std::atan2(MapPos.y - posA.y, MapPos.x - posA.x));
			}
		}

		Main.tick(time);

		posA.x += dx * time;
		posA.y += dy * time;
		dx = 0;
		dy = 0;
	}

	
		
	std::map<std::string, float> GetAllState()
	{
		std::map<std::string, float> AllState;
		AllState["X"] = posA.x;
		AllState["Y"] = posA.y;
		AllState["is_Life"] = life;
		AllState["State"] = State;
		AllState["Rotation"] = rotation_grad;
		AllState["Vector"] = vector;


		return AllState;
	}
};