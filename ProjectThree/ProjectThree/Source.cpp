#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <String>
#include <vector>
#include <Windows.h>
#include <utility>

#include "imgui.h"
#include "imgui-sfml.h"

#include "src/Anim.h"       // +/-Done!
#include "src/Level.h"     // Jopa!
#include "src/TMXLevel.h"
#include "src/Explover.h" // +/-Done!



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

void Hide()
{
	HWND Hide;
	AllocConsole();
	Hide = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Hide, 0);
}

template <typename T>

std::vector <std::string> MapToString(std::map <std::string, T> a)
{
	std::vector <std::string> swag;
	for (auto it = a.begin(); it != a.end(); ++it)
	{
		swag.push_back(it->first);
	}
	return swag;
}

bool checNameAnim(std::vector <AnimManager> a, std::string name)
{
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i].Name == name)return true;
	}
	return false;
}

std::vector <std::string> AnimMToString(std::vector <AnimManager> a) {

	std::vector <std::string> V;
	for (int i = 0; i < a.size(); i++)
	{
		V.push_back(a[i].Name);
	}
	return V;
}

void Save(std::vector <AnimManager>& Anim_Manager, std::string Name = "AutoSave", std::string Way="")
{

	TiXmlDocument doc;
	TiXmlElement* row;
	TiXmlElement* root;
	root = new TiXmlElement("Animation");
	for (int i = 0; i < Anim_Manager.size(); i++)
	{

		for (auto it = Anim_Manager[i].AnimList.begin(); it != Anim_Manager[i].AnimList.end(); ++it)
		{
			row = new TiXmlElement("Anim");
			row->SetAttribute("NameAM", Anim_Manager[i].Name.c_str());
			row->SetAttribute("Name", it->first.c_str());
			row->SetAttribute("File", it->second.File.c_str());
			row->SetDoubleAttribute("Frames", it->second.Frames);
			row->SetDoubleAttribute("Speed", it->second.Speed * 10000);
			root->LinkEndChild(row);
		}
	}
	Name = Name + ".xml";
	doc.LinkEndChild(root);
	doc.SaveFile(Name.c_str());
	std::cout << "Save done!)";
}


void Read(std::vector <AnimManager>& Anim_Manager, std::string WayToFile = "AutoSave.xml")
{
	int framov = 0;
	float speed = 0;
	std::string file, NameAM, Name;
	std::string NameAM_OLD = "AAAAAAAAAA";

	TiXmlDocument doc(WayToFile.c_str());
	if (!doc.LoadFile())
	{
		std::cout << "Read XML XYU :( ./." << std::endl;
	}

	TiXmlElement* element = doc.FirstChildElement("Animation");
	TiXmlElement* objectel;
	objectel = element->FirstChildElement("Anim");

	int i = 0;

	while (objectel)
	{
		if (objectel->Attribute("NameAM") != NULL)
		{
			NameAM = objectel->Attribute("NameAM");
		}
		if (objectel->Attribute("Name") != NULL)
		{
			Name = objectel->Attribute("Name");
		}
		if (objectel->Attribute("File") != NULL)
		{
			file = objectel->Attribute("File");
		}
		if (objectel->Attribute("Frames") != NULL)
		{
			framov = atoi(objectel->Attribute("Frames"));
		}
		if (objectel->Attribute("Speed") != NULL)
		{
			speed = atoi(objectel->Attribute("Speed"));
		}

		if (NameAM != NameAM_OLD || i == 0)
		{
			AnimManager AM(NameAM);
			AM.create(Name, file, speed / 10000, framov);
			Anim_Manager.push_back(AM);
			NameAM_OLD = NameAM;
		}
		else
		{
			Anim_Manager[Anim_Manager.size() - 1].create(Name, file, speed / 10000, framov);
		}
		i++;


		objectel = objectel->NextSiblingElement("Anim");
	}
}


