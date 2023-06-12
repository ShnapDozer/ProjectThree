#include "ImWindowManager.h"

#include "GameApplication.h"
#include "Settings.h"
#include "ImWindowFactory.h"

namespace pt
{
	ImWindowManager::ImWindowManager(const std::string& configPath, ObjectPtr parent) 
		: Object(parent)
	{
		auto window = GameApplication::getRenderWindow();
		ImGui::SFML::Init(*window);

		Settings windowsConfig;
		windowsConfig.openFile(configPath);

		for (auto windowType : windowsConfig.childGroups()) {

			const std::string name = windowsConfig.getStrAttribute(windowType, "Name");
			const int positionX = windowsConfig.getDoubleAttribute(windowType, "PossitionX");
			const int positionY = windowsConfig.getDoubleAttribute(windowType, "PossitionY");
			const int width = windowsConfig.getDoubleAttribute(windowType, "Width");
			const int height = windowsConfig.getDoubleAttribute(windowType, "Height");

			auto imWindow = ImWindowFactory::createWindow(windowType, name, positionX, positionY, width, height);

			if (imWindow != nullptr) {
				windows.push_back(imWindow);
			}
		}



		//All_Window.push_back(std::make_shared<MainWindow>("Main", ConsMenuSize, ConsMenuPos));
		//All_Window.push_back(std::make_shared<A_Create_window>("Anim manager", AnothConsMenuSize, AnothConsMenuPos));
		//All_Window.push_back(std::make_shared<L_Create_window>("Level manager", AnothConsMenuSize, AnothConsMenuPos, LM, LvlF));
		//All_Window.push_back(std::make_shared<S_Video_window>("Video", AnothConsMenuSize, AnothConsMenuPos));
		//All_Window.push_back(std::make_shared<Sc_Load_window>("Load Scripts", AnothConsMenuSize, AnothConsMenuPos, E_MG, Scr_M, Scr_F));
	}

	bool ImWindowManager::inFocus()
	{
		return ImGui::GetIO().WantCaptureMouse;
	}

	void ImWindowManager::update(sf::Time elapsedTime)
	{
		auto window = GameApplication::getRenderWindow();
		ImGui::SFML::Update(*window, elapsedTime);
	}

	void ImWindowManager::processEvent(const sf::Event& event)
	{
		ImGui::SFML::ProcessEvent(event);
	}

	void ImWindowManager::work()
	{
		ImGui::StyleColorsLight();
		for (auto it : windows) {
			it->inWork();
		}
	}

	void ImWindowManager::draw() { 
		auto window = GameApplication::getRenderWindow();
		ImGui::SFML::Render(*window);
	}

}


