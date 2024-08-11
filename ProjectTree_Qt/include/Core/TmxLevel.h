#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include <SFML/Graphics.hpp>

// В картах TMX объект - это область на карте, имеющая имя, тип,
//  границы, набор пользовательских свойств (в формате ключ-значение)
//  и текстурные координаты.
// Текстурные координаты позволяют связать с объектом спрайт,
//  использующий основную текстуру карты как источник данных.

namespace pt
{
    enum class Type
    {
        orthogonal,
        isometric,
        staggered,
        hexagonal,
        non
    };

    struct TmxPolygon
    {
        sf::Vector2f first;
        sf::Vector2f second;
        sf::Vector2f third;
        sf::Vector2f fourth;
    };

    struct NameLVL
    {
        std::string first;
        std::string second;
    };

    struct TmxObject
    {
        int GetPropertyInt(const std::string& propertyName);
        float GetPropertyFloat(const std::string& propertyName);
        std::string GetPropertyString(const std::string& propertyName);
        void draw(sf::RenderTarget& target, sf::Color);

        void MoveBy(const sf::Vector2f& movement);
        void MoveTo(const sf::Vector2f& position);

        std::string name;
        std::string type;
        sf::FloatRect rect = { 0,0,0,0 };
        TmxPolygon _polygon = { { 0,0 },{ 0,0 }, { 0,0 }, { 0,0 } };
        sf::Vector2f possition;
        std::map<std::string, std::string> properties;

        sf::Sprite sprite;
    };



    // В картах TMX слой - это набор тайлов (спрайтов),
    //  из которых складывается ландшафт карты.
    // Слоёв может быть несколько, что позволяет нарисовать,
    //  например, слой травы поверх слоя земли.
    struct TmxLayer
    {
        sf::Uint8 opacity = 0;
        std::vector<sf::Sprite> tiles;
    };

    class TmxLevel
    {
    public:
        TmxLevel();
        ~TmxLevel();

        bool loadFromFile(const std::string& filepath);

        float getTilemapWidth() const;
        float getTilemapHeight() const;
        sf::Vector2i getTileSize() const;
        sf::Vector2f getTilemapSize() const;

        std::map<std::string, std::vector<TmxObject>> getObjectsMap() const;

        void draw(sf::RenderTarget& target) const;

    private:
        int mapWidth;
        int mapHeight;
        int tileWidth;
        int tileHeight;
        int mapFirstTileID;
        
        Type mapType;
        sf::Texture tilesetImage;
        std::string  mapOrientation;
        
        std::vector<TmxLayer> _layers;
        std::map<std::string, std::vector<TmxObject>> _objectsMap;
    };

    bool P_intersectRect(const TmxPolygon& P, const sf::FloatRect& Rect);
    bool P_contains(const TmxPolygon& P, const sf::Vector2f& Point);
    bool T_contains(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& C, const sf::Vector2f& P); // The map must not contain points!!!!
    bool L_intersec(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& A1, const sf::Vector2f& B1);
}