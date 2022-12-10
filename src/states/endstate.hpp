#pragma once

#include <map>

#include "../button.hpp"
#include "../enemy_factory.hpp"
#include "../highscores.hpp"
#include "state.hpp"

/**
 * @brief A gamestate run by GUI corresponding to the game over screen
 */
class EndState : public State {
 public:
  /**
   * @brief Construct a new End State object
   *
   * @param gui A ref to the GUI
   * @param window A ref to the window to draw on
   * @param score The score that was achieved in game
   * @param difficulty The difficulty that the game was played on
   */
  EndState(GUI& gui, sf::RenderWindow& window, uint32_t score, Difficulty difficulty);

  /**
   * @brief Destroy the End State object
   * Frees the buttons
   */
  ~EndState();

  /**
   * @brief Run and draw the Game Over state of the software. (Hosts the loop
   * that Polls GUI events, calls the necessary backend methods and draws the
   * window. Allows saving the score, displays top scores and has a button to
   * main menu.)
   * Exits the loop and calls GUIs MoveToMenuState(int score) when
   * the user presses "Main menu".
   *
   */
  void Run();

 private:
  uint32_t m_score;
  Difficulty m_difficulty;
  std::map<int32_t, Button*> m_buttons;
  Highscores m_highscores;
  std::string m_input;

  sf::Text m_text_score;
  sf::Text m_text_name;
  sf::Text m_text_highscores;

  sf::Font m_font;

  /**
   * @brief Polls the events that have happened in GUI
   */
  void Priv_PollEvents();

  /**
   * @brief Draws the frame to the screen
   */
  void Priv_Draw();
};