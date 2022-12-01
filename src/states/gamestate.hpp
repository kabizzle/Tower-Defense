#include "game.hpp"
#include "state.hpp"

/**
 * @brief GameState class runs and draws the game part of the software.
 *
 */
class GameState : public State {
 public:
  /**
   * @brief Construct a new Game State object
   *
   * @param gui
   * @param window
   * @param difficulty
   * @param filename
   */
  GameState(Gui gui, sf::RenderWindow& window, Difficulty difficulty,
            const std::string& filename)
      : State(gui, window), m_difficulty(difficulty), m_mapFile(filename) {}

  /**
   * @brief Destroy the Game State object
   *
   */
  ~GameState();

  /**
   * @brief Run and draw the game state. (Hosts the loop that Polls GUI events,
   * calls the necessary backend methods and draws the window. Alternates
   * between the building/upgrading phase and running the waves.)
   * Exits the loop and calls GUIs MoveToEndState(int score) when the game is
   * over.
   *
   */
  void run();

 private:
  Difficulty m_difficulty;
  const std::string& m_mapFile;
};