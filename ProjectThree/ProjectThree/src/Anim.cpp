#pragma once

#include "Anim.h"

namespace ProjectThree
{

	//------------Animation Class:
	Animation::Animation()
	{
		isPlay = 0;
		isLoad = 0;
		CurFrame = 0;
		Frames = 0;
	}

	Animation::Animation(std::string file, float speed, int frames)
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



	//------------AnimManager Class:

	AnimManager::AnimManager(std::string name) { Name = name; }

	void AnimManager::create(std::string name, std::string file, float speed, int frames, bool loading)
	{
		Animation Anim(file, speed, frames);
		AnimList[name] = std::move(Anim);
		CurAnim = name;
		if (loading) { AnimList[name].Load(); }
	}

	void AnimManager::loadAnim(const std::vector<std::string>& NameAnim)
	{

	}

	void AnimManager::loadAllAnim()
	{
		for (auto it = AnimList.begin(); it != AnimList.end(); it++)
		{
			it->second.Load();
		}
	}

	void AnimManager::tick(float time)
	{
		if (AnimList.size() == 0) return;
		AnimList[CurAnim].tik(time);
	}

	void AnimManager::set(std::string name)
	{
		CurAnim = name;
	}

	void AnimManager::setAnimList(const std::map<std::string, Animation>& Anims)
	{
		if (!Anims.empty()) AnimList = Anims;
		else std::cout << "Anim manager: " << Name << " can't set! Empty  anim list! :(" << std::endl;
	}

	void AnimManager::setAnimSpeed(std::string name, float speed)
	{
		AnimList[name].setSpeed(speed);
	}

	void AnimManager::draw(sf::RenderTarget& target, const sf::Vector2f& posA, float angle)
	{
		if (AnimList.size() == 0 || !AnimList[CurAnim].isLoad) return;
		const sf::FloatRect viewportRect = target.getView().getViewport();

		S.setTexture(*AnimList[CurAnim].GetCurTexture());
		S.setPosition(posA);

		if (viewportRect.intersects(S.getLocalBounds()))
		{
			S.setOrigin(S.getGlobalBounds().height / 2, S.getGlobalBounds().width / 2);
			S.setRotation(angle);
			target.draw(S);
		}
	}

	sf::FloatRect AnimManager::GetRect() const { return S.getGlobalBounds(); }

}
	

