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
  GameState(Gui gui, sf::RenderWindow& window, Difficulty difficulty,
            const std::string& filename);

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
  void Run();

 private:
<<<<<<< HEAD
  // Difficulty m_difficulty;        //These are not needed as they can be
  // passed directly to Game const std::string& m_mapFile;
  bool m_gameOver, m_buildPhase;
  uint32_t m_roundNum;
  Game m_gameLogic;

  // Private functions
=======
  //Difficulty m_difficulty;        //These are not needed as they can be passed directly to Game
  //const std::string& m_mapFile;
  bool m_gameOver, m_buildPhase;
  uint32_t m_roundNum;
  Game m_gameLogic;
  
  //Private functions
>>>>>>> 0e5e64277aefb3b44b9048d1f8014db4b8ac09e6

  /**
   * @brief Used by Run to run an enemy phase
   * At the end of the phase it will change the value of m_buildPhase.
<<<<<<< HEAD
   * If the player looses during the round, it will change the value of
   * m_gameOver
=======
   * If the player looses during the round, it will change the value of m_gameOver
>>>>>>> 0e5e64277aefb3b44b9048d1f8014db4b8ac09e6
   */
  void Priv_RunEnemyPhase();

  /**
   * @brief Used by Run to run a building phase
   * At the end of the phase it will change the value of m_buildPhase.
   * If the player quits, it will change the value of m_gameOver
   */
  void Priv_RunBuildPhase();
<<<<<<< HEAD
};
=======

};
>>>>>>> 0e5e64277aefb3b44b9048d1f8014db4b8ac09e6
