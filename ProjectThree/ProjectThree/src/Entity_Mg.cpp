#include "Entity_Mg.h"

namespace ProjectThree
{

	EntityManager::EntityManager(std::shared_ptr<Level_Manager> L_M, std::shared_ptr<Scripts_Manager> S_M)
		: _levelManager(L_M), scriptManager(S_M)
	{
		entityObjects = _levelManager->Lvl_Other_Vec();
		_solidObjects = _levelManager->Lvl_Solid_Vec();

		std::string Name, Param;

		_entitys.resize(entityObjects.size() - 1);

		int count = 0;

		for (auto i : entityObjects)
		{
			Param = i.name.substr(0, i.name.find('_'));
			Name = i.name.substr(i.name.find('_') + 1);

			if (Param == "Hero")
			{
				_hero = std::make_shared<Hero>(Name, i.poss);
				if (scriptManager->Get_Anim_Manager(Name) != NULL)
				{
					_hero->setAnimManager(*scriptManager->Get_Anim_Manager(Name));
				}

			}
			else if (Param == "NPC")
			{
				_entitys[count++] = std::make_shared<NPC>(Name, i.poss);
			}
			else { std::cout << i.name << " - bad object" << std::endl; }
		}
	}

	void EntityManager::update(double time)
	{
		_hero->update(time);

		for (auto entity : _entitys) { 
			if (entity != nullptr) {
				entity->update(time);
			}
				
		}
	}

	void EntityManager::draw(sf::RenderTarget& Target)
	{
		_hero->drawAnimation(Target);

		for (auto entity : _entitys) {
			if (entity != nullptr) {
				entity->drawAnimation(Target);
			}
		}
	}

	void EntityManager::setScript()
	{
		if (scriptManager->Get_Anim_Manager(_hero->getName()) != nullptr)
		{
			_hero->setAnimManager(*scriptManager->Get_Anim_Manager(_hero->getName()));
		}

		for (auto entity : _entitys)
		{
			if (scriptManager->Get_Anim_Manager(entity->getName()) != nullptr)
			{
				entity->setAnimManager(*scriptManager->Get_Anim_Manager(_hero->getName()));
			}
		}
	}

	std::shared_ptr<Hero> EntityManager::getHero()
	{
		if (_hero == nullptr) {
			return std::shared_ptr<Hero>();
		}

		return _hero;
	}

	sf::Vector2f EntityManager::getHeroPosition() const
	{
		if (_hero == nullptr) {
			return{ 0.f,0.f };
		}

		return _hero->getPosition();		
	}
}