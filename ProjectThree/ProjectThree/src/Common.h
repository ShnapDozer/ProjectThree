#pragma once

#include <map>
#include <string>
#include <vector>
#include <thread>

#include "SFML/Graphics.hpp"

#include "Defines.h"

namespace Common {
	class AnimManager;

	template <typename T>
	std::vector <std::string> MapToString(std::map <std::string, T> a);
	bool checNameAnim(StringList animNames, std::string name);

	void PrintState(std::map<std::string, float> a);
	
	sf::Color ParseColor(const std::string& hexRGB); // Parses hex-encoded RGB like "6d9fb9"
	float ParseFloat(const std::string& str);	

	StringList splitByChar(const std::string & text, char separator);

}

