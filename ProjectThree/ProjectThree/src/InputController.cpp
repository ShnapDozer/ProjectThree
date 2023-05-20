#include "InputController.h"

#include "GameApplication.h"


ProjectThree::InputController::InputController()
{
	_mousePosition = {0.f,0.f};
}

void ProjectThree::InputController::update()
{
	auto renderWindow = GameApplication::getRenderWindow();
	_mousePosition = renderWindow->mapPixelToCoords(sf::Mouse::getPosition(*renderWindow));
}

sf::Vector2f ProjectThree::InputController::getMousPosition()
{
	return _mousePosition;
}
