#pragma once

#include <string> 
#include <vector>

#include <SFML/Graphics.hpp>
#include "LevelManager.h"
#include "Entity.h"

namespace pt
{
class EntityManager
{
public:
    EntityManager(LevelManagerPtr levelManager);

    void update(double time);
    void draw(sf::RenderTarget& Target);

    std::vector<EntityPtr> getEntitys();

    std::shared_ptr<Hero> getHero();
    sf::Vector2f getHeroPosition() const;

private:

    HeroPtr m_hero;
    std::vector<EntityPtr> m_entitys;
};

    typedef std::shared_ptr<EntityManager> EntityManagerPtr;
}
