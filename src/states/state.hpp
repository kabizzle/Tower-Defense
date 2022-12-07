#pragma once
#include <SFML/Graphics.hpp>

class Gui {  // DUMMY class to get rid of errors
};
/**
 * @brief Abstract State class represents the classes that run and draw the
 * different software states.
 *
 */
class State {
 public:
  /**
   * @brief Construct a new State object
   *
   * @param gui
   * @param window
   */
  State(Gui gui, sf::RenderWindow& window) : m_gui(gui), m_window(window) {}
  /**
   * @brief Destroy the State object
   *
   */
  virtual ~State();

  /**
   * @brief Run the state. (Hosts the loop that Polls GUI events, calls the
   * necessary backend methods and draws the window.)
   *
   */
  virtual void Run() = 0;

 protected:
  Gui& m_gui;
  sf::RenderWindow& m_window;
};