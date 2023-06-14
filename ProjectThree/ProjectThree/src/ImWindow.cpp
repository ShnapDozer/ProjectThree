#include "ImWindow.h"

#include <string>
#include <vector>

#include "GameApplication.h"
#include "ImWindowManager.h"
#include "FileDialog.h"

namespace ImGui // Поддержка строк для GUI
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

namespace pt 
{

	ImWindow::ImWindow(size_t id, const std::string& name, const ImVec2& size, const ImVec2& position)
		: _id(id), _name(name), _windowSize(size), _windowPosition(position), _show(true)
	{
		
	}

	void ImWindow::show()
	{
		_show = true;
	}

	void ImWindow::minimize()
	{
		_show = false;
	}

	MainWindow::MainWindow(size_t id, const std::string& name, const ImVec2& size, const ImVec2& position) : ImWindow(id, name, size, position)
	{

	}

	void MainWindow::inWork()
	{
		ImGui::Begin(_name.c_str(), &_show, ImGuiWindowFlags_MenuBar);
		//ImGui::SetWindowSize(_windowSize);
		//ImGui::SetWindowPos(_windowPosition);

		//if (ImGui::CollapsingHeader("State"))
		//{
		//	ImGui::Value("Focus", ImGui::GetIO().WantCaptureMouse);

		//	ImGui::Text("Hero:");
		//	//PrintState(Hero_ptr->GetAllState());
		//}

		//if (ImGui::CollapsingHeader("Anim Manager"))//основное меню
		//{
		//	auto animManagerMap = Entity::GetMembers();
		//	StringList animManagerNames(Common::MapToString(animManagerMap));

		//	int animManagerChoice = -1;
		//	if (ImGui::ListBox("Anim Manager", &animManagerChoice, animManagerNames)) {}
		//	if (animManagerChoice != -1)
		//	{
		//		auto choicenAnimList = animManagerMap[animManagerNames[animManagerChoice]]->AnimList;
		//		StringList animNames(Common::MapToString(choicenAnimList));

		//		int  animChoice= -1;
		//		if (ImGui::ListBox("Animation", &animChoice, animNames)) {}
		//		if (animChoice != -1)
		//		{

		//			ImGui::Value("Speed", animManagerMap[animManagerNames[animChoice]]->AnimList[animNames[animChoice]].Speed);

		//			animManagerMap[animManagerNames[animChoice]]->set(animNames[animChoice]);

		//			ImGui::SliderFloat("Speed", &Speed, 0, 1);
		//			if (ImGui::Button("SetSpeed"))
		//			{
		//				Entity::GetMembers()[AM[ChoiceOne]]->setAnimSpeed(animNames[ChoiceTwo], Speed);
		//			}
		//		}
		//	}


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

		if (ImGui::BeginMenuBar())//Вверхее меню
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Load Level From File")) { 
					GameApplication::getImWindowsManager()->showWindow("LoadLevelFromFile");
				}
				if (ImGui::MenuItem("Save")) { 
					
				}//Save(ALL_Anim_Manager); }
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

	//A_Create_window::A_Create_window(const std::string& name, const ImVec2& size, const ImVec2& position) : ImWindow(name, size, position)
	//{

	//}

	//void A_Create_window::inWork()
	//{
	//	if (show_A_Create_window)//Вверхее меню вызыв окна
	//	{
	//		ImGui::Begin("Create Animation", &show_A_Create_window);
	//		ImGui::SetWindowSize(_windowSize);
	//		ImGui::SetWindowPos(_windowPosition);

	//		if (ImGui::CollapsingHeader("Create Anim Manager")) {

	//			/*ImGui::InputText("New Anim Manager", nam, 20);
	//			if (ImGui::Button("Create")) {

	//				if (checNameAnim(Entity::GetMembers(), nam)) {
	//					ImGui::Text("Xyu!!!");
	//				}
	//				else {
	//					AnimManager A(nam);
	//					ALL_Anim_Manager.push_back(A);
	//				}
	//			}*/
	//		}
	//		//if (Entity::GetMembers().size() != 0) {
	//			/*std::vector <std::string> a(Common::MapToString(Entity::GetMembers()));
	//			if (ImGui::ListBox("Chose Anim Manager", &ChoiceOne, a)) {}
	//			if (ChoiceOne != -1)
	//			{
	//				if (ImGui::ListBox("Chose first frame your Anim", &ChoiceTwo, Anim->FileNamesVec))
	//				{
	//					strcpy_s(nam, Anim->FileVec[ChoiceTwo].name_Without.c_str());
	//				}
	//				if (ChoiceTwo != -1)
	//				{
	//					ImGui::Text("File:");

	//					ImGui::Text(Anim->FileVec[ChoiceTwo].name.c_str());

	//					ImGui::InputText("Name", nam, 20);
	//					ImGui::SliderInt("Frames", &Frames, 1, 20);
	//					ImGui::SliderFloat("Speed", &Speed, 0, 1);
	//					if (ImGui::Button("Create!"))
	//					{
	//						Entity::GetMembers()[a[ChoiceOne]]->create(nam, Anim->FileVec[ChoiceTwo].GetWayToPic(5), Speed, Frames, true);
	//						ChoiceOne = -1;
	//						ChoiceTwo = -1;
	//						Speed = 0;
	//						Frames = 1;
	//					}
	//				}
	//			}*/
	//			//}
	//		ImGui::End();
	//	}
	//}

	//void L_Create_window::inWork()
	//{
	//	if (show_L_Create_window)//Вверхее меню вызыв окна
	//	{
	//		ImGui::Begin("Create Level", &show_L_Create_window);
	//		ImGui::SetWindowSize(_windowSize);
	//		ImGui::SetWindowPos(_windowPosition);

	//		/*if (ImGui::ListBox("Chose XML file", &ChoiceTwo, Levels->FileNamesVec))
	//		{
	//			strcpy_s(nam, Levels->FileVec[ChoiceTwo].name_Without.c_str());
	//		}
	//		if (ChoiceTwo != -1)
	//		{
	//			ImGui::Text("File:");

	//			ImGui::Text(Levels->FileVec[ChoiceTwo].name.c_str());

	//			ImGui::InputText("Name", nam, 20);
	//			if (ImGui::Button("Create!"))
	//			{
	//				LM->Add_Lvl(nam, Levels->FileVec[ChoiceTwo].GetWay());
	//				ChoiceOne = -1;
	//				ChoiceTwo = -1;
	//			}
	//		}*/

	//		ImGui::End();
	//	}
	//}

	//void Sc_Load_window::inWork()
	//{
	//	if (show_Sc_Load_window)
	//	{

	//		ImGui::Begin("Load script", &show_Sc_Load_window);
	//		ImGui::SetWindowSize(_windowSize);
	//		ImGui::SetWindowPos(_windowPosition);

	//		/*if (ImGui::ListBox("Chose XML file", &ChoiceTwo, Scripts_F->FileNamesVec)) {}
	//		if (ChoiceTwo != -1)
	//		{
	//			File_S = Scripts_F->FileVec[ChoiceTwo];

	//			ImGui::Text("File:");

	//			ImGui::Text(Scripts_F->FileVec[ChoiceTwo].name.c_str());

	//			if (ImGui::Button("Load"))
	//			{
	//				Scr_MG->Read_Script_An(File_S);
	//				Ent_MG->SetScript();
	//				ChoiceOne = -1;
	//				ChoiceTwo = -1;
	//			}
	//		}*/
	//		ImGui::End();
	//	}
	//}
}