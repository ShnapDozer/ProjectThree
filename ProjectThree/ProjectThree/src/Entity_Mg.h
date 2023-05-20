#pragma once

#include <iostream>
#include <String> 
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>

#include "Entity.h" 
#include "TmxLevel.h"
#include "Anim.h"
#include "Scripts_Mg.h"

namespace ProjectThree
{

	class EntityManager
	{
	public:

		EntityManager(std::shared_ptr <Level_Manager> L_M, std::shared_ptr <Scripts_Manager> S_M);

		void update(double time); 
		void draw(sf::RenderTarget& Target);

		void setScript();

		std::shared_ptr<Hero> getHero();
		sf::Vector2f getHeroPosition() const;

	private:

		std::shared_ptr<Hero> _hero;
		std::vector<std::shared_ptr<Entity>> _entitys;
		std::vector<TmxObject> entityObjects;
		std::vector<TmxObject> _solidObjects;
		std::shared_ptr <Level_Manager> _levelManager;
		std::shared_ptr <Scripts_Manager> scriptManager;
	};
}