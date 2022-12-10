#pragma once
#include <iostream>

#include "../button.hpp"
#include "../enemy_factory.hpp"
#include "../level_editor.hpp"
#include "../map.hpp"
#include "state.hpp"

/**
 * @brief A state run by GUI corresponding to the main menu state
 */
class MenuState : public State {
 public:
  /**
   * @brief Construct a new Menu State object
   *
   * @param gui A ref to the GUI
   * @param window A ref to the window
   */
  MenuState(GUI& gui, sf::RenderWindow& window);

  /**
   * @brief Destroy the Menu State object
   * Frees the buttons
   */
  ~MenuState();

  /**
   * @brief Run and draw the Menu state. (Hosts the loop that Polls GUI events,
   * calls the necessary backend methods and draws the window. Has options to
   * select difficulty and map file. Has buttons to game editor and to play.)
   * Exits the loop and calls GUIs MoveToGameState(int score) when the user
   * presses "Play".
   *
   */
  void Run();

 private:
  void RunLevelEditor(int width, int height, const std::string& map);
  Difficulty m_difficulty;
  std::string m_selectedMap;
  int m_width = 30;
  int m_height = 20;
  std::map<int, Button*> m_buttons;
  std::vector<sf::Text> m_texts;
  bool m_editing;

  
  void PollEvents();

  void Draw();
};