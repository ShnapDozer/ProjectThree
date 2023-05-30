#include "WindowManager.h"

#include "FileDialog.h"
#include "Common.h"
#include "GameApplication.h"

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

	// Static:
	bool AnotherWindow::show_F_LLFF_window = 0;
	bool AnotherWindow::show_S_Video_window = 0;
	bool AnotherWindow::show_A_Create_window = 0;
	bool AnotherWindow::show_L_Create_window = 0;
	bool AnotherWindow::show_Sc_Load_window = 0;


	AnotherWindow::AnotherWindow(const std::string& name, const ImVec2& size, const ImVec2& position) : _windowName(name), _windowSize(size), _windowPosition(position)
	{
		_isShow = false;
	}

	MainWindow::MainWindow(const std::string& name, const ImVec2& size, const ImVec2& position) : AnotherWindow(name, size, position) 
	{
	
	}

	void MainWindow::inWork()
	{
		//ImGui::Begin(_windowName.c_str(), &_isShow, ImGuiWindowFlags_MenuBar);
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
				if (ImGui::MenuItem("Load Level From File")) { show_F_LLFF_window = true; }
				if (ImGui::MenuItem("Load Script")) { show_Sc_Load_window = true; }//Read(ALL_Anim_Manager); }
				if (ImGui::MenuItem("Save")) { FileDialog::openFile("All Files (*.*)\0*.*\0", GameApplication::getRenderWindow()->getSystemHandle()); }//Save(ALL_Anim_Manager); }
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Settings"))
			{
				if (ImGui::MenuItem("Video")) { show_S_Video_window = true; }
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Create"))
			{
				if (ImGui::MenuItem("Animation")) { show_A_Create_window = true; }
				if (ImGui::MenuItem("Level")) { show_L_Create_window = true; }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::End();
	}

	A_Create_window::A_Create_window(const std::string& name, const ImVec2& size, const ImVec2& position) : AnotherWindow(name, size, position)
	{

	}

	void A_Create_window::inWork()
	{
		if (show_A_Create_window)//Вверхее меню вызыв окна
		{
			ImGui::Begin("Create Animation", &show_A_Create_window);
			ImGui::SetWindowSize(_windowSize);
			ImGui::SetWindowPos(_windowPosition);

			if (ImGui::CollapsingHeader("Create Anim Manager")) {

				/*ImGui::InputText("New Anim Manager", nam, 20);
				if (ImGui::Button("Create")) {

					if (checNameAnim(Entity::GetMembers(), nam)) {
						ImGui::Text("Xyu!!!");
					}
					else {
						AnimManager A(nam);
						ALL_Anim_Manager.push_back(A);
					}
				}*/
			}
			//if (Entity::GetMembers().size() != 0) {
				/*std::vector <std::string> a(Common::MapToString(Entity::GetMembers()));
				if (ImGui::ListBox("Chose Anim Manager", &ChoiceOne, a)) {}
				if (ChoiceOne != -1)
				{
					if (ImGui::ListBox("Chose first frame your Anim", &ChoiceTwo, Anim->FileNamesVec))
					{
						strcpy_s(nam, Anim->FileVec[ChoiceTwo].name_Without.c_str());
					}
					if (ChoiceTwo != -1)
					{
						ImGui::Text("File:");

						ImGui::Text(Anim->FileVec[ChoiceTwo].name.c_str());

						ImGui::InputText("Name", nam, 20);
						ImGui::SliderInt("Frames", &Frames, 1, 20);
						ImGui::SliderFloat("Speed", &Speed, 0, 1);
						if (ImGui::Button("Create!"))
						{
							Entity::GetMembers()[a[ChoiceOne]]->create(nam, Anim->FileVec[ChoiceTwo].GetWayToPic(5), Speed, Frames, true);
							ChoiceOne = -1;
							ChoiceTwo = -1;
							Speed = 0;
							Frames = 1;
						}
					}
				}*/
			//}
			ImGui::End();
		}
	}

	void L_Create_window::inWork()
	{
		if (show_L_Create_window)//Вверхее меню вызыв окна
		{
			ImGui::Begin("Create Level", &show_L_Create_window);
			ImGui::SetWindowSize(_windowSize);
			ImGui::SetWindowPos(_windowPosition);

			/*if (ImGui::ListBox("Chose XML file", &ChoiceTwo, Levels->FileNamesVec))
			{
				strcpy_s(nam, Levels->FileVec[ChoiceTwo].name_Without.c_str());
			}
			if (ChoiceTwo != -1)
			{
				ImGui::Text("File:");

				ImGui::Text(Levels->FileVec[ChoiceTwo].name.c_str());

				ImGui::InputText("Name", nam, 20);
				if (ImGui::Button("Create!"))
				{
					LM->Add_Lvl(nam, Levels->FileVec[ChoiceTwo].GetWay());
					ChoiceOne = -1;
					ChoiceTwo = -1;
				}
			}*/

			ImGui::End();
		}
	}

	void Sc_Load_window::inWork()
	{
		if (show_Sc_Load_window)
		{

			ImGui::Begin("Load script", &show_Sc_Load_window);
			ImGui::SetWindowSize(_windowSize);
			ImGui::SetWindowPos(_windowPosition);

			File File_S;

			/*if (ImGui::ListBox("Chose XML file", &ChoiceTwo, Scripts_F->FileNamesVec)) {}
			if (ChoiceTwo != -1)
			{
				File_S = Scripts_F->FileVec[ChoiceTwo];

				ImGui::Text("File:");

				ImGui::Text(Scripts_F->FileVec[ChoiceTwo].name.c_str());

				if (ImGui::Button("Load"))
				{
					Scr_MG->Read_Script_An(File_S);
					Ent_MG->SetScript();
					ChoiceOne = -1;
					ChoiceTwo = -1;
				}
			}*/
			ImGui::End();
		}
	}

	WindowManager::WindowManager(std::shared_ptr <EntityManager> E_MG, std::shared_ptr < Level_Manager> LM, std::shared_ptr <Ex> LvlF,
									std::shared_ptr <Scripts_Manager> Scr_M, std::shared_ptr <Ex> Scr_F) 
	{
		focus = false;

		auto window = GameApplication::getRenderWindow();

		ImGui::SFML::Init(*window);
		ConsMenuSize = { 300, float(window->getSize().y) };
		ConsMenuPos = { float(window->getSize().x) - 300, 0 };

		//All_Window.push_back(std::make_shared<MainWindow>("Main", ConsMenuSize, ConsMenuPos));
		//All_Window.push_back(std::make_shared<A_Create_window>("Anim manager", AnothConsMenuSize, AnothConsMenuPos));
		//All_Window.push_back(std::make_shared<L_Create_window>("Level manager", AnothConsMenuSize, AnothConsMenuPos, LM, LvlF));
		//All_Window.push_back(std::make_shared<S_Video_window>("Video", AnothConsMenuSize, AnothConsMenuPos));
		//All_Window.push_back(std::make_shared<Sc_Load_window>("Load Scripts", AnothConsMenuSize, AnothConsMenuPos, E_MG, Scr_M, Scr_F));
	}

	bool WindowManager::inFocus()
	{
		return focus;
	}

	void WindowManager::update(std::shared_ptr<sf::RenderWindow> window, sf::Clock& clock)
	{
		focus = ImGui::GetIO().WantCaptureMouse;
		ImGui::SFML::Update(*window, clock.restart());
	}

	void WindowManager::ProcessEvent(const sf::Event& event)
	{
		ImGui::SFML::ProcessEvent(event);
		switch (event.type)
		{
		case sf::Event::Resized: 
			auto window = GameApplication::getRenderWindow();

			ConsMenuSize.y = window->getSize().y;
			ConsMenuPos.x = window->getSize().x - 300;
			break;
		}
	}

	void WindowManager::Work()
	{
		ImGui::StyleColorsLight();
		for (auto it : All_Window) {
			it->inWork();
		}
	}

	void WindowManager::Render(sf::RenderWindow& Window) { 
		ImGui::SFML::Render(Window); 
	}

}


