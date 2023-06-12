#include "ImWindowFactory.h"

#include "ImWindow.h"

ImWindowPtr pt::ImWindowFactory::createWindow(const std::string& type, const std::string& name, int possitionX, int possitionY, int width, int height)
{
	if (type == "MainWindow") {
		return std::make_shared<MainWindow>(name, ImVec2(width, height), ImVec2(possitionX, possitionY));
	}

	return nullptr;
}
