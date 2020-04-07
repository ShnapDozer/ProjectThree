#pragma once


#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "TinyXML/tinyxml.h"
#include <SFML/Graphics.hpp>


class Object
{
public:
	std::string name;
	sf::FloatRect rect;
	Object(std::string n, sf::FloatRect r)
	{
		name = n;
		rect = r;
	}

};


class Level {
private:

	std::string FileRect;
	std::string FileBackG;

	sf::Texture t;
	sf::Sprite Lev;

public:
	std::string Name;
	std::vector <Object> Obje;
	sf::FloatRect size;

	Level(std::string Name = "TestLVL", std::string FileRect = "Test.xml", std::string FileBackG= "TestIMG.png")
	{
		this->Name = Name;
		this->FileRect = FileRect;
		this->FileBackG = FileBackG;
	}

	void Load(std::vector <Object> &obj)
	{
		sf::FloatRect SizLev;
		std::string nameobj;

		t.loadFromFile(FileBackG);
		Lev.setTexture(t);
		Lev.setPosition(0, 0);
		SizLev=Lev.getGlobalBounds();

		TiXmlDocument doc(FileRect.c_str());
		if (!doc.LoadFile())
		{
			std::cout << "XML XYU :(" << std::endl;
			return;
		}
		TiXmlElement *element = doc.FirstChildElement("Name");
		TiXmlElement *objectel;
		objectel = element->FirstChildElement("Rect");
		while (objectel)
		{
			if (objectel->Attribute("name") != NULL)
			{
				nameobj = objectel->Attribute("name");
			}
			if (objectel->Attribute("X") != NULL)
			{
				size.left = atoi(objectel->Attribute("X"));
			}
			if (objectel->Attribute("Y") != NULL)
			{
				size.top = atoi(objectel->Attribute("Y"));
			}
			if (objectel->Attribute("W") != NULL)
			{
				size.width = atoi(objectel->Attribute("W"));
			}
			if (objectel->Attribute("H") != NULL)
			{
				size.height = atoi(objectel->Attribute("H"));
			}

			size.left   = size.left  + size.width ;
			size.top    = size.top  + size.height ;
			size.width  = size.width;
			size.height = size.height;

			Object o(nameobj, size);
			Obje.push_back(o);
			objectel = objectel->NextSiblingElement("Rect");

		}

		this->Obje = obj;

	}

	void Draw(sf::RenderWindow &window)
	{
		window.draw(Lev);
	}

	Object getObj(std::string name)
	{
		for (int i = 0; i < Obje.size(); i++)
		{
			if (Obje[i].name == name) return Obje[i];
		}
		Object EmtyObj(name, sf::FloatRect(100, 100, 0, 0));
		std::cout << "Object " << name << " is not found! :(" << std::endl;
		return EmtyObj;
	}

	std::vector <Object> GetAllObjects() { return Obje; }
};





