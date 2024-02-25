#include "AnimationManager.h"

namespace pt {
	AnimationManager::AnimationManager(ObjectPtr parent) : Object(parent)
	{

	}
	AnimationManager::AnimationManager(const std::string& name, ObjectPtr parent) : m_name(name), Object(parent)
	{ 
		 
	}

	void AnimationManager::addAnimation(const std::string& name, const std::vector<std::string>& fileNames, float speed)
	{
		m_animationsMap[name] = Animation(fileNames, speed);
		m_currentAnimation = name;
	}

	void AnimationManager::update(float time)
	{
		if (m_animationsMap.find(m_currentAnimation) == m_animationsMap.end()) {
			return;
		}
		m_animationsMap[m_currentAnimation].update(time);
	}

	void AnimationManager::setAnimation(const std::string& name)
	{
		m_currentAnimation = name;
	}

	void AnimationManager::setAnimationSpeed(const std::string& name, float speed)
	{
		m_animationsMap[name].setSpeed(speed);
	}

	void AnimationManager::draw(sf::RenderTarget& target, const sf::Vector2f& possition, float angle)
	{
		
		if (m_animationsMap.find(m_currentAnimation) == m_animationsMap.end()) {
			return;
		}

		m_sprite.setTexture(*m_animationsMap[m_currentAnimation].getCurrentTexture());
		m_sprite.setPosition(possition);

		const sf::FloatRect viewportRect = target.getView().getViewport();
		if (viewportRect.intersects(m_sprite.getLocalBounds()))
		{
			m_sprite.setOrigin(m_sprite.getGlobalBounds().height / 2, m_sprite.getGlobalBounds().width / 2);
			m_sprite.setRotation(angle);
			target.draw(m_sprite);
		}
	}

	sf::FloatRect AnimationManager::getSpriteRect() const 
	{ 
		return m_sprite.getGlobalBounds(); 
	}
}