#include "ImWindowManager.h"

#include "GameApplication.h"
#include "Settings.h"
#include "ImWindowFactory.h"

#include <iostream>

namespace pt
{
	size_t ImWindowManager::_id = 0;

	ImWindowManager::ImWindowManager(ObjectPtr parent)
		: Object(parent)
	{
		auto window = GameApplication::getRenderWindow();
		ImGui::SFML::Init(*window);
	}

	bool ImWindowManager::inFocus()
	{
		return  focus;
	}

	void ImWindowManager::showWindow(const std::string & windowName)
	{
		Settings windowsConfig;
		const std::string windowsConfigPath = std::get<std::string>(GameApplication::getConstant("WindowsConfig"));

		if (windowsConfig.openFile(windowsConfigPath)) {

			for (auto windowType : windowsConfig.childGroups()) {

				const std::string name = windowsConfig.getStrAttribute(windowType, "Name");
				if (name == windowName) {
					const int positionX = windowsConfig.getDoubleAttribute(windowType, "PossitionX");
					const int positionY = windowsConfig.getDoubleAttribute(windowType, "PossitionY");
					const int width = windowsConfig.getDoubleAttribute(windowType, "Width");
					const int height = windowsConfig.getDoubleAttribute(windowType, "Height");

					auto imWindow = ImWindowFactory::createWindow(_id++, windowType, name, positionX, positionY, width, height);

					if (imWindow != nullptr) {
						windows[_id] = imWindow;
					}
				}

			}
		}
		else {
			// TODO: Логика ассертов, пока хз
		}
	}

	void ImWindowManager::closeWindow(size_t id)
	{
		windows.erase(id);
	}

	void ImWindowManager::update(sf::Time elapsedTime)
	{
		auto window = GameApplication::getRenderWindow();
		ImGui::SFML::Update(*window, elapsedTime);
		focus = ImGui::GetIO().WantCaptureMouse;
	}

	void ImWindowManager::processEvent(const sf::Event& event)
	{
		ImGui::SFML::ProcessEvent(event);
	}

	void ImWindowManager::work()
	{
		ImGui::StyleColorsLight();
		for (auto window : windows) {
			window.second->inWork();
		}
	}

	void ImWindowManager::draw() { 
		auto window = GameApplication::getRenderWindow();
		ImGui::SFML::Render(*window);
	}

}


