#pragma once

#include "src/Game.h"

// Static:
bool AnotherWindow::show_F_LLFF_window       = 0;
bool AnotherWindow::show_S_Video_window      = 0;
bool AnotherWindow::show_A_Create_window     = 0;
bool AnotherWindow::show_L_Create_window     = 0;
bool AnotherWindow::show_Sc_Load_window   = 0;

std::map <std::string, AnimManager*> Entity::Members;

int main()
{
	int Wx = 1440;
	int Wy = 900;
	Game game(Wx, Wy);
	game.processing();
	ImGui::SFML::Shutdown();
	return 0;
}
