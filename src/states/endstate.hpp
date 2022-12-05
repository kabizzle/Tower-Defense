#pragma once
#include "state.hpp"

class EndState : public State {
 public:
  /**
   * @brief Construct a new End State object
   *
   * @param gui
   * @param window
   * @param score
   */
  EndState(Gui gui, sf::RenderWindow& window, int score)
      : State(gui, window), m_score(score) {}

  /**
   * @brief Destroy the End State object
   *
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
  int m_score;
};