#include "ImWindowFactory.h"

#include "AddAnimationWindow.h"
#include "MainWindow.h"

ImWindowPtr pt::ImWindowFactory::createWindow(size_t id, const std::string& type, const std::string& name, int possitionX, int possitionY, int width, int height)
{
	if (type == "MainWindow") {
		return std::make_shared<MainWindow>(id, name, ImVec2(width, height), ImVec2(possitionX, possitionY));
	} else if (type == "AddAnimation") {
		return std::make_shared<AddAnimationWindow>(id, name, ImVec2(width, height), ImVec2(possitionX, possitionY));
	}

	return nullptr;
}
