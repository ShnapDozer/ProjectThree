#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <thread>

#include "SFML/Graphics.hpp"
#include "ImGui/imgui.h"

#include "Defines.h"

namespace Common {
	class AnimManager;

	template <typename T>
	StringList map2StringList(std::unordered_map <std::string, T> data);
	
	sf::Color ParseColor(const std::string& hexRGB); // Parses hex-encoded RGB like "6d9fb9"
	float ParseFloat(const std::string& str);	

	StringList splitByChar(const std::string & text, char separator);

}

