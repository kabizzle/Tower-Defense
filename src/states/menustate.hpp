#pragma once
#include <iostream>

#include "../enemy_factory.hpp"
#include "../level_editor.hpp"
#include "../map.hpp"
#include "button.hpp"
#include "state.hpp"

class MenuState : public State {
 public:
  /**
   * @brief Construct a new Menu State object
   *
   * @param gui
   * @param window
   */
  MenuState(Gui gui, sf::RenderWindow& window);

  /**
   * @brief Destroy the Menu State object
   *
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
  std::map<std::string, Button> m_buttons;
  bool m_editing;

  sf::Event m_event;
  void PollEvents();

  void Draw();
};