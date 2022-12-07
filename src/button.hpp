#pragma once

#include <SFML/Graphics.hpp>
#include <string>



class Button {
public: 
    Button(std::string text, int x, int y);
    
    ~Button() = default;
    
    void addHighlight();
    void removeHighlight();
    void drawButton(sf::RenderWindow& window);
    sf::FloatRect getGlobalBounds();

private:
    sf::RectangleShape m_button;
    sf::Text m_text;
};