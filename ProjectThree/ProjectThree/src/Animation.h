#pragma once

#include <iostream>
#include <string> 
#include <vector>

#include <SFML/Graphics.hpp>

#include "Defines.h"
#include "Object.h"


namespace pt
{
	class Animation : public Object	{
	public:


		Animation(ObjectPtr parent = nullptr);
		Animation(const std::vector<std::string> &fileNames, float speed, ObjectPtr parent = nullptr); // speed 0.7 normal

		bool load();
		void clear();
		void setSpeed(float speed);
		void update(float time);

		const sf::Texture* getCurrentTexture();



	private:
		float _speed;
		float _currentFrame;
		
		std::vector <sf::Texture> _textures;
	};
}