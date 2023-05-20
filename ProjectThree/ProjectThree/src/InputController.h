#pragma once

#include <SFML/Graphics.hpp>

#include "Object.h"

namespace ProjectThree {

	class InputController : public Object
	{
	public:
		InputController();

		void update();

		sf::Vector2f getMousPosition();


	private:
		sf::Vector2f _mousePosition;
	};
}