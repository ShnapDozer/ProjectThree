#pragma once
#include <string>

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Object.h"

namespace pt {

	class Entity;

	class EntityFactory : public Object
	{
	public:
		static EntityPtr createEntity(const std::string& type, const std::string& name, sf::Vector2f possition);
	};
}

