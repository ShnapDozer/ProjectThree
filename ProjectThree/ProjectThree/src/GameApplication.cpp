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
	RenderWindowPtr GameApplication::m_mainWindow = nullptr;
	ImWindowsManagerPtr GameApplication::_imWindowsManager = nullptr;
	InputControllerPtr GameApplication::_inputController = nullptr;
	
	EntityManagerPtr GameApplication::_entityManager = nullptr;
	LevelManagerPtr GameApplication::_levelManager = nullptr;

	AnimationManagersMapPtr GameApplication::_animationManagers = nullptr;

	std::unordered_map<std::string, GameAppParameter>  GameApplication::m_parametersMap;

	GameApplication::GameApplication(int argc, char* argv[]) 
		: Object()
	{
		this->setParameter("appConfig",				std::string{"configs/applicationConfig.xml"});
		this->setParameter("animationsConfig",		std::string{"configs/animations.xml"});
		this->setParameter("windowsConfig",			std::string{"configs/windows.xml"});
		this->setParameter("zoomOut",				0.75f);
		this->setParameter("zoomIn",				1.25f);
		this->setParameter("gameWindowInFocus",		true);
		this->setParameter("timeDiv",				double{ 800 });

		processArguments(argc, argv);

		_animationManagers = std::make_shared<std::unordered_map<std::string, std::shared_ptr<AnimationManager>>>();

		this->initRenderer();

		_levelManager = std::make_shared<LevelManager>();
		_levelManager->addLevel("01", "Data/Levels/Isometric/01.tmx");

		const std::string animationConfigPath = std::get<std::string>(getParameter("animationsConfig"));
		pt::LoadingManager::loadAnimation(animationConfigPath);

		_inputController = std::make_shared<InputController>();

		_entityManager = std::make_shared<EntityManager>(_levelManager);

		_imWindowsManager = std::make_shared<ImWindowManager>();
		_imWindowsManager->showWindow("MainWindow");

		srand(time(NULL));
	}

	void GameApplication::processArguments(int argc, char* argv[])
	{

	}

	void GameApplication::initRenderer()
	{
		Settings configFile;
		const std::string appConfigPath = std::get<std::string>(getParameter("appConfig"));
		configFile.openFile(appConfigPath);

		sf::VideoMode mode;
		mode.height = configFile.getIntAttribute("mainWindow", "VideoModeHeight");
		mode.width = configFile.getIntAttribute("mainWindow", "VideoModeWidth");

		this->setParameter("VideoModeHeight", (int)mode.height);
		this->setParameter("VideoModeWidth", (int)mode.width);

		m_mainWindow = std::make_shared<sf::RenderWindow>(mode, "ProjectThree");
		m_mainWindow->setVerticalSyncEnabled(true);
		m_mainWindow->setKeyRepeatEnabled(false);

		sf::Image windowIcon;
		windowIcon.loadFromFile("Data/icon.png");
		m_mainWindow->setIcon(32, 32, windowIcon.getPixelsPtr());

		_mainView = std::make_shared<sf::View>();
		_mainView->setCenter(0, 0);
	}

	void GameApplication::processEvents()
	{
		sf::Event event;
		while (m_mainWindow->pollEvent(event))
		{
			_imWindowsManager->processEvent(event);
			switch (event.type)
			{
			case sf::Event::Closed:
				m_mainWindow->close();
				break;
			case sf::Event::Resized:
				m_mainWindow->getSize();
				break;
			case sf::Event::MouseWheelScrolled:
				if (!_imWindowsManager->inFocus()) {
					if (event.mouseWheelScroll.delta > 0) { _mainView->zoom(std::get<float>(getParameter("zoomOut"))); }
					if (event.mouseWheelScroll.delta < 0) { _mainView->zoom(std::get<float>(getParameter("zoomIn"))); }
				}
				break;
			case sf::Event::LostFocus:
				setParameter("gameWindowInFocus", false);
				break;
			case sf::Event::GainedFocus:
				setParameter("gameWindowInFocus", true);
				break;

			}
		}
	}

	void GameApplication::update()
	{
		sf::Time time = _clock.restart();
		double elapsedTime = time.asMicroseconds() / std::get<double>(this->getParameter("timeDiv"));

		this->processEvents();

		if (std::get<bool>(this->getParameter("gameWindowInFocus")))
		{
			_inputController->update();
			_imWindowsManager->update(time);
			_entityManager->update(elapsedTime);
		}
	}

	void GameApplication::draw()
	{
		sf::RenderTarget& target = *m_mainWindow;

		_mainView->setCenter(_entityManager->getHeroPosition());

		m_mainWindow->clear();

		m_mainWindow->setView(*_mainView);

		_levelManager->draw(target);

		for (auto it : _levelManager->getGroupObjects("Solid")) {
			it.draw(target, sf::Color::Blue);
		}

		_entityManager->draw(target);
		_imWindowsManager->draw();

		m_mainWindow->display();
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
		while (m_mainWindow->isOpen())
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

	GameAppParameter GameApplication::getParameter(const std::string& key)
	{
		auto constant = m_parametersMap.find(key);
		if (constant != m_parametersMap.end()) {
			return constant->second;
		}

		return GameAppParameter();
	}

	void GameApplication::setParameter(const std::string& key, GameAppParameter value)
	{
		m_parametersMap[key] = value;
	}

	RenderWindowPtr GameApplication::getRenderWindow()
	{
		return m_mainWindow;
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
