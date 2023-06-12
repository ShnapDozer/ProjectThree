#include "EntityFactory.h"

#include "GameApplication.h"

EntityPtr pt::EntityFactory::createEntity(const std::string& type, const std::string& name, sf::Vector2f possition)
{
	auto animationManagersMap = GameApplication::getAnimationManagersMap();

	if (type == "Hero") {
		
		auto hero = std::make_shared<Hero>(name, possition);
		if (animationManagersMap->find(type) != animationManagersMap->end()) {
			hero->setAnimManager(*animationManagersMap->at(type));
		}

		return hero;
	}
	else if (type == "NPC") {
		return std::make_shared<NPC>(name, possition);
	}

	return std::shared_ptr<Entity>();
}
