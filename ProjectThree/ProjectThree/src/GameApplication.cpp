#include "GameApplication.h"

#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>

#include "ImGui/imgui-sfml.h"

#include <ctime>
#include <memory>
#include <String>
#include <vector>
#include <Windows.h>
#include <utility>

#include "TMXLevel.h"
#include "WindowManager.h"
#include "Anim.h"
#include "Scripts_Mg.h"
#include "Entity.h"
#include "Entity_Mg.h"
#include "Explover.h" 
#include "InputController.h"

namespace ProjectThree
{
	RenderWindowPtr GameApplication::_mainWindow = nullptr;
	UserInterfacePtr GameApplication::_userInterface = nullptr;
	InputControllerPtr GameApplication::_inputController = nullptr;

	GameApplication::GameApplication(sf::VideoMode mode) : Object()
	{
		_windowFocus = true;
		_elapsedTime = 0;

		initRenderer(mode);

		Levels_M = std::make_shared<Level_Manager>();
		Levels_M->Add_Lvl("01", "Data/Levels/Isometric/01.tmx");


		Iso_Levels_EX = std::make_shared<Ex>("\\Data\\Levels\\Isometric\\*", "Data/Levels/Isometric/");
		Hex_Levels_EX = std::make_shared<Ex>("\\Data\\Levels\\Hex\\*", "Data/Levels/Hex/");
		Ort_Levels_EX = std::make_shared<Ex>("\\Data\\Levels\\Ortogonal\\*", "Data/Levels/Ortogonal/");
		Scripts_EX = std::make_shared<Ex>("\\Data\\Scripts\\*", "Data/Scripts/");

		_inputController = std::make_shared<InputController>();

		Scripts_M = std::make_shared<Scripts_Manager>(*Scripts_EX);

		Scripts_M->Read_Script_An(Scripts_EX->FileVec[2]);

		Entity_M = std::make_shared<EntityManager>(Levels_M, Scripts_M);

		//hero = std::make_shared<Hero>("Hero"/*, Levels_M->Lvl_FirstObject("Hero_Play").poss*/);
		//hero->AddAnim("Walk", "Data/Animation/H", 0.007, 8);

		_userInterface = std::make_shared<WindowManager>(Entity_M, Levels_M, Iso_Levels_EX, Scripts_M, Scripts_EX);

		srand(time(NULL));
	}

	void GameApplication::processArguments(int argc, char* argv[])
	{

	}

	void GameApplication::initSettingsConfig()
	{

	}

	void GameApplication::initRenderer(sf::VideoMode mode)
	{
		_mainWindow = std::make_shared<sf::RenderWindow>(mode, "ProjectThree");
		_mainWindow->setVerticalSyncEnabled(true);
		_mainWindow->setKeyRepeatEnabled(false);

		_windowIcon.loadFromFile("Data/icon.png");
		_mainWindow->setIcon(32, 32, _windowIcon.getPixelsPtr());

		_mainView = std::make_shared<sf::View>();
		_mainView->setCenter(0, 0);
	}

	void GameApplication::updateClock()
	{
		_elapsedTime = _clock.getElapsedTime().asMicroseconds();
		_clock.restart();
		_elapsedTime = _elapsedTime / 800;
	}

	void GameApplication::processEvents()
	{
		sf::Event event;
		while (_mainWindow->pollEvent(event))
		{
			_userInterface->ProcessEvent(event);
			switch (event.type)
			{
			case sf::Event::Closed:
				_mainWindow->close();
				break;
			case sf::Event::Resized:

				break;
			case sf::Event::MouseWheelScrolled:
				if (!_userInterface->inFocus()) {
					if (event.mouseWheelScroll.delta > 0) { _mainView->zoom(0.75); }
					if (event.mouseWheelScroll.delta < 0) { _mainView->zoom(1.35); }
				}
				break;
			case sf::Event::LostFocus:
				_windowFocus = 0;
				break;
			case sf::Event::GainedFocus:
				_windowFocus = 1;
				break;

			}
		}
	}

	void GameApplication::update()
	{
		this->updateClock();
		this->processEvents();

		_inputController->update();

		if (_windowFocus) {
			Entity_M->update(_elapsedTime);
			_userInterface->update(_mainWindow, _deltaClock);
			_userInterface->Work();
		}
	}

	void GameApplication::draw()
	{
		sf::RenderTarget& target = *_mainWindow;

		_mainView->setCenter(Entity_M->getHeroPosition());

		_mainWindow->clear();

		_mainWindow->setView(*_mainView);

		Levels_M->Draw_Lvl(target, _mouseCoordinate);

		for (auto it : Levels_M->Lvl_Solid_Vec()) {
			it.draw(target, sf::Color::Blue);
		}

		Entity_M->draw(target);
		_userInterface->Render(*_mainWindow);

		_mainWindow->display();
	}

	void GameApplication::hideConsolWindow()
	{
		HWND Hide;
		AllocConsole();
		Hide = FindWindowA("ConsoleWindowClass", NULL);
		ShowWindow(Hide, 0);
	}

	void GameApplication::gameLoop()
	{
		while (_mainWindow->isOpen())
		{
			update();
			draw();
		}
	}

	void GameApplication::cleanup()
	{
		ImGui::SFML::Shutdown();
	}

	int GameApplication::run()
	{
		this->gameLoop();
		this->cleanup();

		return 0;
	}

	RenderWindowPtr GameApplication::getRenderWindow()
	{
		return _mainWindow;
	}

	UserInterfacePtr GameApplication::getUserInterface()
	{
		return _userInterface;
	}

	InputControllerPtr GameApplication::getInputController()
	{
		return _inputController;
	}

	

	

}
