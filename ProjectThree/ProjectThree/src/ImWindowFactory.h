#pragma once
#include <string>

#include "Defines.h"
#include "Object.h"



namespace pt {

	class ImWindow;

	class ImWindowFactory : public Object {
	public:

		static ImWindowPtr createWindow(const std::string& type, const std::string &name, int possitionX, int possitionY, int width, int height);


	};
}