int main()
{
	int Wy = 900;
	int Wx = 1440;

	ImVec2 ConsMenuSize(300, Wy);
    ImVec2 ConsMenuPos(Wx - 300, 0);
    ImVec2 AnothConsMenuSize(600, 400);

	Ex Anim("\\Data\\Animation\\*", "Data/Animation/");
	Ex Levels("\\Data\\Levels\\*", "Data/Levels/");

	//Window&View:
	sf::RenderWindow window(sf::VideoMode(Wx, Wy), "ProjectTwo");
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	sf::View view;
	view.setCenter(0, 0);

	//All:

	std::vector <AnimManager> ALL_Anim_Manager;
	std::vector <AnimManager> USING_Anim_Manager;

	//std::vector <Level> ALL_Level;
	//std::vector <Object> Load_Level;

	std::map <std::string, std::string> ALL_TMX_Level;

	TmxLevel MainLevel;
	MainLevel.LoadFromFile("res/platformer.tmx");


	//Support:

	bool TmxLev                = true;
	bool LoadTmxLev            = false;
	int SelectLev = 0;

	AnimManager A("Test");
	A.create("Walk", "Data/Animation/H", 0.007, 8, true);
	ALL_Anim_Manager.push_back(A);

	//ImGui:
	bool Main;
	bool ImgConsole            = 1;
	bool show_F_LLFF_window    = 0;
	bool show_S_Video_window   = 0;
	bool show_A_Create_window  = 0;

	int Frams = 0;
	int ChozeOne = -1;
	int ChozeTwo = -1;
	float Speed = 0;
	char nam[20] = { };

	sf::Clock deltaClock;
	sf::Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		sf::Event event;
		while (window.pollEvent(event)) 
		{
			ImGui::SFML::ProcessEvent(event);

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close(); 
				break;
			case sf::Event::Resized:
				Wy = window.getSize().y;
				Wx = window.getSize().x;
				ConsMenuSize.y = Wy;
				ConsMenuPos.x = Wx - 300;
				break;
			case sf::Event::MouseWheelScrolled:
				if (event.mouseWheelScroll.delta > 0) { view.zoom(0.75); }
				if (event.mouseWheelScroll.delta < 0) { view.zoom(1.35); }
				break;

			}
		}

		//ImGui:
		if (ImgConsole)
		{
			ImGui::SFML::Update(window, deltaClock.restart());
			ImGui::Begin("Main Window", &Main, ImGuiWindowFlags_MenuBar);

			ImGui::SetWindowSize(ConsMenuSize);
			ImGui::SetWindowPos(ConsMenuPos);
			ImGui::StyleColorsLight();

			if (ImGui::CollapsingHeader("Anim Manager"))//основное меню
			{ 

				std::vector <std::string> AM = AnimMToString(ALL_Anim_Manager);
				if (ImGui::ListBox("Anim Manager", &ChozeOne, AM)) {}
				if (ChozeOne != -1)
				{
					std::vector <std::string> Animlist = MapToString(ALL_Anim_Manager[ChozeOne].AnimList);
					if (ImGui::ListBox("Animation", &ChozeTwo, Animlist)) {}

					if (ChozeTwo != -1)
					{
						ImGui::Value("Speed", ALL_Anim_Manager[ChozeOne].AnimList[Animlist[ChozeTwo]].Speed);
						ALL_Anim_Manager[ChozeOne].set(Animlist[ChozeTwo]);
						ImGui::SliderFloat("Speed", &Speed, 0, 1);
						if (ImGui::Button("SetSpeed"))
						{
							ALL_Anim_Manager[ChozeOne].setAnimSpeed(Animlist[ChozeTwo], Speed);
						}
					}
				}


			}
			if (ImGui::CollapsingHeader("Levels"))//основное меню
			{

				//something will be here
				ImGui::Text("something will be here");
			
			}
			if (ImGui::BeginMenuBar())//Вверхее меню
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Load Level From File")) { show_F_LLFF_window = true; }
					if (ImGui::MenuItem("Save")) { std::cout << "Soon!"; }//Save(ALL_Anim_Manager); }
					if (ImGui::MenuItem("Load")) { std::cout << "Soon!"; }//Read(ALL_Anim_Manager); }
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Settings"))
				{
					if (ImGui::MenuItem("Video")) { show_S_Video_window = true; }
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Animation"))
				{
					if (ImGui::MenuItem("Create")) { show_A_Create_window = true; }
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}
			if (show_F_LLFF_window) //Вверхее меню вызыв окна
			{

				ImGui::Begin("Load Level", &show_F_LLFF_window);
				ImGui::SetWindowSize(AnothConsMenuSize);

				//something will be here
				ImGui::Text("something will be here");

				/*if (ImGui::ListBox("Choze Xml File", &ChozeOne, Levels.FileNamesVec)) {}
				if (ChozeOne != -1)
				{
					if (!TmxLev)
					{
						if (ImGui::ListBox("Chose background PNG", &ChozeTwo, Levels.FileNamesVec)) {}
						if (ChozeTwo != -1)
						{
							ImGui::InputText("Name", nam, 20);
							if (ImGui::Button("Create!")) {
								Level Lev(nam, Levels.FileVec[ChozeOne].GetWay(), Levels.FileVec[ChozeTwo].GetWay());
								//ALL_Level.push_back(Lev);
								//SelectLev = ALL_Level.size() - 1;
								ChozeOne = -1;
								ChozeTwo = -1;
							}
						}
					}
					else
					{
						ImGui::InputText("Name", nam, 20);
						if (ImGui::Button("Create!"))
						{
							ALL_TMX_Level[nam] = Levels.FileVec[ChozeOne].GetWay();
							ChozeOne = -1;
							ChozeTwo = -1;
						}
					}
				}*/
				ImGui::End();
			}
			if (show_S_Video_window)//Вверхее меню вызыв окна
			{
				ImGui::Begin("Video Settings", &show_S_Video_window);
				ImGui::SetWindowSize(AnothConsMenuSize);
				//something will be here
				ImGui::Text("something will be here");
				ImGui::End();
			}
			if (show_A_Create_window)//Вверхее меню вызыв окна
			{
				ImGui::Begin("Create Animation", &show_A_Create_window);
				ImGui::SetWindowSize(AnothConsMenuSize);

				if (ImGui::CollapsingHeader("Create Anim Manager")) {

					ImGui::InputText("New Anim Manager", nam, 20);
					if (ImGui::Button("Create")) {

						if (checNameAnim(ALL_Anim_Manager, nam)) {
							ImGui::Text("Xyu!!!");
						}
						else {
							AnimManager A(nam);
							ALL_Anim_Manager.push_back(A);
						}
					}
				}
				if (ALL_Anim_Manager.size() != 0)
				{
					std::vector <std::string> a = AnimMToString(ALL_Anim_Manager);
					if (ImGui::ListBox("Chose Anim Manager", &ChozeOne, a)) {}
					if (ChozeOne != -1)
					{
						if (ImGui::ListBox("Chose 0 Frame o Anim", &ChozeTwo, Anim.FileNamesVec)) {}
						if (ChozeTwo != -1)
						{
							ImGui::Text("File:");

							ImGui::Text(Anim.FileVec[ChozeTwo].name.c_str());
							ImGui::InputText("Name", nam, 20);
							ImGui::SliderInt("Frames", &Frams, 1, 20);
							ImGui::SliderFloat("Speed", &Speed, 0, 1);
							if (ImGui::Button("Create!"))
							{
								ALL_Anim_Manager[ChozeOne].create(nam, Anim.FileVec[ChozeTwo].GetWayToPic(5), Speed, Frams, true);
								ChozeOne = -1;
								ChozeTwo = -1;
								Speed = 0;
								Frams = 1;
							}
						}
					}
				}


				ImGui::End();
			}
			ImGui::End();
		}

//UpDate:

		for (int i = 0; i < ALL_Anim_Manager.size(); i++)
		{
			ALL_Anim_Manager[i].tick(time);
		}

		window.clear();

		window.setView(view);

		sf::RenderTarget &target = window;

		MainLevel.Draw(target);

		for (int i = 0; i < ALL_Anim_Manager.size(); i++)
		{
			ALL_Anim_Manager[i].draw(target);
		}

		ImGui::SFML::Render(window);
	
		window.display();
	}

	return 0;
}