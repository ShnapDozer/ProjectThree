#pragma once
#include <string>

#include <SFML/Graphics.hpp>

#include "Object.h"
#include "GameApplication.h"


namespace pt {

	class Entity;

	class EntityFactory {
	public:
		static std::shared_ptr<Entity> createEntity(const std::string& type, const std::string& name, sf::Vector2f possition, ScriptManagerPtr scriptManager);
	};
}

