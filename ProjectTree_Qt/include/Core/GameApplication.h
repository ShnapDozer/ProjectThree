#pragma once
#include <SFML/Graphics.hpp>

#include "Defines.h"
#include "EntityManager.h"
#include "InputController.h"
#include "Object.h"

namespace pt
{

	class GameApplication : public Object
	{

	public:

        GameApplication(int argc = 0, char* argv[] = nullptr);

        void                                        processArguments(int argc, char* argv[]);
        int                                         run();

        static GameAppParameter                     getParameter(const std::string& key);
        static void                                 setParameter(const std::string& key, GameAppParameter value);

        static RenderWindowPtr                      getRenderWindow();
        static InputControllerPtr                   getInputController();
        static AnimationManagerPtr                  getAnimationManager(const std::string &name);
        static EntityManagerPtr                     getEntityManager();
        static LevelManagerPtr                      getLevelManager();

        static AnimationManagersMapPtr              getAnimationManagersMap();
		
	private:
        void                                        cleanup();
        void                                        draw();
        void                                        gameLoop();
        void                                        hideConsolWindow();
        void                                        initRenderer();
        void                                        processEvents();
        void                                        update();

        static GameAppParameterUMap                 m_parametersMap;
        static RenderWindowPtr                      m_mainWindow;
        static InputControllerPtr                   _inputController;
        static AnimationManagersMapPtr              _animationManagers;
        static EntityManagerPtr                     _entityManager;
        static LevelManagerPtr                      _levelManager;
        ViewPtr                                     _mainView;
        sf::Clock                                   _clock;
	};
}

