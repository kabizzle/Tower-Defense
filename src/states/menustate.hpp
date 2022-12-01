#include "state.hpp"

class MenuState : public State {
 public:
  /**
   * @brief Construct a new Menu State object
   *
   * @param gui
   * @param window
   */
  MenuState(Gui gui, sf::RenderWindow& window) : State(gui, window) {}

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
  void run();

 private:
};