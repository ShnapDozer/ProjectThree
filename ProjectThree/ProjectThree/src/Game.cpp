#include "Game.h"

void Hide()
{
	HWND Hide;
	AllocConsole();
	Hide = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Hide, 0);
}

bool checNameAnim(std::vector <std::string> a, std::string name)
{
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] == name)return true;
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

Game::Game(int x, int y): Wx(x), Wy(y)
{
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Wx, Wy), "ProjectThree");
	window->setVerticalSyncEnabled(true);
	window->setKeyRepeatEnabled(false);

	view = std::make_shared<sf::View>();
	view->setCenter(0, 0);

	Levels_M = std::make_shared<Level_Manager>();
	Levels_M->Add_Lvl("01", "Data/Levels/Isometric/01.tmx");

	icon.loadFromFile("Data/icon.png");
	window->setIcon(32, 32, icon.getPixelsPtr());

	Anim_EX       = std::make_shared<Ex>("\\Data\\Animation\\*", "Data/Animation/");
	Iso_Levels_EX = std::make_shared<Ex>("\\Data\\Levels\\Isometric\\*", "Data/Levels/Isometric/");
	Hex_Levels_EX = std::make_shared<Ex>("\\Data\\Levels\\Hex\\*", "Data/Levels/Hex/");
	Ort_Levels_EX = std::make_shared<Ex>("\\Data\\Levels\\Ortogonal\\*", "Data/Levels/Ortogonal/");
	Scripts_EX    = std::make_shared<Ex>("\\Data\\Scripts\\*", "Data/Scripts/");

	Scripts_M = std::make_shared <Scripts_Manager>(*Scripts_EX);

	Scripts_M->Read_Script_An(Scripts_EX->FileVec[2]);

	Entity_M = std::make_shared <Entity_Manager>(Levels_M, Scripts_M);

	//hero = std::make_shared<Hero>("Hero"/*, Levels_M->Lvl_FirstObject("Hero_Play").poss*/);
	//hero->AddAnim("Walk", "Data/Animation/H", 0.007, 8);

	GUI = std::make_shared<IMG_Manager>(window, Entity_M, Levels_M, Anim_EX, Iso_Levels_EX, Scripts_M, Scripts_EX);

	srand(time(NULL));
}
void Game::processing()
{
	while (window->isOpen())
	{
		update();
		draw();
	}
}
void Game::update()
{
	float time = clock.getElapsedTime().asMicroseconds();
	clock.restart();
	time = time / 800;

	//Mouse
	Pos_M = sf::Mouse::getPosition(*window);
	MapPos = window->mapPixelToCoords(Pos_M);

	sf::Event event;
	while (window->pollEvent(event))
	{
		GUI->ProcessEvent(event);
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::Resized:
			Wy = window->getSize().y;
			Wx = window->getSize().x;
			break;
		case sf::Event::MouseWheelScrolled:
			if (!GUI->focus)
			{
				if (event.mouseWheelScroll.delta > 0) { view->zoom(0.75); }
				if (event.mouseWheelScroll.delta < 0) { view->zoom(1.35); }
			}
			break;
		case sf::Event::LostFocus:
			WindowFocus = 0;
			break;
		case sf::Event::GainedFocus:
			WindowFocus = 1;
			break;

		}
	}

	if (WindowFocus)
	{
		Entity_M->Update(time, MapPos, GUI->focus);
		GUI->update(window, deltaClock);
		GUI->Work();
	}
}

void Game::draw()
{
	sf::RenderTarget& target = *window;

	view->setCenter(Entity_M->GetHeroPos());

	window->clear();

	window->setView(*view);

	Levels_M->Draw_Lvl(target, MapPos);

	for (auto it : Levels_M->Lvl_Solid_Vec())
	{
		it.draw(target, sf::Color::Blue);
	}

	Entity_M->Draw(target);
	GUI->Render(*window);

	window->display();
}
