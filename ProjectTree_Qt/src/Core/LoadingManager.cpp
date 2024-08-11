#include "LoadingManager.h"

#include "AnimationManager.h"
#include "GameApplication.h"
#include "Settings.h"

namespace pt
{
	void pt::LoadingManager::loadAnimation(const std::string& configFile)
	{
		Settings animationConfig;
		if (animationConfig.openFile(configFile)) {

			auto animationManagersMap = GameApplication::getAnimationManagersMap();
			animationManagersMap->clear();

			for (auto managerName : animationConfig.childGroups()) {
				const std::string defaultAnimation = animationConfig.getStrAttribute(managerName, "DefaultAnimation");

				(*animationManagersMap)[managerName] = std::make_shared<AnimationManager>(managerName);

				for (auto animationName : animationConfig.childGroups(managerName)) {
					const float speed = animationConfig.getDoubleAttribute(managerName + '/' + animationName, "Speed");

					StringList framePaths;
					for (auto frame : animationConfig.childGroups(managerName + '/' + animationName)) {
						framePaths.push_back(animationConfig.getStrState(managerName + '/' + animationName + '/' + frame));
					}

					(*animationManagersMap)[managerName]->addAnimation(animationName, framePaths, speed);
				}

				(*animationManagersMap)[managerName]->setAnimation(defaultAnimation);
			}
		}
	}
}