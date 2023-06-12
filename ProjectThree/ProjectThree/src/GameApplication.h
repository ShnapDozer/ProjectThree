#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

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

		static RenderWindowPtr getRenderWindow();
		static ImWindowsManagerPtr getImWindowsManager();

		static InputControllerPtr getInputController();

		static AnimationManagerPtr getAnimationManager(const std::string &name);
		static EntityManagerPtr getEntityManager();
		static LevelManagerPtr getLevelManager();

		static AnimationManagersMapPtr getAnimationManagersMap();
		
	private:

		void checkConfigFile();

		void initRenderer(sf::VideoMode mode);

		void processEvents();
		void gameLoop();

		void cleanup();

		void update();
		void draw();

		void hideConsolWindow();

		static RenderWindowPtr _mainWindow;
		static ImWindowsManagerPtr _imWindowsManager;
		static InputControllerPtr _inputController;
		
		static AnimationManagersMapPtr _animationManagers;
		static EntityManagerPtr _entityManager;
		static LevelManagerPtr _levelManager;

		std::shared_ptr<sf::View> _mainView;
		
		bool _windowFocus;
		
		sf::Clock _clock;
		Timer<GameApplication> _updateConfigTimer;

		std::shared_ptr<Ex>       Anim_EX;
		std::shared_ptr<Ex> Iso_Levels_EX;
		std::shared_ptr<Ex> Hex_Levels_EX;
		std::shared_ptr<Ex> Ort_Levels_EX;
		std::shared_ptr<Ex>    Scripts_EX;
	};
}

