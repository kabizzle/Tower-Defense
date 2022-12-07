#include "button.hpp"

Button::Button(std::string text, int x, int y) : m_button(sf::RectangleShape(sf::Vector2f(350, 30))) {
    m_button.setPosition(sf::Vector2f(x, y));
    m_button.setFillColor(sf::Color::Cyan);
    m_button.setOutlineThickness(4);
    m_button.setOutlineColor(sf::Color::Cyan);
    
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