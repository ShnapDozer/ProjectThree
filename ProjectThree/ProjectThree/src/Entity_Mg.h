#pragma once

#include <iostream>
#include <String> 
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>

#include "Entity.h" 
#include "TmxLevel.h"
#include "Anim.h"
#include"Scripts_Mg.h"


class Entity_Manager
{
public:

	Entity_Manager(std::shared_ptr <Level_Manager> L_M, std::shared_ptr <Scripts_Manager> S_M);

	void Update(float time, const sf::Vector2f& map_Pos, bool ImGui);

	void Draw(sf::RenderTarget& Target);

	void SetScript();

	std::shared_ptr<Hero> GetHero();

    sf::Vector2f GetHeroPos() const;

private:

	std::shared_ptr<Hero> GG;
	std::vector<std::shared_ptr<Entity>> Entity_List;
	std::vector<TmxObject> Entity_Objects, Solid_Objects;
	const std::shared_ptr <Level_Manager> Lvl_Mg;
	std::shared_ptr <Scripts_Manager> Scr_Mg;
};
