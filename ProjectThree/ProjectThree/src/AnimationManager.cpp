#include "AnimationManager.h"

namespace pt {
	AnimationManager::AnimationManager(const std::string& name, ObjectPtr parent) : Object(parent)
	{ 
		_name = name; 
	}

	void AnimationManager::create(const std::string& name, const std::string& file, float speed, int frames, bool loading)
	{
		Animation Anim(file, speed, frames);
		_animList[name] = std::move(Anim);
		_currentAnimation = name;
		if (loading) { _animList[name].Load(); }
	}

	void AnimationManager::loadAnim(const std::vector<std::string>& NameAnim)
	{

	}

	void AnimationManager::loadAllAnim()
	{
		for (auto it = _animList.begin(); it != _animList.end(); it++)
		{
			it->second.Load();
		}
	}

	void AnimationManager::tick(float time)
	{
		if (_animList.size() == 0) return;
		_animList[_currentAnimation].tik(time);
	}

	void AnimationManager::set(const std::string& name)
	{
		_currentAnimation = name;
	}

	void AnimationManager::setAnimList(const std::map<std::string, Animation>& Anims)
	{
		if (!Anims.empty()) _animList = Anims;
		else std::cout << "Anim manager: " << _name << " can't set! Empty  anim list! :(" << std::endl;
	}

	void AnimationManager::setAnimSpeed(const std::string& name, float speed)
	{
		_animList[name].setSpeed(speed);
	}

	void AnimationManager::draw(sf::RenderTarget& target, const sf::Vector2f& posA, float angle)
	{
		if (_animList.size() == 0 || !_animList[_currentAnimation].isLoad) return;
		const sf::FloatRect viewportRect = target.getView().getViewport();

		_sprite.setTexture(*_animList[_currentAnimation].GetCurTexture());
		_sprite.setPosition(posA);

		if (viewportRect.intersects(_sprite.getLocalBounds()))
		{
			_sprite.setOrigin(_sprite.getGlobalBounds().height / 2, _sprite.getGlobalBounds().width / 2);
			_sprite.setRotation(angle);
			target.draw(_sprite);
		}
	}

	sf::FloatRect AnimationManager::GetRect() const 
	{ 
		return _sprite.getGlobalBounds(); 
	}
}