#pragma once

#include <iostream>
#include <String> 
#include <vector>
#include <ctime>


#include <SFML/Graphics.hpp>
#include "TMXLevel.h"

#include "Anim.h"


enum class state
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

class Entity 
{
public:
	
	Entity(std::string name, const sf::Vector2f& posS = { 0.f,0.f });

	bool Collision() const;

	bool Check_Collision(const std::vector<TmxObject>& Solid_Vec) const;

	sf::Vector2f GetPoss() const;

	sf::FloatRect GetRect() const;

	std::string GetName() const;

	void AddAnim(std::string name, std::string file, float speed, int frames);

	void SetAnim_Mg(AnimManager& A);

	void ChoiseAnim(std::string Name);

	void Draw(sf::RenderTarget& target);

	virtual std::map<std::string, float> GetAllState() const = 0;

	virtual void Update(float time, const sf::Vector2f& map_Pos, bool ImGui, const std::vector<TmxObject>& Solid_Vec) = 0;

	static std::map <std::string, AnimManager*> GetMembers();
	
protected:

	bool life, collision;

	std::string Name;

	AnimManager Main;
	sf::Vector2f posA;

	static std::map <std::string, AnimManager*> Members;
};

class Hero : public Entity
{
public:
	
	Hero(std::string name, const sf::Vector2f& posS = { 0,0 });

	void Update(float time, const sf::Vector2f& map_Pos, bool ImGui, const std::vector<TmxObject>& Solid_Vec)override;
	
	std::map<std::string, float> GetAllState() const override;

private:

	float dx = 0;
	float dy = 0;
	float vector = 0;
	float rotation_rad = 0;
	float rotation_grad = 0;

	state State = state::stay;
};

class NPC : public Entity
{
public:
	NPC(std::string name, const sf::Vector2f& posS = { 0,0 })
		: Entity(name, posS), interaction(false) {}

	void Update(float time, const sf::Vector2f& map_Pos, bool ImGui, const std::vector<TmxObject>& Solid_Vec)override
	{
		Main.tick(time);

		collision = Check_Collision(Solid_Vec);
		interaction = Main.GetRect().contains(map_Pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !ImGui;

		posA.x += dx * time;
		posA.y += dy * time;
		dx = 0;
		dy = 0;
	}

	std::map<std::string, float> GetAllState() const override 
	{
		std::map<std::string, float> AllState;
		AllState["X"] = posA.x;
		AllState["Y"] = posA.y;
		AllState["Is Life"] = life;
		AllState["Collision"] = collision;

		return AllState;
	}

private:

	float dx = 0;
	float dy = 0;

	bool interaction;

	state State = state::stay;
};