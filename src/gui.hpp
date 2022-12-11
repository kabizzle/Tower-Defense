#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

#include "button.hpp"
#include "renderables.hpp"

class State;  //Forward declaration

/**
 * @brief A class to add elements to the Graphical User Interface
 */
class GUI {
 public:
  /**
   * @brief Construct a new GUI object
   * This will create a Renderables object, which stores the sprites of everything
   */
  GUI();

  /**
   * @brief Destroy the GUI object
   * Frees the dynamically allocated member variables
   */
  ~GUI();

  /**
   * @brief Initializes the different variables and makes the window ready
   */
  void init();

  /**
   * @brief Tells if the GUI is open
   * @return bool
   */
  bool running();

  // Detect events in gui window
  //void pollEvents();

  /**
   * @brief Updates GUI each frame
   */
  void update();

  // move enemy
  //void moveEnemies();

  /**
   * @brief Is used to create button objects
   * 
   * @param text What is shown on the button
   * @param x The x-coordinate of the upper left corner
   * @param y The y-coordinate of the upper left corner
   * @return Button* 
   */
  Button* CreateButton(std::string text, int32_t x, int32_t y);

  /**
   * @brief Is used to create towerbutton objects
   * 
   * @param text What is shown on the button
   * @param x The x-coordinate of the upper left corner
   * @param y The y-coordinate of the upper left corner
   * @return Button* 
   */
  TowerButton* CreateTowerButton(TowerType type, int32_t x, int32_t y);

  /**
   * @brief Get the Font used here
   * @return const sf::Font& 
   */
  const sf::Font& GetFont() const;

  /**
   * @brief Changes the state present in the GUI
   * @param state The new state
   */
  void ChangeState(State* state);


 private:
  Renderables* m_renderables;
  sf::RenderWindow* m_window;       // window that displays game
  sf::VideoMode m_videoMode;        // dimensions of window
  sf::Event m_event;                // events that occur in gui window
  std::vector<sf::Sprite> enemies;  // list of enemy objects
  float x_velo = 3.f;
  float y_velo = 4.f;
  sf::Vector2f start;
  sf::Font m_font;
  State* m_state;
  State* m_new_state;

  /**
   * @brief Private deletes the state in the GUI, if present
   */
  void Priv_DeleteState();
};
