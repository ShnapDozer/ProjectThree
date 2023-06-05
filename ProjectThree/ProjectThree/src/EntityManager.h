#pragma once
#include <String> 
#include <vector>

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include "GameApplication.h"

namespace pt
{

	class EntityManager
	{
	public:

		EntityManager(LevelManagerPtr levelManager, ScriptManagerPtr scriptManager);

		void update(double time); 
		void draw(sf::RenderTarget& Target);

		void setScript();

		std::shared_ptr<Hero> getHero();
		sf::Vector2f getHeroPosition() const;

	private:

		std::shared_ptr<Hero> _hero;
		std::vector<std::shared_ptr<Entity>> _entitys;
		std::shared_ptr <LevelManager> _levelManager;
	};
}