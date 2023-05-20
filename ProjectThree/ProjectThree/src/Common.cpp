#include "Common.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui-sfml.h"

void Common::PrintState(std::map<std::string, float> a)
{
	for (auto it = a.begin(); it != a.end(); ++it)
	{
		ImGui::Value(it->first.c_str(), it->second);
	}
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
