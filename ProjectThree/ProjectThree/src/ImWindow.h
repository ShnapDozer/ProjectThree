#pragma once

#include "ImGui/imgui.h"
#include "ImGui/imgui-sfml.h"

#include <SFML/Graphics.hpp>

#include "Object.h"

namespace pt
{
	class ImWindow
	{
	public:

		ImWindow(const std::string& name, const ImVec2& size, const ImVec2& position);

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

	class MainWindow : public ImWindow
	{
	public:

		MainWindow(const std::string& name, const ImVec2& size, const ImVec2& position);

		void inWork() override;


	private:

	};

	class A_Create_window : public ImWindow
	{
	public:

		A_Create_window(const std::string& name, const ImVec2& size, const ImVec2& position);

		void inWork() override;

	private:

		int Frames = 1;
		float Speed = 0;
		char nam[20] = { };
	};

	class L_Create_window : public ImWindow
	{
	public:

		L_Create_window(const std::string& N, ImVec2& S, ImVec2& P)
			: ImWindow(N, S, P) {}

		void inWork() override;

	private:
		std::string Name;
		char nam[20] = { };
	};

	class S_Video_window : public ImWindow
	{
	public:
		S_Video_window(const std::string& N, ImVec2& S, ImVec2& P) : ImWindow(N, S, P) {}
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

	class  Sc_Load_window : public ImWindow
	{
	public:

		Sc_Load_window(const std::string& N, ImVec2& S, ImVec2& P) : ImWindow(N, S, P) {}

		void inWork() override;


	private:

		float Speed = 0;
	};
}