#include "LevelManager.h"

pt::LevelManager::LevelManager() 
    : _level(std::make_shared<TmxLevel>())
{

}

pt::LevelManager::~LevelManager()
{

}

std::map<std::string, std::string> pt::LevelManager::getLevels() const
{
    return _levels;
}

std::vector<pt::TmxObject> pt::LevelManager::getGroupObjects(const std::string& groupName) const
{
    return _level->getObjectsMap()[groupName];
}

bool pt::LevelManager::addLevel(const std::string& name, const std::string& filePath)
{
    _levels[name] = filePath;

    return loadLevel(name);
}

bool pt::LevelManager::loadLevel(const std::string& name)
{
    return _level->loadFromFile(_levels[name]);
}

void pt::LevelManager::draw(sf::RenderTarget& target) const
{
    _level->draw(target);
}
