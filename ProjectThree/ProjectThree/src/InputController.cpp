#include "InputController.h"

#include "GameApplication.h"


pt::InputController::InputController()
{
	_mousePosition = {0.f,0.f};
}

void pt::InputController::update()
{
	auto renderWindow = GameApplication::getRenderWindow();
	_mousePosition = renderWindow->mapPixelToCoords(sf::Mouse::getPosition(*renderWindow));
}

sf::Vector2f pt::InputController::getMousPosition()
{
	return _mousePosition;
}
