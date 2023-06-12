#include "AnimationManager.h"

namespace pt {
	AnimationManager::AnimationManager(ObjectPtr parent) : Object(parent)
	{

	}
	AnimationManager::AnimationManager(const std::string& name, ObjectPtr parent) : _name(name), Object(parent)
	{ 
		 
	}

	void AnimationManager::addAnimation(const std::string& name, const std::vector<std::string>& fileNames, float speed)
	{
		_animMap[name] = Animation(fileNames, speed);
		_currentAnimation = name;
	}

	void AnimationManager::update(float time)
	{
		if (_animMap.find(_currentAnimation) == _animMap.end()) {
			return;
		}
		_animMap[_currentAnimation].update(time);
	}

	void AnimationManager::setAnimation(const std::string& name)
	{
		_currentAnimation = name;
	}

	void AnimationManager::setAnimationSpeed(const std::string& name, float speed)
	{
		_animMap[name].setSpeed(speed);
	}

	void AnimationManager::draw(sf::RenderTarget& target, const sf::Vector2f& possition, float angle)
	{
		
		if (_animMap.find(_currentAnimation) == _animMap.end()) {
			return;
		}

		_sprite.setTexture(*_animMap[_currentAnimation].getCurrentTexture());
		_sprite.setPosition(possition);

		const sf::FloatRect viewportRect = target.getView().getViewport();
		if (viewportRect.intersects(_sprite.getLocalBounds()))
		{
			_sprite.setOrigin(_sprite.getGlobalBounds().height / 2, _sprite.getGlobalBounds().width / 2);
			_sprite.setRotation(angle);
			target.draw(_sprite);
		}
	}

	sf::FloatRect AnimationManager::getSpriteRect() const 
	{ 
		return _sprite.getGlobalBounds(); 
	}
}