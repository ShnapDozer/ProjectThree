#include "EntityFactory.h"

#include "Entity.h"
#include "Scripts_Mg.h"

std::shared_ptr<pt::Entity> pt::EntityFactory::createEntity(const std::string& type, const std::string& name, 
	sf::Vector2f possition, ScriptManagerPtr scriptManager)
{
	if (type == "Hero") {
		
		auto hero = std::make_shared<Hero>(name, possition);
		if (!scriptManager->Get_Anim_Manager(name)) {
			hero->setAnimManager(*scriptManager->Get_Anim_Manager(name));
		}

		return hero;
	}
	else if (type == "NPC") {
		return std::make_shared<NPC>(name, possition);
	}

	return std::shared_ptr<Entity>();
}
