#pragma once
#include "../game.hpp"
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
  GameState(GUI& gui, sf::RenderWindow& window, Difficulty difficulty,
            const std::string& filename);

  /**
   * @brief Destroy the Game State object
   *
   */
  ~GameState() = default;

  /**
   * @brief Run and draw the game state. (Hosts the loop that Polls GUI events,
   * calls the necessary backend methods and draws the window. Alternates
   * between the building/upgrading phase and running the waves.)
   * Exits the loop and calls GUIs MoveToEndState(int score) when the game is
   * over.
   *
   */
  void Run();

 private:
  // Difficulty m_difficulty;        //These are not needed as they can be
  // passed directly to Game const std::string& m_mapFile;
  bool m_gameOver, m_buildPhase;
  uint32_t m_roundNum;
  int32_t m_frameInTick;
  Game m_gameLogic;
  std::vector<sf::Sprite> m_mapTileSprites;
  std::map<int, Button*> m_buttons;

  // For the build phase
  int32_t m_selX,
      m_selY;  // The selected tile on the map, -1, -1 means nothing selected

  // Private functions

  void PollEvents();

  void Draw();

  /**
   * @brief Draws the background and map to the window
   * Assumes that the window has been properly cleared
   */
  void Priv_DrawBCG();
};
