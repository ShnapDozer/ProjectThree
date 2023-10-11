#pragma once

#include <string>

#include "Object.h"

namespace pt
{

	class LoadingManager : public Object
	{
	public:

		static void loadAnimation(const std::string& configFile);

	private:

	};
}

