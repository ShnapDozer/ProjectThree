#include "EntityManager.h"

#include <iostream>

#include "AnimationManager.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "GameApplication.h"
#include "LevelManager.h"

namespace pt
{

	EntityManager::EntityManager(LevelManagerPtr levelManager)
	{
		auto entityObjects = levelManager->getGroupObjects("Entity");

		for (auto &entityObject : entityObjects) {
			auto entity = EntityFactory::createEntity(entityObject.type, entityObject.name, entityObject.possition);
			
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