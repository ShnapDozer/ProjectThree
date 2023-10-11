#pragma once

#include <string>

#include "ImGui/imgui.h"

#include "Defines.h"
#include "ImWindow.h"

namespace pt
{

	class AddAnimationWindow : public ImWindow
	{
	public:
		AddAnimationWindow(size_t id, const std::string& name, const ImVec2& size, const ImVec2& position, ObjectPtr parent = nullptr);
		void inWork() override;

	private:
		int _ñhooseManager = -1;

		char _animationName[20];
		char _managerName[20];
		char _framePath[200];

		StringList _framePaths;
	};


}