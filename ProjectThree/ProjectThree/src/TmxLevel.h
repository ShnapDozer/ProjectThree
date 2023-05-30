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
        TmxPolygon Polygon = { { 0,0 },{ 0,0 }, { 0,0 }, { 0,0 } };
        sf::Vector2f poss;
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
        // Загружает данные из TMX в память объекта.
        bool LoadFromFile(const std::string& filepath);

        TmxObject GetFirstObject(const std::string& name) const;
        void GetAllObjects(const std::string& name, std::vector<TmxObject>& Cont);
        void GetOtherObjects(const std::string& name, std::vector<TmxObject>& Cont);
        sf::Vector2i GetTileSize() const;
        float GetTilemapWidth() const;
        float GetTilemapHeight() const;
        sf::Vector2f GetTilemapSize() const;

        // Рисует все слои тайлов один за другим,
        //  но не рисует объекты (рисованием которых должна заниматься игра).
        // Принимает любую цель для рисования, например, sf::RenderWindow.
        void Draw(sf::RenderTarget& target, sf::Vector2f MapPos) const;

    private:
        int m_width = 0;
        int m_height = 0;
        int m_tileWidth = 0;
        int m_tileHeight = 0;
        int m_firstTileID = 0;
        Type m_type = Type::non;
        sf::Texture m_tilesetImage;
        std::string  m_orientation = "non";
        std::vector<TmxObject> m_objects;
        std::vector<TmxLayer> m_layers;
    };

    bool P_intersectRect(const TmxPolygon& P, const sf::FloatRect& Rect);
    bool P_contains(const TmxPolygon& P, const sf::Vector2f& Point);
    bool T_contains(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& C, const sf::Vector2f& P); // The map must not contain points!!!!
    bool L_intersec(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& A1, const sf::Vector2f& B1);


    class Level_Manager
    {
    public:

        Level_Manager() {}

        bool Add_Lvl(const std::string& Name, const std::string& file)
        {
            Levels[Name] = file;
            return Load_Lvl(Name);
        }

        bool Load_Lvl(const std::string& Name)
        {
            if (Level.LoadFromFile(Levels[Name]))
            {
                Solid.clear();
                Level.GetAllObjects("Solid", Solid);
                Level.GetOtherObjects("Solid", Other);
                return true;
            }
            else return false;
        }

        void Draw_Lvl(sf::RenderTarget& target, sf::Vector2f MapPos) const
        {
            Level.Draw(target, MapPos);
        }
        std::vector<TmxObject> Lvl_Solid_Vec() const { return Solid; }
        std::vector<TmxObject> Lvl_Other_Vec() const { return Other; }
        std::map<std::string, std::string> Lvl_Get_Map() const { return Levels; }
        TmxObject Lvl_FirstObject(const std::string& name) const { return Level.GetFirstObject(name); }

    private:

        std::map<std::string, std::string> Levels;
        std::vector<TmxObject> Solid, Other;
        TmxLevel Level;
    };
}