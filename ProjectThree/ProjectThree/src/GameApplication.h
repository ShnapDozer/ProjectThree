#pragma once

#include <SFML/Graphics.hpp>

#include "Object.h"
#include "Timer.h"

namespace pt
{
	#define StringList std::vector <std::string>
	#define RenderWindowPtr std::shared_ptr<sf::RenderWindow>
	#define UserInterfacePtr std::shared_ptr<WindowManager>
	#define InputControllerPtr std::shared_ptr<InputController>

	#define AnimationManagerPtr std::shared_ptr<AnimationManager>
	#define LevelManagerPtr std::shared_ptr<LevelManager>
	#define EntityManagerPtr std::shared_ptr<EntityManager>
	#define ScriptManagerPtr std::shared_ptr<Scripts_Manager>
	
	class AnimationManager;
	class EntityManager;
	class Ex;
	class Hero;
	class InputController;
	class LevelManager;
	class Scripts_Manager;
	class WindowManager;

	class GameApplication : public Object
	{

	public:

		GameApplication(int argc, char* argv[]);

		void processArguments(int argc, char* argv[]);
		int run();

		static RenderWindowPtr getRenderWindow();
		static UserInterfacePtr getUserInterface();

		static InputControllerPtr getInputController();

		static AnimationManagerPtr getAnimationManager();
		static EntityManagerPtr getEntityManager();
		static LevelManagerPtr getLevelManager();
		static ScriptManagerPtr getScriptManager();
		
	private:

		void checkConfigFile();

		void initRenderer(sf::VideoMode mode);

		void updateClock();
		void processEvents();
		void gameLoop();

		void cleanup();

		void update();
		void draw();

		void hideConsolWindow();

		static RenderWindowPtr _mainWindow;
		static UserInterfacePtr _userInterface;
		static InputControllerPtr _inputController;
		
		static AnimationManagerPtr _animationManager;
		static EntityManagerPtr _entityManager;
		static ScriptManagerPtr _scriptManager;
		static LevelManagerPtr _levelManager;

		std::shared_ptr<sf::View> _mainView;
		
		bool _windowFocus;
		double _elapsedTime;
		
		sf::Clock _clock;
		sf::Clock _deltaClock;
		Timer<GameApplication> _updateConfigTimer;

		std::shared_ptr<Ex>       Anim_EX;
		std::shared_ptr<Ex> Iso_Levels_EX;
		std::shared_ptr<Ex> Hex_Levels_EX;
		std::shared_ptr<Ex> Ort_Levels_EX;
		std::shared_ptr<Ex>    Scripts_EX;
	};
}

