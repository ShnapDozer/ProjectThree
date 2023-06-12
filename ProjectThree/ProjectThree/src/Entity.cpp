#include "Entity.h"

#include "GameApplication.h"
#include "InputController.h"

namespace pt
{

	WorldObject::WorldObject(const std::string& name, const sf::Vector2f& startPosition, ObjectPtr parent) 
		: Object(parent), _name(name), _position(startPosition)
	{
		_collision = false;
	}

	std::string WorldObject::getName() const
	{
		return _name;
	}

	void WorldObject::setName(std::string name)
	{
		_name = name;
	}

	sf::Vector2f WorldObject::getPosition() const
	{
		return _position;
	}

	void WorldObject::setPosition(sf::Vector2f position)
	{
		_position = position;
	}

	bool WorldObject::getCollision() const
	{
		return _collision;
	}

	bool WorldObject::checkCollisionWithObjects(const std::vector<TmxObject>& solidObjects) const
	{
		for (auto it : solidObjects)
		{ 
			if (P_intersectRect(it._polygon, this->getRect())) {
				return true;
			}
		}

		return false;
	}

	sf::FloatRect WorldObject::getRect() const
	{
		return _rect;
	}

	void WorldObject::setRect(const sf::FloatRect &rect)
	{
		_rect = rect;
	}


	Entity::Entity(const std::string& name, const sf::Vector2f& startPosition, ObjectPtr parent)
		: WorldObject(name, startPosition, parent)
	{
		_die = false;
	}

	void Entity::setAnimManager(const AnimationManager& animManager)
	{
		_animManager = animManager;
	}

	AnimationManager Entity::getAnimManager() const
	{
		return _animManager;
	}

	void Entity::selectAnimation(const std::string &name)
	{
		_animManager.setAnimation(name);
	}

	void Entity::drawAnimation(sf::RenderTarget& target)
	{
		_animManager.draw(target, _position);
	}

	Hero::Hero(const std::string& name, const sf::Vector2f& startPosition, ObjectPtr parent) 
		: Entity(name, startPosition, parent)
	{
		dx = 0;
		dy = 0;
		vector = 0;
		rotation_rad = 0;
		rotation_grad = 0;
	}

	void Hero::update(double time)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			auto inputController = GameApplication::getInputController();
			auto mousPosition = inputController->getMousPosition();

			rotation_rad = std::atan2(mousPosition.y - _position.y, mousPosition.x - _position.x);
			rotation_grad = rotation_rad * 180.f / 3.1415;
			vector = (pow(mousPosition.y - _position.y, 2)) + (pow(mousPosition.x - _position.x, 2));

			if (false) {
				State = state::up_left;

			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				State = state::up_right;

			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				State = state::down_left;

			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				State = state::down_right;

			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				State = state::left;
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				State = state::right;

			} else if (rotation_grad <= -80 && rotation_grad >= -100) {
				State = state::up;

			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				State = state::down;

			} else State = state::stay;

			if (vector < 10000) {
				dx = 0.05 * std::cos(std::atan2(mousPosition.y - _position.y, mousPosition.x - _position.x));
				dy = 0.05 * std::sin(std::atan2(mousPosition.y - _position.y, mousPosition.x - _position.x));
			} else {
				dx = 0.1 * std::cos(std::atan2(mousPosition.y - _position.y, mousPosition.x - _position.x));
				dy = 0.1 * std::sin(std::atan2(mousPosition.y - _position.y, mousPosition.x - _position.x));
			}
		}

		_animManager.update(time);

		//_collision = checkCollisionWithObjects(Solid_Vec);
		_collision = false;

		_position.x += dx * time;
		_position.y += dy * time;

		dx = 0;
		dy = 0;
	}
	void NPC::update(double time)
	{
		_animManager.update(time);

		_collision = false; // checkCollisionWithObjects(Solid_Vec);

		auto inputController = GameApplication::getInputController();
		auto mousPosition = inputController->getMousPosition();

		interaction = _animManager.getSpriteRect().contains(mousPosition) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

		_position.x += dx * time;
		_position.y += dy * time;

		dx = 0;
		dy = 0;
	}
}