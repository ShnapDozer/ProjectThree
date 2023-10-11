#pragma once

#include "Animation.h"

namespace pt
{
	Animation::Animation(ObjectPtr parent) : Object(parent)
	{
		_speed = 0;
		_currentFrame = 0;
	}

	Animation::Animation(const std::vector<std::string>& fileNames, float speed, ObjectPtr parent) : Object(parent)
	{
		_speed = speed;
		_currentFrame = 0;

		if (fileNames.empty()) {
			std::cout << "Animation: fileNames is empty! /t .|. /n";
			return;
		}

		sf::Texture T;
		for (auto fileName : fileNames) {
			T.loadFromFile(fileName);
			_textures.push_back(std::move(T));
		}
	}

	void Animation::clear()
	{
		_textures.clear();
	}

	void Animation::setSpeed(float speed) 
	{ 
		_speed = speed; 
	}

	void Animation::update(float time)
	{
		_currentFrame += _speed * time;
		if (_currentFrame > _textures.size()) {
			_currentFrame = 0;
		}
	}

	const sf::Texture* Animation::getCurrentTexture()
	{
		return &_textures[_currentFrame];
	}

}
	

