#pragma once

#include <iostream>
#include <String> 
#include <vector>
#include <ctime>


#include <SFML/Graphics.hpp>


struct Tunel 
{
	sf::Vector2i XY;
	char direction = 'N';
	int Distans;
};

void Displacement(struct Tunel &Tun, bool map0[], char wall = 'N')
{
	int Chans = rand() % 100;
	switch (Tun.direction) 
	{
	case 'N':
		if      (Chans < 25)  { Tun.XY.x++; Tun.direction = 'R'; Tun.Distans = 1;}
		else if (Chans < 50) { Tun.XY.x--; Tun.direction = 'L';  Tun.Distans = 1; }
		else if (Chans < 75) { Tun.XY.y++; Tun.direction = 'D'; Tun.Distans = 1; }
		else if (Chans < 100) { Tun.XY.y--; Tun.direction = 'U'; Tun.Distans = 1; }
		break;

	case 'U':
		
		if (Chans < 15 && !(map0[2] + map0[8]) && Tun.Distans < 0) //Right
		{ 
			Tun.XY.x++; Tun.direction = 'R';
			Tun.Distans = 1;
		}
		else if (Chans < 30 && !(map0[0] + map0[6]) && Tun.Distans < 0) //Left
		{
			Tun.XY.x--; Tun.direction = 'L'; 
			Tun.Distans = 1;
		}
		else if (Chans < 100) // Up
		{
			Tun.XY.y--;
			Tun.direction = 'U';
			Tun.Distans--;
		}
		break;

	case 'D':
		if (Chans < 15 && !(map0[2] + map0[8]) && Tun.Distans < 1) //Right
		{ 
			Tun.XY.x++; Tun.direction = 'R'; 
		    Tun.Distans = 0; 
		}
		else if (Chans < 30 && !(map0[0] + map0[6]) && Tun.Distans < 1) //Left
		{ 
			Tun.XY.x--; Tun.direction = 'L'; 
			Tun.Distans = 0; 
		}
		else if (Chans < 100) //Down
		{ 
			Tun.XY.y++; Tun.direction = 'D'; 
			Tun.Distans--; }
		break;

	case 'L':
		if (Chans < 70) //Left
		{ 
			Tun.XY.x--; Tun.direction = 'L'; 
			Tun.Distans--; 
		}	
		else if (Chans < 85 && !(map0[8] + map0[6]) && Tun.Distans < 1) //Down
		{ 
			Tun.XY.y++; Tun.direction = 'D'; 
			Tun.Distans = 0; 
		}
		else if (Chans < 100 && !(map0[0] + map0[2]) && Tun.Distans < 1) //Up
		{ 
			Tun.XY.y--; Tun.direction = 'U'; 
			Tun.Distans = 0; 
		}
		break;

	case 'R':
		if (Chans < 70)//Right
		{
			Tun.XY.x++; Tun.direction = 'R';
			Tun.Distans--;
		}
		else if (Chans < 85 && !(map0[8] + map0[6]) && Tun.Distans < 1) //Down
		{ 
			Tun.XY.y++; Tun.direction = 'D'; 
			Tun.Distans = 0; 
		}
		else if (Chans < 100 && !(map0[0] + map0[2]) && Tun.Distans < 1) //Up
		{ 
			Tun.XY.y--; Tun.direction = 'U'; 
			Tun.Distans = 0; 
		}
		break;

	}
}


class randMap
{
private:

	const int Ro0 = 5; // Reference point
	const int RoDip0 = 3; // Number of rooms

	const int Co0 = 20;
	const int CoDip0 = 20;

	int Distance;
	int min;

	int Difficult;

	sf::Sprite S;

	sf::Texture Tcor;
	sf::Texture Trom;
	sf::Texture Tnot;

public:

	int Rooms;
	int Ñorridors;

	// N-not, Ñ-corridor, R-room.

	char map0[100][100] = { 'N' }; // D 0; R 5-8; Ñ 15-25;
	randMap(int difficult = 0)
	{
		Difficult = difficult;
		Tcor.loadFromFile("1.Data/Map/Corridor.png");
		Trom.loadFromFile("1.Data/Map/Room.png");
		Tnot.loadFromFile("1.Data/Map/Not.png");
	}

	void reLoad()
	{
		Tunel Tun;
		for (int i = 0; i < 41; i++)
		{
			for (int j = 0; j < 41; j++)
			{
				map0[i][j] = 'N';
			}
		}
		Tun.XY.x = 21;
		Tun.XY.y = 21;
		Rooms = rand() % RoDip0 + Ro0;
		Ñorridors = rand() % CoDip0 + Co0;
		min = Ñorridors / Rooms;

		std::cout << Tun.XY.x << ":X  Y:" << Tun.XY.y << std::endl;
		std::cout << Rooms << ":R  C:" << Ñorridors << std::endl;
		std::cout << min << ":Min" << std::endl;

		map0[Tun.XY.y][Tun.XY.x] = 'R';

		int count = 0;

		while (Rooms != 0)
		{
			bool mapNine[9] = { 0 };
			count = 0;
			for (int i = 0; i < 3; i++) 
			{
				for (int j = 0; j < 3; j++)
				{
					if (map0[Tun.XY.y + i][Tun.XY.x + j] == 'R' || map0[Tun.XY.y + i][Tun.XY.x + j] == 'C') 
					{
						mapNine[count] = 1;
					}
					count++;
				}
			}
			Displacement(Tun, mapNine);
			if (rand() % 100 < 25 && Distance < 0)
			{
				map0[Tun.XY.y][Tun.XY.x] = 'R'; 
				Distance = 3;
				Rooms--;
			}
		
			else 
			{
				map0[Tun.XY.y][Tun.XY.x] = 'C';
				Distance--;
			}
		}
	}
	void Draw(sf::RenderTarget& target)
	{
		const sf::FloatRect viewportRect = target.getView().getViewport();

		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				if (map0[i][j] == 'C')      S.setTexture(Tcor);
				else if (map0[i][j] == 'R') S.setTexture(Trom);
				else                        S.setTexture(Tnot);

				S.setPosition(j * 10, i * 10);

				if (viewportRect.intersects(S.getLocalBounds()))
				{
					target.draw(S);
				}
			}
		}
	}
};



