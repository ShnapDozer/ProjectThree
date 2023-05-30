#pragma once

#include "ImGui/imgui.h"
#include "ImGui/imgui-sfml.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <String>
#include <vector>
#include <memory>

#include "Explover.h" 
#include "Scripts_Mg.h"
#include "Entity_Mg.h"
#include "Entity.h" 

namespace pt
{

	class AnotherWindow
	{
	public:

		AnotherWindow(const std::string& name, const ImVec2& size, const ImVec2& position);

		virtual void inWork() = 0;

	protected:
		const std::string _windowName;
		bool _isShow;
		ImVec2 _windowSize;
		ImVec2 _windowPosition;

		//Logic window variable:
		static bool show_F_LLFF_window;
		static bool show_S_Video_window;
		static bool show_A_Create_window;
		static bool show_L_Create_window;
		static bool show_Sc_Load_window;
	};

	class MainWindow : public AnotherWindow
	{
	public:

		MainWindow(const std::string& name, const ImVec2& size, const ImVec2& position);

		void inWork() override;


	private:

	};

	class A_Create_window : public AnotherWindow
	{
	public:

		A_Create_window(const std::string& name, const ImVec2& size, const ImVec2& position);

		void inWork() override;

	private:

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
				ImGui::SetWindowSize(_windowSize);
				ImGui::SetWindowPos(_windowPosition);
				//something will be here
				ImGui::Text("something will be here");
				ImGui::End();
			}
		}
	};

	class  Sc_Load_window : public AnotherWindow
	{
	public:

		Sc_Load_window(const std::string& N, ImVec2& S, ImVec2& P, std::shared_ptr <EntityManager> E_MG,
			std::shared_ptr <Scripts_Manager> S_MG, std::shared_ptr <Ex> Scr_F)
			: AnotherWindow(N, S, P), Ent_MG(E_MG), Scr_MG(S_MG), Scripts_F(Scr_F) {}

		void inWork() override;


	private:

		float Speed = 0;
		const std::shared_ptr <Scripts_Manager> Scr_MG;
		const std::shared_ptr <EntityManager> Ent_MG;
		const std::shared_ptr <Ex> Scripts_F;
	};

	class WindowManager
	{
	public:
		WindowManager(std::shared_ptr <EntityManager> E_MG,std::shared_ptr <Level_Manager> LM, std::shared_ptr <Ex> LvlF,
						std::shared_ptr <Scripts_Manager> Scr_M, std::shared_ptr <Ex> Scr_F);

		void update(std::shared_ptr<sf::RenderWindow> window, sf::Clock& clock);

		void ProcessEvent(const sf::Event& event);

		void Work();
		void Render(sf::RenderWindow& Window);

		bool inFocus();

	private:

		bool focus;

		std::shared_ptr<sf::RenderWindow> main_Window;
		ImVec2 AnothConsMenuSize = { 600, 400 };
		ImVec2 AnothConsMenuPos = { 100, 100 };
		std::vector<std::shared_ptr<AnotherWindow>> All_Window;
		ImVec2 ConsMenuSize;
		ImVec2 ConsMenuPos;

	};
}