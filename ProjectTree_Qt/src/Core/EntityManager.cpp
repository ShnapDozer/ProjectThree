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
			
			auto entity = EntityFactory::createEntity(
				  entityObject.type
				, entityObject.name
				, entityObject.possition
			);
			
			if (entity != nullptr) {
				
				if (entityObject.type == "Hero") {
					m_hero = std::static_pointer_cast<Hero>(entity);
					m_entitys.push_back(entity);
				} else {
					m_entitys.push_back(std::move(entity));
				}
			} else { 
				std::cout << entityObject.name << " - bad object" << std::endl;
			}
		}
	}

	void EntityManager::update(double time)
	{
		m_hero->update(time);

		for (auto entity : m_entitys) { 
			if (entity != nullptr) 
			{
				entity->update(time);
			}
				
		}
	}

	void EntityManager::draw(sf::RenderTarget& Target)
	{
		m_hero->drawAnimation(Target);

		for (auto entity : m_entitys) {
			if (entity) {
				entity->drawAnimation(Target);
			}
		}
	}

	std::vector<EntityPtr> EntityManager::getEntitys()
	{
		return std::vector<EntityPtr>();
	}

	std::shared_ptr<Hero> EntityManager::getHero()
	{
		if (m_hero == nullptr) {
			return std::shared_ptr<Hero>();
		}

		return m_hero;
	}

	sf::Vector2f EntityManager::getHeroPosition() const
	{
		if (m_hero == nullptr) {
			return{ 0.f,0.f };
		}

		return m_hero->getPosition();		
	}
}