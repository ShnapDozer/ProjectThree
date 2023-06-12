#include "Common.h"

#include <sstream>
#include <chrono>
#include <thread>

#include "ImGui/imgui.h"
#include "ImGui/imgui-sfml.h"




void Common::PrintState(std::map<std::string, float> a)
{
	for (auto it = a.begin(); it != a.end(); ++it)
	{
		ImGui::Value(it->first.c_str(), it->second);
	}
}

std::vector<std::string> Common::splitByChar(const std::string& text, char separator)
{
	StringList splitString;
	std::stringstream stream(text);
	std::string segment;


	while (std::getline(stream, segment, separator)) {
		splitString.push_back(segment);
	}

	return splitString;
}

bool Common::checNameAnim(StringList animNames, std::string name)
{
	for (auto animName : animNames) {
		if (animName == name) {
			return true;
		}
	}
	return false;
}

template<typename T>
std::vector<std::string> Common::MapToString(std::map<std::string, T> a)
{
	std::vector <std::string> result;
	for (auto it = a.begin(); it != a.end(); ++it) {
		result.push_back(it->first);
	}
	return result;
}

sf::Color Common::ParseColor(const std::string& hexRGB)
{
	char* pEnd = nullptr;
	const long hexValue = strtol(hexRGB.c_str(), &pEnd, 16);
	if (*pEnd != '\0')
	{
		throw std::runtime_error(hexRGB + " is not valid hex-encoded RGB color");
	}

	const uint8_t red = uint8_t((hexValue >> 16) % 256);
	const uint8_t green = uint8_t((hexValue >> 8) % 256);
	const uint8_t blue = uint8_t(hexValue % 256);

	return sf::Color(red, green, blue);
}

float Common::ParseFloat(const std::string& str)
{
	char* pEnd = nullptr;
	const float value = strtof(str.c_str(), &pEnd);

	return value;
}
