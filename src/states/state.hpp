#pragma once
#include <SFML/Graphics.hpp>

#include "../gui.hpp"
/**
 * @brief Abstract State class represents the classes that run and draw the
 * different software states.
 */
class State {
 public:
  /**
   * @brief Construct a new State object
   *
   * @param gui A ref to the gui
   * @param window A ref to the window
   */
  State(GUI& gui, sf::RenderWindow& window) : m_gui(gui), m_window(window) {}
  /**
   * @brief Virtual destructor
   */
  virtual ~State() = default;

  /**
   * @brief Run the state. (Hosts the loop that Polls GUI events, calls the
   * necessary backend methods and draws the window.)
   * A pure virtual function
   */
  virtual void Run() = 0;

 protected:
  GUI& m_gui;
  sf::RenderWindow& m_window;
  sf::Event m_event;
};