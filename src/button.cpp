#include "button.hpp"
#define TILE_SIZE 30

Button::Button(std::string text, int x, int y, sf::Font& font) : m_button(sf::RectangleShape(sf::Vector2f(350, 30))), m_font(font) {
    m_button.setPosition(sf::Vector2f(x, y));
    m_button.setFillColor(sf::Color::Cyan);
    m_button.setOutlineThickness(4);
    m_button.setOutlineColor(sf::Color::Cyan);
    
    m_text.setFont(m_font);
    m_text.setString(text);
    m_text.setCharacterSize(15);
    m_text.setPosition(sf::Vector2f(x + 20, y + 10));
}

void Button::addHighlight() {
    m_button.setOutlineColor(sf::Color::Red);
    m_text.setStyle(sf::Text::Bold);
}

void Button::removeHighlight() {
    m_button.setOutlineColor(sf::Color::Cyan);
    m_text.setStyle(sf::Text::Regular);

}

void Button::drawButton(sf::RenderWindow& window) {
    window.draw(m_button);
    window.draw(m_text);
}

sf::FloatRect Button::getGlobalBounds() {
    return sf::FloatRect(m_button.getPosition(), m_button.getSize());
}


TowerButton::TowerButton(TowerType tower, std::string text, int x, int y, sf::Font& font) : Button(text, x, y, font) {
    switch (tower) {
        case TowerType::Freshman:
            m_sprite = Renderables::getFreshman1Sprite();
            break;
        case TowerType::Teekkari:
            m_sprite = Renderables::getTeekkari1Sprite();
            break;
        case TowerType::Bachelor:
            m_sprite = Renderables::getBachelor1Sprite();
            break;
        case TowerType::Master:
            m_sprite = Renderables::getMaster1Sprite();
            break;
        case TowerType::Doctor:
            m_sprite = Renderables::getDoctor1Sprite();
            break;
        case TowerType::Calculator:
            m_sprite = Renderables::getCalculatorSprite();
            break;
        case TowerType::CoffeeTable:
            m_sprite = Renderables::getCoffeeTableSprite();
            break;
    }

    m_sprite.setPosition(sf::Vector2f(x, y));
    
    m_button.setPosition(sf::Vector2f(x + TILE_SIZE, y));
    m_button.setFillColor(sf::Color::Cyan);
    m_button.setOutlineThickness(4);
    m_button.setOutlineColor(sf::Color::Cyan);
    
    m_text.setFont(m_font);
    m_text.setString(text);
    m_text.setCharacterSize(15);
    m_text.setPosition(sf::Vector2f(x + TILE_SIZE + 20, y + 10));
}

void TowerButton::drawButton(sf::RenderWindow& window) {
    window.draw(m_sprite);    
    window.draw(m_button);
    window.draw(m_text);
}

