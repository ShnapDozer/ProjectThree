#include "AddAnimationWindow.h"

#include "AnimationManager.h"
#include "Common.h"
#include "GameApplication.h"
#include "FileDialog.h"

namespace ImGui // Ïîääåðæêà ñòðîê äëÿ GUI
{
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return Combo(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}

	bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return ListBox(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}

}

pt::AddAnimationWindow::AddAnimationWindow(size_t id, const std::string& name, const ImVec2& size, const ImVec2& position, ObjectPtr parent)
	: ImWindow(id, name, size, position, parent), _ñhooseManager(-1), _animationName(""), _managerName(""), _framePath("")
{

}

void pt::AddAnimationWindow::inWork()
{
	if (_show)
	{
		ImGui::Begin(_name.c_str(), &_show, ImGuiWindowFlags_MenuBar);
		ImGui::SetWindowSize(_windowSize, ImGuiCond_FirstUseEver);
		ImGui::SetWindowPos(_windowPosition, ImGuiCond_FirstUseEver);

		auto animationManagersMap = GameApplication::getAnimationManagersMap();

		if (ImGui::CollapsingHeader("Create Animation Manager")) {
			ImGui::InputText("Name of animation manager", _managerName, 20);
			if (ImGui::Button("Create")) {
				if (animationManagersMap->find(_managerName) == animationManagersMap->end()) {	
					(*animationManagersMap)[_managerName] = std::make_shared<AnimationManager>();
				} else {
					ImGui::Text("Error: animation manager with this name is already exist!");
				}
			}
		}

		if (!animationManagersMap->empty()) {
			StringList managerNames;
			for (auto managerName : *animationManagersMap) {
				managerNames.push_back(managerName.first);
			}

			
			if (ImGui::ListBox("Choose animation manager", &_ñhooseManager, managerNames)) {}
			
			if (_ñhooseManager != -1)
			{
				ImGui::InputText("Path to frame", _framePath, 200);
				if (ImGui::Button("Browse...")) {
					strcpy_s(_framePath, FileDialog::openFile("*", GameApplication::getRenderWindow()->getSystemHandle()).c_str());
				}
				if (ImGui::Button("Add")) {
					_framePaths.push_back(_framePath);
				}

				int tmp = -1;
				if (ImGui::ListBox("Files", &tmp, _framePaths)) {}

				if (!_framePaths.empty()) {
					ImGui::InputText("Animation name", _animationName, 20);
					if (ImGui::Button("Create"))
					{
						(*animationManagersMap)[_managerName]->addAnimation(_animationName, _framePaths);
						_framePaths.clear();
					}
				}
			}			
		}
		ImGui::End();
	}
}
