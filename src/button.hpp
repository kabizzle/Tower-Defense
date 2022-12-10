#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "tower.hpp"

/**
 * @brief A class for the buttons in the game
 */
class Button {
public:
  /**
   * @brief Construct a new Button object
   * @param text What do display on the button
   * @param x The x-coordinate of the upper left corner
   * @param y The y-coordinate of the upper left corner
   * @param font The font used by the text
   */
  Button(std::string text, int32_t x, int32_t y, sf::Font& font);
  
  /**
   * @brief A virtual destructor
   */
  virtual ~Button() = default;
  
  /**
   * @brief Adds a highlighted border for the button
   */
  void addHighlight();

  /**
   * @brief Removes the highlight
   */
  void removeHighlight();

  /**
   * @brief Makes the button grayed out
   */
  virtual void disableButton();

  /**
   * @brief Restores the original look of the button
   */
  virtual void enableButton();

  /**
   * @brief Changes the text shown in the button
   * @param text The new text
   */
  virtual void changeText(std::string text);

  /**
   * @brief Draws the button on the window
   * @param window A ref to the window where to draw
   */
  virtual void drawButton(sf::RenderWindow& window);

  /**
   * @brief Get the bounds of this button
   * @return sf::FloatRect 
   */
  sf::FloatRect getGlobalBounds();

protected:
  sf::RectangleShape m_button;
  sf::Text m_text;
  sf::Font& m_font;
};

/**
 * @brief A subclass of buttons, for building the towers
 */
class TowerButton : public Button {
public:
  /**
   * @brief Construct a new Tower Button object
   * @param tower The type of tower this is supposed to represent
   * @param x The x-coordinate of the upper left corner
   * @param y The y-coordinate of the upper left corner
   * @param font The font used by the text 
   */
  TowerButton(TowerType tower, int32_t x, int32_t y, sf::Font& font);

  /**
   * @brief Default destructor
   */
  ~TowerButton() = default;

  /**
   * @brief Draws the button on the window
   * @param window A ref to the window where to draw
   */
  void drawButton(sf::RenderWindow& window);

  /**
   * @brief Makes the button grayed out
   */
  void disableButton();

  /**
   * @brief Restores the original look of the button
   */
  void enableButton();

private:
  sf::Sprite m_sprite;
  std::string m_name;
};