#pragma once
#include <string> 
#include <vector>

#include <SFML/Graphics.hpp>

#include "Defines.h"


namespace pt
{
	class Entity;
	class Hero;
	class LevelManager;

	class EntityManager
	{
	public:

		EntityManager(LevelManagerPtr levelManager);

		void update(double time); 
		void draw(sf::RenderTarget& Target);

		std::vector<EntityPtr> getEntitys();

		std::shared_ptr<Hero> getHero();
		sf::Vector2f getHeroPosition() const;

	private:

		HeroPtr _hero;
		std::vector<EntityPtr> _entitys;
	};
}