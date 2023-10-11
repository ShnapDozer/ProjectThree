#pragma once

#include <unordered_map>

#include "Defines.h"

#include "ImWindow.h"
#include "Object.h"

namespace pt
{
	class ImWindowManager : public Object
	{
	public:
		ImWindowManager(ObjectPtr parent = nullptr);

		void processEvent(const sf::Event& event);

		void update(sf::Time elapsedTime);
		void work();
		void draw();

		bool inFocus();

		void showWindow(const std::string& windowName);
		void closeWindow(size_t id);

	private:
		bool focus;
		static size_t _id;

		std::unordered_map<size_t, ImWindowPtr> windows;
	};
}