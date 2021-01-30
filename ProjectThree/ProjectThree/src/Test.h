#pragma once



#include <iostream>
#include <String> 
#include <vector>

#include <SFML/Graphics.hpp>






void Draw_Hex(sf::RenderTarget& target, sf::Vector2f posA = { 0,0 }, int rad = 16, int Plus = 32) 
{
    sf::CircleShape hexagon(rad, 6);
    hexagon.setOrigin(rad, rad);
    hexagon.setRotation(90);
    
    sf::Texture T;
    T.loadFromFile("Data/Levels/Hex Teest/Hex32.png");
    hexagon.setTexture(&T);
}