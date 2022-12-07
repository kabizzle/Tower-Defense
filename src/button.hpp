#pragma once

#include <SFML/Graphics.hpp>
#include <string>



class Button {
public: 
    Button(std::string text, int x, int y, sf::Font& font);
    
    ~Button() = default;
    
    void addHighlight();
    void removeHighlight();
    void drawButton(sf::RenderWindow& window);
    sf::FloatRect getGlobalBounds();

private:
    sf::RectangleShape m_button;
    sf::Text m_text;
    sf::Font& m_font;
};