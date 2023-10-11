#include "MainWindow.h"

#include "Common.h"
#include "EntityManager.h"
#include "GameApplication.h"
#include "ImWindowManager.h"
#include "FileDialog.h"

pt::MainWindow::MainWindow(size_t id, const std::string& name, const ImVec2& size, const ImVec2& position, ObjectPtr parent)
	: ImWindow(id, name, size, position, parent)
{

}

void pt::MainWindow::inWork()
{
	if (_show) {
		ImGui::Begin(_name.c_str(), &_show, ImGuiWindowFlags_MenuBar);
		ImGui::SetWindowSize(_windowSize, ImGuiCond_FirstUseEver);
		ImGui::SetWindowPos(_windowPosition, ImGuiCond_FirstUseEver);

		if (ImGui::CollapsingHeader("State"))
		{
			//ImGui::Value("Focus", ImGui::GetIO().WantCaptureMouse);

			//ImGui::Text("Hero:");
			//PrintState(Hero_ptr->GetAllState());
		}

		if (ImGui::CollapsingHeader("Anim Manager"))
		{
			GameApplication::getEntityManager()->getEntitysMap();
			Common::map2StringList()
			auto animManagerMap = Entity::GetMembers();
			StringList animManagerNames(Common::map2StringList(animManagerMap));

			int animManagerChoice = -1;
			if (ImGui::ListBox("Anim Manager", &animManagerChoice, animManagerNames)) {}
			if (animManagerChoice != -1)
			{
				auto choicenAnimList = animManagerMap[animManagerNames[animManagerChoice]]->AnimList;
				StringList animNames(Common::map2StringList(choicenAnimList));

				int  animChoice= -1;
				if (ImGui::ListBox("Animation", &animChoice, animNames)) {}
				if (animChoice != -1)
				{

					ImGui::Value("Speed", animManagerMap[animManagerNames[animChoice]]->AnimList[animNames[animChoice]].Speed);

					animManagerMap[animManagerNames[animChoice]]->set(animNames[animChoice]);

					ImGui::SliderFloat("Speed", &Speed, 0, 1);
					if (ImGui::Button("SetSpeed"))
					{
						Entity::GetMembers()[AM[ChoiceOne]]->setAnimSpeed(animNames[ChoiceTwo], Speed);
					}
				}
			}


		//}
		if (ImGui::CollapsingHeader("Level Manager"))//основное меню
		{
			/*std::vector <std::string> LM(Common::MapToString(LM_ptr->Lvl_Get_Map()));
			if (ImGui::ListBox("Level manager", &ChoiceOne, LM)) {}
			if (ChoiceOne != -1)
			{
				if (ImGui::Button("Load")) { LM_ptr->Load_Lvl(LM[ChoiceOne]); }
			}*/
		}
		if (ImGui::CollapsingHeader("Debug settings"))//основное меню
		{

		}

		if (ImGui::BeginMenuBar())//¬верхее меню
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Load Level From File")) {
					GameApplication::getImWindowsManager()->showWindow("LoadLevelFromFile");
				}
				if (ImGui::MenuItem("Save")) {

				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Settings"))
			{
				if (ImGui::MenuItem("Video")) {
					GameApplication::getImWindowsManager()->showWindow("VideoSettings");
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Add"))
			{
				if (ImGui::MenuItem("Animation")) {
					GameApplication::getImWindowsManager()->showWindow("AddAnimation");
				}
				if (ImGui::MenuItem("Level")) {
					GameApplication::getImWindowsManager()->showWindow("AddLevel");
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::End();
	}
}