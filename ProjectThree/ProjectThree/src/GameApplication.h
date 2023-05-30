#pragma once

#include <SFML/Graphics.hpp>

#include "Object.h"

namespace pt
{
	#define StringList std::vector <std::string>
	#define RenderWindowPtr std::shared_ptr<sf::RenderWindow>
	#define UserInterfacePtr std::shared_ptr<WindowManager>
	#define InputControllerPtr std::shared_ptr<InputController>
	
	class EntityManager;
	class Ex;
	class Hero;
	class InputController;
	class Level_Manager;
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

	private:

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

		bool _windowFocus;
		double _elapsedTime;

		sf::Image _windowIcon;
		std::shared_ptr<sf::View> _mainView;

		sf::Clock _clock;
		sf::Clock _deltaClock;

		sf::Vector2f _mouseCoordinate;
		std::map <std::string, std::string> _levelsMap;

		std::shared_ptr<Level_Manager>     Levels_M;
		std::shared_ptr<EntityManager>    Entity_M;
		std::shared_ptr<Scripts_Manager>  Scripts_M;
		

		std::shared_ptr<Hero> hero;

		std::shared_ptr<Ex>       Anim_EX;
		std::shared_ptr<Ex> Iso_Levels_EX;
		std::shared_ptr<Ex> Hex_Levels_EX;
		std::shared_ptr<Ex> Ort_Levels_EX;
		std::shared_ptr<Ex>    Scripts_EX;
	};
}

