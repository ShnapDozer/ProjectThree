#pragma once

#include <SFML/Graphics.hpp>


class InputController {
public:
	InputController();

	void update();

	sf::Vector2f getMousPosition();


private:
	sf::Vector2f _mouseCoordinate;
};