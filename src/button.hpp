#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public: 
    Button(std::string text, int x, int y);
    void addHighlight();
    void removeHighlight();
    void drawButton(sf::RenderWindow& window);

private:
    sf::RectangleShape m_button;
    sf::Text m_text;
};