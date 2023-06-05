#include "EntityManager.h"

#include <iostream>
#include <ctime>

#include "AnimationManager.h"
#include "EntityFactory.h"
#include "LevelManager.h"
#include "Scripts_Mg.h"

namespace pt
{

	EntityManager::EntityManager(LevelManagerPtr levelManager, ScriptManagerPtr scriptManager)
	{
		auto entityObjects = levelManager->getGroupObjects("Entity");

		for (auto &entityObject : entityObjects) {
			auto entity = EntityFactory::createEntity(entityObject.type, entityObject.name, entityObject.possition, scriptManager);
			
			if (entity != nullptr) {
				
				if (entityObject.type == "Hero") {
					_hero = std::static_pointer_cast<Hero>(entity);
					_entitys.push_back(entity);
				} else {
					_entitys.push_back(std::move(entity));
				}
			} else { 
				std::cout << entityObject.name << " - bad object" << std::endl;
			}
		}
	}

	void EntityManager::update(double time)
	{
		_hero->update(time);

		for (auto entity : _entitys) { 
			if (entity != nullptr) {
				entity->update(time);
			}
				
		}
	}

	void EntityManager::draw(sf::RenderTarget& Target)
	{
		_hero->drawAnimation(Target);

		for (auto entity : _entitys) {
			if (entity) {
				entity->drawAnimation(Target);
			}
		}
	}

	void EntityManager::setScript()
	{
		auto scriptManager = GameApplication::getScriptManager();
		if (scriptManager->Get_Anim_Manager(_hero->getName()) != nullptr)
		{
			_hero->setAnimManager(*scriptManager->Get_Anim_Manager(_hero->getName()));
		}

		for (auto entity : _entitys)
		{
			if (scriptManager->Get_Anim_Manager(entity->getName()) != nullptr)
			{
				entity->setAnimManager(*scriptManager->Get_Anim_Manager(_hero->getName()));
			}
		}
	}

	std::shared_ptr<Hero> EntityManager::getHero()
	{
		if (_hero == nullptr) {
			return std::shared_ptr<Hero>();
		}

		return _hero;
	}

	sf::Vector2f EntityManager::getHeroPosition() const
	{
		if (_hero == nullptr) {
			return{ 0.f,0.f };
		}

		return _hero->getPosition();		
	}
}