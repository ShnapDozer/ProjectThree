#pragma once

#include "imgui.h"
#include "imgui-sfml.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <String>
#include <vector>
#include <memory>

#include "Explover.h" 
#include "Scripts_Mg.h"
#include "Entity_Mg.h"
#include "Entity.h" 


class AnotherWindow
{
public:

	AnotherWindow(const std::string& name, ImVec2& Size, ImVec2& Pos) : name_Windows(name), WinSize(Size), WinPos(Pos) {}

	virtual void inWork() = 0;

protected:
	const std::string name_Windows;
	bool is_Show = false;
	ImVec2 WinSize;
	ImVec2 WinPos;

	//Logic window variable:
	static bool show_F_LLFF_window;
	static bool show_S_Video_window;
	static bool show_A_Create_window;
	static bool show_L_Create_window;
	static bool show_Sc_Load_window;

	int ChoiceOne = -1;
	int ChoiceTwo = -1;
};

class MainWindow : public AnotherWindow
{
public:

	MainWindow(const std::string& N, ImVec2& S, ImVec2& P, const std::shared_ptr <Hero> H, std::shared_ptr <Level_Manager> L) 
		: AnotherWindow(N, S, P), Hero_ptr(H), LM_ptr(L) {}

	void inWork() override;
	

private:

	float Speed = 0;
	const std::shared_ptr <Hero> Hero_ptr;
	std::shared_ptr <Level_Manager> LM_ptr;
};

class A_Create_window : public AnotherWindow
{
public:

	A_Create_window(const std::string& N, ImVec2& S, ImVec2& P, std::shared_ptr <Ex> A) : AnotherWindow(N, S, P), Anim(A) {}

	void inWork() override;
	
private:

	std::shared_ptr <Ex> Anim;
	int Frames = 1;
	float Speed = 0;
	char nam[20] = { };
};

class L_Create_window : public AnotherWindow
{
public:

	L_Create_window(const std::string& N, ImVec2& S, ImVec2& P, std::shared_ptr <Level_Manager> L_M, std::shared_ptr <Ex> L) 
		: AnotherWindow(N, S, P), LM(L_M), Levels(L) {}

	void inWork() override;

private:

	std::shared_ptr <Ex> Levels;
	std::shared_ptr <Level_Manager> LM;
	std::string Name;
	char nam[20] = { };
};

class S_Video_window : public AnotherWindow
{
public:
	S_Video_window(const std::string& N, ImVec2& S, ImVec2& P) : AnotherWindow(N, S, P) {}
	void inWork() override
	{
		if (show_S_Video_window)//¬верхее меню вызыв окна
		{
			ImGui::Begin("Video Settings", &show_S_Video_window);
			ImGui::SetWindowSize(WinSize);
			ImGui::SetWindowPos(WinPos);
			//something will be here
			ImGui::Text("something will be here");
			ImGui::End();
		}
	}
};

class  Sc_Load_window : public AnotherWindow
{
public:

	Sc_Load_window(const std::string& N, ImVec2& S, ImVec2& P, std::shared_ptr <Entity_Manager> E_MG,
		std::shared_ptr <Scripts_Manager> S_MG, std::shared_ptr <Ex> Scr_F)
		: AnotherWindow(N, S, P), Ent_MG(E_MG), Scr_MG(S_MG), Scripts_F(Scr_F){}

	void inWork() override;
	

private:

	float Speed = 0;
	const std::shared_ptr <Scripts_Manager> Scr_MG;
	const std::shared_ptr <Entity_Manager> Ent_MG;
	const std::shared_ptr <Ex> Scripts_F;
};

class IMG_Manager
{
public:

	bool focus = false;
	
	IMG_Manager
	(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr <Entity_Manager> E_MG,
	std::shared_ptr <Level_Manager> LM, std::shared_ptr <Ex> AnimF, std::shared_ptr <Ex> LvlF,
		std::shared_ptr <Scripts_Manager> Scr_M, std::shared_ptr <Ex> Scr_F);

	void update(std::shared_ptr<sf::RenderWindow> window, sf::Clock& clock);

	void ProcessEvent(const sf::Event& event);
	

	void Work();
	

	void Render(sf::RenderWindow& Window);

private:

	std::shared_ptr<sf::RenderWindow> main_Window;
	ImVec2 AnothConsMenuSize = { 600, 400 };
	ImVec2 AnothConsMenuPos  = { 100, 100 };
	std::vector<std::shared_ptr<AnotherWindow>> All_Window;
	ImVec2 ConsMenuSize;
	ImVec2 ConsMenuPos;

};
