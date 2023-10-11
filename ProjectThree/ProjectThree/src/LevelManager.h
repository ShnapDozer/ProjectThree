#pragma once

#include <string>
#include <map>
#include <vector>

#include "Object.h"
#include "TmxLevel.h"

namespace pt 
{
    class LevelManager : public Object {
    public:

        LevelManager();
        ~LevelManager();

        std::map<std::string, std::string> getLevels() const;
        std::vector<TmxObject> getGroupObjects(const std::string& groupName) const;

        bool addLevel(const std::string& name, const std::string& filePath);
        bool loadLevel(const std::string& name);
        void draw(sf::RenderTarget& target) const;

    private:

        std::shared_ptr<TmxLevel> _level;
        std::map<std::string, std::string> _levels;
    };
}
