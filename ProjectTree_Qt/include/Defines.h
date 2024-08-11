#ifndef DEFINES_H
#define DEFINES_H

#include <memory>
#include <vector>
#include <variant>

#include <SFML/Graphics.hpp>

#include "QSFMLCanvas.h"

namespace pt
{

typedef std::vector <std::string> StringList;
typedef const std::string& ConstStringRef;
typedef std::shared_ptr<QSFMLCanvas> RenderWindowPtr;
typedef std::shared_ptr<sf::View> ViewPtr;
typedef std::variant<bool, int, float, double, std::string> GameAppParameter;
typedef std::unordered_map<std::string, GameAppParameter> GameAppParameterUMap;
}

#endif


