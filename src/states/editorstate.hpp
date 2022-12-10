#pragma once
#include <iostream>

#include "../button.hpp"
#include "../enemy_factory.hpp"
#include "../level_editor.hpp"
#include "../map.hpp"
#include "state.hpp"

/**
 * @brief A gamestate run by GUI corresponding to the level editor
 */
class EditorState : public State {
 public:
  /**
   * @brief Construct a new Menu State object
   * @param gui A ref to the GUI used
   * @param window A ref to the window used
   * @param mapPath The map file which is edited
   */
  EditorState(GUI& gui, sf::RenderWindow& window, std::string& mapPath);

  /**
   * @brief Destroy the Menu State object
   * Frees the buttons
   */
  ~EditorState();

  /**
   * @brief Run and draw the Menu state.
   * (Hosts the loop that Polls GUI events, calls the necessary backend
   * methods and draws the window. Has options to select difficulty and map
   * file. Has buttons to game editor and to play.)
   * Exits the loop and calls GUIs MoveToGameState(int score) when the user
   * presses "Play".
   *
   */
  void Run();

 private:
  LevelEditor m_editor;
  std::vector<sf::Sprite> m_mapTileSprites;
  std::map<int, Button*> m_buttons;
  sf::RectangleShape m_selectedShape;
  sf::Text m_validated, m_unvalidated, m_instructions;
  std::string m_mapPath;
  int32_t m_selX,
      m_selY;  // The selected tile on the map, -1, -1 means nothing selected
  bool m_drawSelectedShape;
  int32_t m_selectedButton;

  //Private functions
  /**
   * @brief Polls the events that have happened in GUI
   */
  void Priv_PollEvents();

  /**
   * @brief Draws the frame to the screen
   * 
   */
  void Priv_Draw();
};