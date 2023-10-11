#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include "SFML/Graphics.hpp"

#include "Animation.h"
#include "Object.h"


namespace pt {
	class AnimationManager : public Object {
	public:
		AnimationManager(ObjectPtr parent = nullptr);
		AnimationManager(const std::string& name, ObjectPtr parent = nullptr);

		void addAnimation(const std::string& name, const std::vector<std::string>& fileNames, float speed = 100);
		void setAnimation(const std::string& name);
		void setAnimationSpeed(const std::string& name, float speed);

		sf::FloatRect getSpriteRect() const;

		void update(float time);
		void draw(sf::RenderTarget& target, const sf::Vector2f& possition = { 0,0 }, float angle = 0);

	private:
		std::string _name;
		sf::Sprite _sprite;
		std::string _currentAnimation;
		std::unordered_map<std::string, Animation> _animMap;
	};
}

