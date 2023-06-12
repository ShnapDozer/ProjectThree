#pragma once

#include <iostream>
#include <String> 
#include <vector>

#include <SFML/Graphics.hpp>
#include "TMXLevel.h"

#include "AnimationManager.h"
#include "Object.h"

namespace pt
{
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

	class WorldObject : public Object 
	{
	public:
		WorldObject(const std::string& name,  const sf::Vector2f& startPosition = { 0.f,0.f }, ObjectPtr parent = nullptr);

		std::string getName() const;
		void setName(std::string name);

		sf::Vector2f getPosition() const;
		void setPosition(sf::Vector2f position);

		bool getCollision() const;
		bool checkCollisionWithObjects(const std::vector<TmxObject>& solidObjects) const;

		sf::FloatRect getRect() const;
		void setRect(const sf::FloatRect &rect);

	protected:
		bool _collision;

		std::string _name;

		sf::Vector2f _position;
		sf::FloatRect _rect;
	};

	class Entity : public WorldObject
	{
	public:

		Entity(const std::string& name, const sf::Vector2f& startPosition = { 0.f,0.f }, ObjectPtr parent = nullptr);

		void setAnimManager(const AnimationManager& animManager);
		AnimationManager getAnimManager() const;

		void selectAnimation(const std::string &name);
		void drawAnimation(sf::RenderTarget& target);

		virtual void update(double time) = 0;

	protected:

		bool _die;		
		AnimationManager _animManager;
	};

	class Hero : public Entity
	{
	public:

		Hero(const std::string& name, const sf::Vector2f& startPosition = { 0.f,0.f }, ObjectPtr parent = nullptr);
		void update(double time) override;

	private:

		float dx;
		float dy;
		float vector;
		float rotation_rad;
		float rotation_grad;

		state State = state::stay;
	};

	class NPC : public Entity
	{
	public:
		NPC(std::string name, const sf::Vector2f& posS = { 0,0 }, ObjectPtr parent = nullptr)
			: Entity(name, posS, parent), interaction(false) {}

		void update(double time) override;

	private:

		float dx = 0;
		float dy = 0;

		bool interaction;

		state State = state::stay;
	};
}