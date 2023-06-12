#pragma once

#include "Defines.h"

#include "ImWindow.h"
#include "Object.h"

namespace pt
{
	class ImWindowManager : public Object
	{
	public:
		ImWindowManager(const std::string& configPath, ObjectPtr parent = nullptr);

		void processEvent(const sf::Event& event);

		void update(sf::Time elapsedTime);
		void work();
		void draw();

		bool inFocus();

	private:
		std::vector<ImWindowPtr> windows;
	};
}