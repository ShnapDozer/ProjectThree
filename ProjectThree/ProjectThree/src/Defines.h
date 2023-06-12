#pragma once

#include <memory>

#define StringList std::vector <std::string>

#define RenderWindowPtr std::shared_ptr<sf::RenderWindow>
#define InputControllerPtr std::shared_ptr<InputController>

#define EntityPtr std::shared_ptr<pt::Entity>
#define HeroPtr std::shared_ptr<pt::Hero>
#define ObjectPtr std::shared_ptr <pt::Object>
#define ImWindowPtr std::shared_ptr<pt::ImWindow>

#define AnimationManagerPtr std::shared_ptr<AnimationManager>
#define EntityManagerPtr std::shared_ptr<EntityManager>
#define LevelManagerPtr std::shared_ptr<LevelManager>
#define ImWindowsManagerPtr std::shared_ptr<ImWindowManager>

#define AnimationManagersMapPtr  std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<AnimationManager>>>