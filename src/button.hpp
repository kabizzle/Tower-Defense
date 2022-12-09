#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "tower.hpp"

class Button {
public: 
    Button(std::string text, int x, int y, sf::Font& font);
    
    virtual ~Button() = default;
    
    void addHighlight();
    void removeHighlight();

    void disableButton();
    void enableButton();
    virtual void changeText(std::string text);

    virtual void drawButton(sf::RenderWindow& window);
    sf::FloatRect getGlobalBounds();

protected:
    sf::RectangleShape m_button;
    sf::Text m_text;
    sf::Font& m_font;
};


class TowerButton : public Button{
public:
    TowerButton(TowerType tower, int x, int y, sf::Font& font);
    void drawButton(sf::RenderWindow& window);
    void disableButton();
    void enableButton();

private:
    sf::Sprite m_sprite;
    std::string m_name;
};