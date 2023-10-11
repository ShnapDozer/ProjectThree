#include "ImWindow.h"

#include <string>
#include <vector>

#include "GameApplication.h"
#include "ImWindowManager.h"
#include "FileDialog.h"

#include "ImGui/imgui.h"

namespace pt 
{

	ImWindow::ImWindow(size_t id, const std::string& name, const ImVec2& size, const ImVec2& position, ObjectPtr parent)
		: _id(id), _name(name), _windowSize(size), _windowPosition(position), _show(true), Object(parent)
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

	

	

	//void L_Create_window::inWork()
	//{
	//	if (show_L_Create_window)//¬верхее меню вызыв окна
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