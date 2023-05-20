#include "TmxLevel.h"

#include <iostream>
#include <algorithm>
#include "TinyXML2/tinyxml2.h"

namespace ProjectThree
{

    using namespace tinyxml2;

    // On Windows, backslash '\\' is directory separator in paths
    // On UNIX paths separated with slash '/'.
#if defined(_WIN32)
    const char DIR_SEPARATOR = '\\';
#else
    const char DIR_SEPARATOR = '/';
#endif

    float V_product(const sf::Vector2f& A, const sf::Vector2f& B) { return (A.x * B.y - A.y * B.x); }

    bool L_intersec(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& A1, const sf::Vector2f& B1)
    {
        float uA = ((B1.x - A1.x) * (A.y - A1.y) - (B1.y - A1.y) * (A.x - A1.x)) / ((B1.y - A1.y) * (B.x - A.x) - (B1.x - A1.x) * (B.y - A.y));

        float uB = ((B.x - A.x) * (A.y - A1.y) - (B.y - A.y) * (A.x - A1.x)) / ((B1.y - A1.y) * (B.x - A.x) - (B1.x - A1.x) * (B.y - A.y));

        if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) return true;

        return false;
    }

    bool T_contains(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& C, const sf::Vector2f& P)
    {
        float BA = V_product((B - A), (P - A));
        float CB = V_product((C - B), (P - B));
        float AC = V_product((A - C), (P - C));

        return (BA >= 0.0 && CB >= 0.0 && AC >= 0.0) || (BA < 0.0 && CB < 0.0 && AC < 0.0);
    }

    bool P_contains(const TmxPolygon& P, const sf::Vector2f& Point)
    {
        if (T_contains(P.first, P.second, P.third, Point))
        {
            return true;
        }
        else if (T_contains(P.first, P.fourth, P.third, Point))
        {
            return true;
        }
        else return false;
    }

    bool P_intersectRect(const TmxPolygon& P, const sf::FloatRect& Rect)
    {
        std::vector<sf::Vector2f> RV = { {Rect.left, Rect.top}, {Rect.left + Rect.width, Rect.top},
        {Rect.left + Rect.width, Rect.top + Rect.width }, {Rect.left, Rect.top + Rect.width } };

        int next;

        for (int current = 0; current < RV.size(); ++current)
        {
            next = current + 1;
            if (current == 3)next = 0;
            if (L_intersec(RV[current], RV[next], P.first, P.second)) return true;
            if (L_intersec(RV[current], RV[next], P.second, P.third)) return true;
            if (L_intersec(RV[current], RV[next], P.third, P.fourth)) return true;
            if (L_intersec(RV[current], RV[next], P.fourth, P.first)) return true;
        }
        return false;
    }

    void TmxObject::draw(sf::RenderTarget& target, sf::Color color) // Rework!!!!!!
    {
        sf::VertexArray polygon(sf::Quads, 4);

        polygon[0].position = Polygon.first;
        polygon[1].position = Polygon.second;
        polygon[3].position = Polygon.third;
        polygon[2].position = Polygon.fourth;

        target.draw(polygon);
    }


    // Returns parent directory of given path;
    std::string GetParentDirectory(const std::string& filepath)
    {
        const size_t slashPos = filepath.find_last_of('/');
        std::string parentDir;
        if (slashPos != std::string::npos)
        {
            parentDir = filepath.substr(0, slashPos);
        }
        return parentDir;
    }

    // Joins two path fragments, e.g. directory path and filename
    std::string JoinPaths(const std::string& path, const std::string& subpath)
    {
        if (path.empty())
        {
            return subpath;
        }
        if (subpath.empty())
        {
            return path;
        }

        return path + DIR_SEPARATOR + subpath;
    }

    sf::Vector2f pixelToScreenCoords(float x, float y, float tile_Width, float tile_Height)
    {
        sf::Vector2f F;
        float tileY = y / tile_Height;
        float tileX = x / tile_Height;
        F.x = (tileX - tileY) * tile_Width / 2;
        F.y = (tileX + tileY) * tile_Height / 2;
        return F;
    }

    TmxPolygon pixelRectToScreenPolygon(sf::FloatRect& oldRect, float tile_Width, float tile_Height)
    {
        TmxPolygon polygon;
        polygon.first = pixelToScreenCoords(oldRect.left, oldRect.top, tile_Width, tile_Height);
        polygon.second = pixelToScreenCoords(oldRect.left + oldRect.width, oldRect.top, tile_Width, tile_Height);
        polygon.third = pixelToScreenCoords(oldRect.left, oldRect.top + oldRect.height, tile_Width, tile_Height);
        polygon.fourth = pixelToScreenCoords(oldRect.left + oldRect.width, oldRect.top + oldRect.height, tile_Width, tile_Height);

        return polygon;
    }

    // Parses hex-encoded RGB like "6d9fb9"
    sf::Color ParseColor(const std::string& hexRGB)
    {
        char* pEnd = nullptr;
        const long hexValue = strtol(hexRGB.c_str(), &pEnd, 16);
        if (*pEnd != '\0')
        {
            throw std::runtime_error(hexRGB + " is not valid hex-encoded RGB color");
        }

        const uint8_t red = uint8_t((hexValue >> 16) % 256);
        const uint8_t green = uint8_t((hexValue >> 8) % 256);
        const uint8_t blue = uint8_t(hexValue % 256);

        return sf::Color(red, green, blue);
    }

    float ParseFloat(const std::string& str)
    {
        char* pEnd = nullptr;
        const float value = strtof(str.c_str(), &pEnd);

        return value;
    }

    int TmxObject::GetPropertyInt(const std::string& propertyName)
    {
        return std::stoi(properties[propertyName].c_str());
    }

    float TmxObject::GetPropertyFloat(const std::string& propertyName)
    {
        return ParseFloat(properties[propertyName].c_str());
    }

    std::string TmxObject::GetPropertyString(const std::string& propertyName)
    {
        return properties[propertyName];
    }

    void TmxObject::MoveBy(const sf::Vector2f& movement)
    {
        rect.left += movement.x;
        rect.top += movement.y;
        sprite.move(movement);
    }

    void TmxObject::MoveTo(const sf::Vector2f& position)
    {
        rect.left = position.x;
        rect.top = position.y;
        sprite.setPosition(position);
    }

    bool TmxLevel::LoadFromFile(const std::string& filepath)
    {
        XMLDocument levelFile;

        // Load XML into in-memory XMLDocument.
        if (levelFile.LoadFile(filepath.c_str()) != XML_SUCCESS)
        {
            throw std::runtime_error("Loading level \"" + filepath + "\" failed.");
        }

        // Element <map> should be root in TMX format.
        XMLElement* map = levelFile.FirstChildElement("map");
        if (map == 0)
        {
            throw std::runtime_error("<map> element not found");
        }

        m_layers.clear();
        m_objects.clear();

        // Map element example:
        //   <map version="1.0" orientation="orthogonal"
        //    width="10" height="10" tilewidth="34" tileheight="34">
        m_orientation = std::string(map->Attribute("orientation"));
        m_width = std::stoi(map->Attribute("width"));
        m_height = std::stoi(map->Attribute("height"));
        m_tileWidth = std::stoi(map->Attribute("tilewidth"));
        m_tileHeight = std::stoi(map->Attribute("tileheight"));

        // Retrieve tileset description and the first tile GID (Group Identifier).
        XMLElement* tilesetElement = map->FirstChildElement("tileset");
        m_firstTileID = std::stoi(tilesetElement->Attribute("firstgid"));

        // <image> contains tileset texture
        XMLElement* image = tilesetElement->FirstChildElement("image");
        const std::string imageFilename = image->Attribute("source");
        const std::string imagePath = JoinPaths(GetParentDirectory(filepath), imageFilename);

        sf::Color matteColor = sf::Color(0, 0, 0, 0);
        if (image->Attribute("trans") != nullptr)
        {
            matteColor = ParseColor(image->Attribute("trans"));
        }

        sf::Image img;
        if (!img.loadFromFile(imagePath))
        {
            std::cout << "Failed to load tile sheet." << std::endl;
            return false;
        }

        // Set tileset matte color, used to composite transparent image on
        //  background filled with matte color.
        img.createMaskFromColor(matteColor);
        // Load texture from file.
        m_tilesetImage.loadFromImage(img);
        // Keep texture sharp when resized.
        m_tilesetImage.setSmooth(false);

        // Retrieve amount of rows and columns in tileset.
        const int columns = m_tilesetImage.getSize().x / m_tileWidth;
        const int rows = m_tilesetImage.getSize().y / m_tileHeight;

        // Collect texture rects list.
        // Each texture rect is subimage in tileset image, i.e. single tile image.
        std::vector<sf::IntRect> subRects;
        for (int y = 0; y < rows; y++)
        {
            for (int x = 0; x < columns; x++)
            {
                sf::IntRect rect;
                rect.top = y * m_tileHeight;
                rect.height = m_tileHeight;
                rect.left = x * m_tileWidth;
                rect.width = m_tileWidth;
                subRects.push_back(rect);
            }
        }

        ////////////////////////////////////////////////////////////////////////////
        /// Parse tile layers
        ///
        XMLElement* layerElement = map->FirstChildElement("layer");
        while (layerElement)
        {
            TmxLayer layer;

            // Copy transparency if it set in XML,
            //  or make layer opaque (255).
            if (layerElement->Attribute("opacity") != nullptr)
            {
                float opacity = ParseFloat(layerElement->Attribute("opacity"));
                layer.opacity = sf::Uint8(255 * opacity);
            }
            else
            {
                layer.opacity = 255;
            }

            // <data> contains multiple tiles description.
            XMLElement* layerDataElement = layerElement->FirstChildElement("data");
            if (layerDataElement == nullptr)
            {
                std::cout << "Bad map. No layer information found." << std::endl;
            }

            // <tile> contains single tile description.
            XMLElement* tileElement = layerDataElement->FirstChildElement("tile");
            if (tileElement == nullptr)
            {
                std::cout << "Bad map. No tile information found." << std::endl;
                return false;
            }

            int x = 0;
            int y = 0;
            while (tileElement)
            {
                const int tileGID = std::stoi(tileElement->Attribute("gid"));
                const int subRectToUse = tileGID - m_firstTileID;

                // Figure out texture rect for each tile.
                if (subRectToUse >= 0)
                {
                    sf::Sprite sprite;
                    float cartX = static_cast<float>(x * m_tileWidth);
                    float cartY = static_cast<float>(y * m_tileHeight);

                    if (m_orientation == "orthogonal")
                    {
                        m_type = Type::orthogonal;
                        sprite.setTexture(m_tilesetImage);
                        sprite.setTextureRect(subRects[subRectToUse]);
                        sprite.setPosition(cartX, cartY);
                        sprite.setColor(sf::Color(255, 255, 255, layer.opacity));
                    }
                    else if (m_orientation == "isometric")
                    {
                        m_type = Type::isometric;
                        float isoX = (cartX / 2) - cartY - (m_tileWidth / 2);
                        float isoY = ((cartX / 2) + cartY) / 2;
                        sprite.setTexture(m_tilesetImage);
                        sprite.setTextureRect(subRects[subRectToUse]);
                        sprite.setPosition(isoX, isoY);
                        sprite.setColor(sf::Color(255, 255, 255, layer.opacity));
                    }
                    else if (m_orientation == "staggered")
                    {
                        float stragX = cartX + y % 2 * (m_tileWidth / 2);
                        float stragY = y * (m_tileHeight / 2);
                        m_type = Type::staggered;
                        sprite.setTexture(m_tilesetImage);
                        sprite.setTextureRect(subRects[subRectToUse]);
                        sprite.setPosition(cartX, cartY);
                        sprite.setColor(sf::Color(255, 255, 255, layer.opacity));
                    }
                    else if (m_orientation == "hexagonal")
                    {
                        std::cout << "It's not worked! (Hexagonal map not supported)" << std::endl;
                        m_type = Type::hexagonal;
                    }
                    else  std::cout << "Bad map. Orientation is not found" << std::endl;

                    layer.tiles.push_back(std::move(sprite));
                }

                tileElement = tileElement->NextSiblingElement("tile");

                x++;
                if (x >= m_width)
                {
                    x = 0;
                    y++;
                    if (y >= m_height)
                    {
                        y = 0;
                    }
                }
            }

            m_layers.push_back(std::move(layer));

            layerElement = layerElement->NextSiblingElement("layer");
        }

        ////////////////////////////////////////////////////////////////////////////
        /// Collecting objects list.
        ///

        // If there are object layers.
        if (map->FirstChildElement("objectgroup") != nullptr)
        {
            XMLElement* objectGroupElement = map->FirstChildElement("objectgroup");



            while (objectGroupElement)
            {

                std::string objectName;
                if (objectGroupElement->Attribute("name") != nullptr)
                {
                    objectName = objectGroupElement->Attribute("name");
                }

                // Enter into <object> node
                XMLElement* objectElement;
                objectElement = objectGroupElement->FirstChildElement("object");

                while (objectElement)
                {
                    // Collecting object properties - type, name, position, etc.

                    std::string objectType;
                    if (objectElement->Attribute("type") != nullptr)
                    {
                        objectType = objectElement->Attribute("type");
                    }

                    int objectID;
                    if (objectElement->Attribute("id") != nullptr)
                    {
                        objectID = std::stoi(objectElement->Attribute("id"));
                    }

                    float x = std::stof(objectElement->Attribute("x"));
                    float y = std::stof(objectElement->Attribute("y"));
                    float isoX = ((x / 2) - y);
                    float isoY = ((x / 2) + y) / 2;
                    float width = 0;
                    float height = 0;

                    sf::Sprite sprite;
                    sprite.setTexture(m_tilesetImage);
                    sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
                    sprite.setPosition(x, y);

                    if (objectElement->Attribute("width") != nullptr)
                    {
                        width = std::stof(objectElement->Attribute("width"));
                        height = std::stof(objectElement->Attribute("height"));
                    }
                    else if (objectElement->Attribute("gid") != nullptr)
                    {
                        const size_t index = std::stoi(objectElement->Attribute("gid")) - m_firstTileID;
                        width = static_cast<float>(subRects[index].width);
                        height = static_cast<float>(subRects[index].height);
                        sprite.setTextureRect(subRects[index]);
                        sprite.setOrigin(0, height);
                    }

                    // Define object
                    TmxObject object;
                    object.name = objectName;
                    object.type = objectType;
                    object.sprite = sprite;

                    sf::FloatRect objectRect;





                    switch (m_type)
                    {

                    case Type::orthogonal:
                        objectRect.left = x;
                        objectRect.top = y;
                        objectRect.height = height;
                        objectRect.width = width;

                        object.rect = objectRect;
                        object.poss = { object.rect.left, object.rect.top };
                        break;

                    case Type::isometric:

                        objectRect.left = x;
                        objectRect.top = y;
                        objectRect.height = height;
                        objectRect.width = width;

                        object.Polygon = pixelRectToScreenPolygon(objectRect, m_tileWidth, m_tileHeight);
                        object.poss = { object.Polygon.first.x, object.Polygon.first.y };
                        break;

                    case Type::staggered:
                        objectRect.left = x;
                        objectRect.top = y;
                        objectRect.height = height;
                        objectRect.width = width;
                        break;

                    case Type::hexagonal:
                        objectRect.left = x;
                        objectRect.top = y;
                        objectRect.height = height;
                        objectRect.width = width;
                        break;

                    }



                    // Read object properties
                    XMLElement* properties = objectElement->FirstChildElement("properties");
                    if (properties != nullptr)
                    {
                        XMLElement* prop = properties->FirstChildElement("property");
                        if (prop != nullptr)
                        {
                            while (prop)
                            {
                                std::string propertyName = prop->Attribute("name");
                                std::string propertyValue = prop->Attribute("value");

                                object.properties[propertyName] = propertyValue;

                                prop = prop->NextSiblingElement("property");
                            }
                        }
                    }

                    // Add object to list
                    m_objects.push_back(std::move(object));

                    objectElement = objectElement->NextSiblingElement("object");
                }
                objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
            }
        }
        else
        {
            std::cout << "No object layers found..." << std::endl;
        }

        return true;
    }

    TmxObject TmxLevel::GetFirstObject(const std::string& name) const
    {
        // Only first object with given name
        for (size_t i = 0; i < m_objects.size(); i++)
            if (m_objects[i].name == name)
                return m_objects[i];
        throw std::runtime_error("Object with name " + name + " was not found");
    }

    void TmxLevel::GetAllObjects(const std::string& name, std::vector<TmxObject>& Cont)
    {
        for (size_t i = 0; i < m_objects.size(); i++)
        {
            if (m_objects[i].name == name)
            {
                Cont.push_back(m_objects[i]);
            }
        }
    }

    void TmxLevel::GetOtherObjects(const std::string& name, std::vector<TmxObject>& Cont)
    {
        for (size_t i = 0; i < m_objects.size(); i++)
        {
            if (m_objects[i].name != name)
            {
                Cont.push_back(m_objects[i]);
            }
        }
    }

    sf::Vector2i TmxLevel::GetTileSize() const
    {
        return sf::Vector2i(m_tileWidth, m_tileHeight);
    }

    float TmxLevel::GetTilemapWidth() const
    {
        return static_cast<float>(m_tileWidth * m_width);
    }

    float TmxLevel::GetTilemapHeight() const
    {
        return static_cast<float>(m_tileHeight * m_height);
    }

    sf::Vector2f TmxLevel::GetTilemapSize() const
    {
        return sf::Vector2f(GetTilemapWidth(), GetTilemapHeight());
    }

    void TmxLevel::Draw(sf::RenderTarget& target, sf::Vector2f MapPos) const
    {
        float Targ_x = target.getView().getCenter().x - target.getView().getSize().x / 2;
        float Targ_y = target.getView().getCenter().y - target.getView().getSize().y / 2;
        const sf::FloatRect viewportRect(Targ_x, Targ_y, target.getView().getSize().x, target.getView().getSize().y);

        for (const auto& layer : m_layers)
        {
            for (const auto& tile : layer.tiles)
            {

                if (viewportRect.intersects(tile.getGlobalBounds()))
                {
                    target.draw(tile);
                }
            }
        }
    }
}