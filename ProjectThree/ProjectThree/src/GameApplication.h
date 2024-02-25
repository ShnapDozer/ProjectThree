#pragma once

#include <unordered_map>
#include <variant>

#include <SFML/Graphics.hpp>

#include "Defines.h"

#include "Object.h"
#include "Timer.h"

namespace pt
{
	class AnimationManager;
	class EntityManager;
	class Ex;
	class Hero;
	class InputController;
	class LevelManager;
	class Scripts_Manager;
	class ImWindowManager;

	class GameApplication : public Object
	{

	public:

		GameApplication(int argc, char* argv[]);

		void processArguments(int argc, char* argv[]);
		int run();

		static GameAppParameter getParameter(const std::string& key);
		static void setParameter(const std::string& key, GameAppParameter value);

		static RenderWindowPtr getRenderWindow();
		static ImWindowsManagerPtr getImWindowsManager();

		static InputControllerPtr getInputController();

		static AnimationManagerPtr getAnimationManager(const std::string &name);
		static EntityManagerPtr getEntityManager();
		static LevelManagerPtr getLevelManager();

		static AnimationManagersMapPtr getAnimationManagersMap();
		
	private:
		void initRenderer();

		void processEvents();
		void gameLoop();

		void cleanup();

		void update();
		void draw();

		void hideConsolWindow();

		static std::unordered_map<std::string, GameAppParameter> m_parametersMap;

		static RenderWindowPtr m_mainWindow;
		static ImWindowsManagerPtr _imWindowsManager;
		static InputControllerPtr _inputController;
		
		static AnimationManagersMapPtr _animationManagers;
		static EntityManagerPtr _entityManager;
		static LevelManagerPtr _levelManager;

		std::shared_ptr<sf::View> _mainView;
		
		sf::Clock _clock;
	};
}

