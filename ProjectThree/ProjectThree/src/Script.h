#pragma once

#include <iostream>
#include <String> 
#include <vector>
#include <ctime>


#include <SFML/Graphics.hpp>
#include "TMXLevel.h"

#include "Anim.h"

class Script_Anim 
{
public:

	Script_Anim(std::string name) 
		: Name(name) {}

	void add_Anim(std::string name, Animation anim) 
	{
		AnimList[name] = anim;
	}

	std::map<std::string, Animation>* get_Data() 
	{
		return &AnimList;
	}

	const std::string Name;
private:
	std::map<std::string, Animation> AnimList;
};

class Script_Dial
{
public:

	Script_Dial(std::string name)
		: Name(name) {}

	void add_Anim(std::string name, Animation anim)
	{

	}

	void get_Data()
	{

	}

	const std::string Name;
private:
	
};

class Script_Stats
{
public:

	Script_Stats(std::string name)
		: Name(name) {}

	void add_Anim(std::string name, Animation anim)
	{
		
	}

	void get_Data()
	{
		
	}

	const std::string Name;
private:
	
};
