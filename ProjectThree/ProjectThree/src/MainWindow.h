#pragma once

#include <string>

#include "ImGui/imgui.h"

#include "ImWindow.h"

namespace pt
{

	class MainWindow : public ImWindow
	{
	public:
		MainWindow(size_t id, const std::string& name, const ImVec2& size, const ImVec2& position, ObjectPtr parent = nullptr);
		void inWork() override;
	};
	

}