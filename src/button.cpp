#include "button.hpp"
#define TILE_SIZE 30

Button::Button(std::string text, int32_t x, int32_t y, sf::Font& font)
    : m_button(sf::RectangleShape(sf::Vector2f(350, 30))), m_font(font) {
  m_button.setPosition(sf::Vector2f(x, y));
  // m_button.setFillColor(sf::Color::Cyan);
  m_button.setOutlineThickness(4);
  m_button.setOutlineColor(sf::Color::Transparent);

  m_text.setFont(m_font);
  m_text.setFillColor(sf::Color::Black);
  m_text.setString(text);
  m_text.setCharacterSize(24);

  m_text.setPosition(x + 175 - text.length()*8, y);


  if (text == "Play now") {
    m_button.setFillColor(sf::Color::Blue);
    m_text.setFillColor(sf::Color::White);
    // m_text.setPosition(x + 124, y); 

    // m_button.setOutlineColor(sf::Color::Blue);
  } else if (text == "Give up") {
    m_button.setFillColor(sf::Color::Red);
    m_text.setFillColor(sf::Color::White);
    // m_button.setOutlineColor(sf::Color::Red);
  } else {  
    m_button.setFillColor(sf::Color::Cyan);
  }
}

void Button::addHighlight() {
  m_button.setOutlineColor(sf::Color::Blue);
  m_text.setStyle(sf::Text::Bold);
}

void Button::removeHighlight() {
  m_button.setOutlineColor(sf::Color::Transparent);
  m_text.setStyle(sf::Text::Regular);
}

void Button::drawButton(sf::RenderWindow& window) {
  window.draw(m_button);
  window.draw(m_text);
}

sf::FloatRect Button::getGlobalBounds() {
  return sf::FloatRect(m_button.getPosition(), m_button.getSize());
}

void Button::enableButton() { this->m_button.setFillColor(sf::Color::Cyan); }

void Button::disableButton() {
  this->m_button.setFillColor(sf::Color(190, 190, 190, 190));
}

void Button::changeText(std::string text) {
  this->m_text.setString(text);
}


TowerButton::TowerButton(TowerType tower, int32_t x, int32_t y,
                         sf::Font& font)
    : Button("", x, y, font) {
  switch (tower) {
    case TowerType::Freshman:
      m_sprite = Renderables::getFreshman1Sprite();
      m_name = "Freshman (attack)";
      break;
    case TowerType::Teekkari:
      m_sprite = Renderables::getTeekkari1Sprite();
      m_name = "Teekkari (attack)";
      break;
    case TowerType::Bachelor:
      m_sprite = Renderables::getBachelor1Sprite();
      m_name = "Bachelor (attack)";
      break;
    case TowerType::Master:
      m_sprite = Renderables::getMaster1Sprite();
      m_name = "Master (attack)";
      break;
    case TowerType::Doctor:
      m_sprite = Renderables::getDoctor1Sprite();
      m_name = "Doctor (attack)";
      break;
    case TowerType::Calculator:
      m_sprite = Renderables::getCalculatorSprite();
      m_name = "Calculator (buff)";
      break;
    case TowerType::CoffeeTable:
      m_sprite = Renderables::getCoffeeTableSprite();
      m_name = "CoffeeTable (heal)";
      break;
  }

  m_sprite.setPosition(sf::Vector2f(x, y));

  m_button.setSize(sf::Vector2f(320, 30));
  m_button.setPosition(sf::Vector2f(x + TILE_SIZE, y));
  m_button.setFillColor(sf::Color::Cyan);
  m_button.setOutlineThickness(4);
  m_button.setOutlineColor(sf::Color::Transparent);

  m_text.setFont(m_font);
  m_text.setFillColor(sf::Color::Black);
  m_text.setString(m_name + " " + std::to_string(Tower::towerPrices.at(tower)) + " cr");
  m_text.setCharacterSize(20);
  m_text.setPosition(sf::Vector2f(x + 32, y + 2));
}

void TowerButton::drawButton(sf::RenderWindow& window) {
  window.draw(m_sprite);
  window.draw(m_button);
  window.draw(m_text);
}

void TowerButton::disableButton() {
  this->m_button.setFillColor(sf::Color(190, 190, 190, 190));
  this->m_sprite.setColor(sf::Color(190, 190, 190, 190));
}

void TowerButton::enableButton() {
  this->m_button.setFillColor(sf::Color::Cyan);
  this->m_sprite.setColor(sf::Color(255, 255, 255, 255));
}
