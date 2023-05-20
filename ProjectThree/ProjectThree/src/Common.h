#pragma once

#include <map>
#include <string>
#include <vector>


namespace Common {

	#define StringList std::vector <std::string>

	class AnimManager;

	void PrintState(std::map<std::string, float> a);

	template <typename T>
	std::vector <std::string> MapToString(std::map <std::string, T> a);

	void Hide();

	bool checNameAnim(StringList animNames, std::string name);

}

