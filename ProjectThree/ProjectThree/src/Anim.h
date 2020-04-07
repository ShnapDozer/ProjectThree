#pragma once

#include <iostream>
#include <String> 
#include <vector>

#include <SFML/Graphics.hpp>



class Animation
{

public:


	Animation();


	Animation(std::string file, float speed, int frames); // speed 0.7 normal


	bool Load();


	void ClearAnim();


	void setSpeed(float speed);


	void tik(float time);


	sf::Texture* GetCurTexture();


	int Frames;
	std::string File = " ";
	float  Speed = 0;
	bool   isPlay = false;
	bool   isLoad = false;

private:
	std::map<int, std::string > numList =
	{
		{0, "0.png"},
		{1, "1.png"},
		{2, "2.png"},
		{3, "3.png"},
		{4, "4.png"},
		{5, "5.png"},
		{6, "6.png"},
		{7, "7.png"},
		{8, "8.png"},
		{9, "9.png"},
		{10, "10.png"},
		{11, "11.png"},
		{12, "12.png"},
		{13, "13.png"},
		{14, "14.png"},
		{15, "15.png"},
		{16, "16.png"},
		{17, "17.png"},
		{18, "18.png"},
		{19, "19.png"},
		{20, "20.png"},

	};

	float CurFrame;
	std::vector <sf::Texture> AnimTexture;
};

class AnimManager 
{
public:
	

	AnimManager(std::string name);


	void create(std::string name, std::string file, float speed, int frames, bool loading = false);
	
	
	void loadAnim(std::vector<std::string>NamesAnim);

	
	void loadAllAnim();
	
	
	void tick(float time);
	

	void set(std::string name);
	

	void setAnimSpeed(std::string name, float speed);
	

	void draw(sf::RenderTarget& target, sf::Vector2f posA = { 0,0 }, float angle = 0);


	std::string Name;
	std::map<std::string, Animation> AnimList;

private:
	sf::Sprite S;
	std::string CurAnim;
};