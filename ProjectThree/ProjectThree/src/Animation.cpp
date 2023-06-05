#pragma once

#include "Animation.h"

namespace pt
{
	Animation::Animation(ObjectPtr parent) : Object(parent)
	{
		isPlay = 0;
		isLoad = 0;
		CurFrame = 0;
		Frames = 0;
	}

	Animation::Animation(std::string file, float speed, int frames, ObjectPtr parent) : Object(parent)
	{
		Speed = speed;
		Frames = frames;
		File = file;
		CurFrame = 0;
	}

	bool Animation::Load()
	{
		if (File == " ")
		{
			std::cout << "File is empty! /t .|.";
			return false;
		}
		sf::Texture T;
		for (int i = 0; i < Frames; i++)
		{
			T.loadFromFile(File + numList[i]);
			AnimTexture.push_back(std::move(T));
		}
		isPlay = true;
		isLoad = true;
		if (AnimTexture.size() == Frames)return true;
		else return false;

	}


	void Animation::ClearAnim()
	{
		AnimTexture.clear();
		isPlay = false;
		isLoad = false;
	}

	void Animation::setSpeed(float speed) { Speed = speed / 100; }

	void Animation::tik(float time)
	{
		if (!isPlay || !isLoad)return;
		CurFrame += Speed * time;
		if (CurFrame > Frames) CurFrame = 0;
	}

	sf::Texture* Animation::GetCurTexture()
	{
		return &AnimTexture[CurFrame];
	}

}
	

