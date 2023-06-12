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

#include<iostream>

#include "Animation.h"
#include "Explover.h" 
#include "Entity.h"

#include "EntityManager.h"
#include "LevelManager.h"
#include "LoadingManager.h"
#include "ImWindowManager.h"
#include "InputController.h"

#include "Settings.h"

namespace pt
{
	RenderWindowPtr GameApplication::_mainWindow = nullptr;
	ImWindowsManagerPtr GameApplication::_imWindowsManager = nullptr;
	InputControllerPtr GameApplication::_inputController = nullptr;
	
	EntityManagerPtr GameApplication::_entityManager = nullptr;
	LevelManagerPtr GameApplication::_levelManager = nullptr;

	AnimationManagersMapPtr GameApplication::_animationManagers = nullptr;

	GameApplication::GameApplication(int argc, char* argv[]) : Object()
	{
		_windowFocus = true;

		processArguments(argc, argv);

		_animationManagers = std::make_shared<std::unordered_map<std::string, std::shared_ptr<AnimationManager>>>();

		Settings configFile;
		configFile.openFile("configs/MainConfig.xml");

		sf::VideoMode mode;
		mode.height = configFile.getIntAttribute("mainWindow", "VideoModeHeight");
		mode.width = configFile.getIntAttribute("mainWindow", "VideoModeWidth");
		initRenderer(mode);

		_levelManager = std::make_shared<LevelManager>();
		_levelManager->addLevel("01", "Data/Levels/Isometric/01.tmx");

		Iso_Levels_EX = std::make_shared<Ex>("\\Data\\Levels\\Isometric\\*", "Data/Levels/Isometric/");
		Hex_Levels_EX = std::make_shared<Ex>("\\Data\\Levels\\Hex\\*", "Data/Levels/Hex/");
		Ort_Levels_EX = std::make_shared<Ex>("\\Data\\Levels\\Ortogonal\\*", "Data/Levels/Ortogonal/");
		Scripts_EX = std::make_shared<Ex>("\\Data\\Scripts\\*", "Data/Scripts/");

		pt::LoadingManager::loadAnimation("configs/animations.xml");

		_inputController = std::make_shared<InputController>();

		_entityManager = std::make_shared<EntityManager>(_levelManager);

		_imWindowsManager = std::make_shared<ImWindowManager>("configs/windows.xml");

		_updateConfigTimer.start(1000, this, &GameApplication::checkConfigFile);

		srand(time(NULL));
	}

	void GameApplication::processArguments(int argc, char* argv[])
	{

	}

	void GameApplication::checkConfigFile()
	{
		std::cout << "Work!!!";
	}

	void GameApplication::initRenderer(sf::VideoMode mode)
	{
		_mainWindow = std::make_shared<sf::RenderWindow>(mode, "ProjectThree");
		_mainWindow->setVerticalSyncEnabled(true);
		_mainWindow->setKeyRepeatEnabled(false);

		sf::Image windowIcon;
		windowIcon.loadFromFile("Data/icon.png");
		_mainWindow->setIcon(32, 32, windowIcon.getPixelsPtr());

		_mainView = std::make_shared<sf::View>();
		_mainView->setCenter(0, 0);
	}

	void GameApplication::processEvents()
	{
		sf::Event event;
		while (_mainWindow->pollEvent(event))
		{
			_imWindowsManager->processEvent(event);
			switch (event.type)
			{
			case sf::Event::Closed:
				_mainWindow->close();
				break;
			case sf::Event::Resized:

				break;
			case sf::Event::MouseWheelScrolled:
				if (!_imWindowsManager->inFocus()) {
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
		sf::Time time = _clock.restart();
		double elapsedTime = time.asMicroseconds() / 800;

		this->processEvents();

		_inputController->update();

		if (_windowFocus) {
			_entityManager->update(elapsedTime);
			_imWindowsManager->update(time);
			_imWindowsManager->work();
		}
	}

	void GameApplication::draw()
	{
		sf::RenderTarget& target = *_mainWindow;

		_mainView->setCenter(_entityManager->getHeroPosition());

		_mainWindow->clear();

		_mainWindow->setView(*_mainView);

		_levelManager->draw(target);

		for (auto it : _levelManager->getGroupObjects("Solid")) {
			it.draw(target, sf::Color::Blue);
		}

		_entityManager->draw(target);
		_imWindowsManager->draw();

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

	LevelManagerPtr GameApplication::getLevelManager()
	{
		return _levelManager;
	}

	ImWindowsManagerPtr GameApplication::getImWindowsManager()
	{
		return _imWindowsManager;
	}

	InputControllerPtr GameApplication::getInputController()
	{
		return _inputController;
	}

	AnimationManagersMapPtr GameApplication::getAnimationManagersMap()
	{
		return _animationManagers;
	}
	AnimationManagerPtr GameApplication::getAnimationManager(const std::string& name)
	{
		if (_animationManagers->count(name)) {
			return _animationManagers->at(name);
		} else {
			return AnimationManagerPtr();
		}
		
	}
	EntityManagerPtr GameApplication::getEntityManager()
	{
		return _entityManager;
	}
}
