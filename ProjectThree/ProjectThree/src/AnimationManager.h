#pragma once

#include <map>
#include <string>
#include <vector>

#include "SFML/Graphics.hpp"

#include "Animation.h"
#include "Object.h"


namespace pt {
	
	class AnimationManager : public Object {
	public:

		AnimationManager(const std::string& name = "Test", ObjectPtr parent = nullptr);

		void create(const std::string& name, const std::string& file, float speed, int frames, bool loading = true);

		void loadAnim(const std::vector<std::string>& animationNames);

		void loadAllAnim();

		void tick(float time);

		void set(const std::string& name);

		void setAnimList(const std::map<std::string, Animation>& animationMap);

		void setAnimSpeed(const std::string& name, float speed);

		void draw(sf::RenderTarget& target, const sf::Vector2f& posA = { 0,0 }, float angle = 0);

		sf::FloatRect GetRect() const;

		std::string _name;
		std::map<std::string, Animation> _animList;

	private:
		sf::Sprite _sprite;
		std::string _currentAnimation;
	};
}

