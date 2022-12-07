#include "gamestate.hpp"

#define ANIMATION_LENGTH 30  // 30 frames is 1/2 second

GameState::GameState(GUI& gui, sf::RenderWindow& window, Difficulty difficulty,
                     const std::string& filename)
    : State(gui, window),
      m_gameOver(false),
      m_buildPhase(true),
      m_roundNum(0),
      m_frameInTick(0),
      m_gameLogic(Game(30, 20, filename, difficulty)) {}

void GameState::Run() {
  //We check which phase is active
  if (m_buildPhase) {
    Priv_RunBuildPhase();
  } else {
    Priv_RunEnemyPhase();
  }
  //If the game is over, we change the state to endstate
  if (m_gameOver) {
    // change state to endstate
  }
}

void GameState::Priv_RunEnemyPhase() {
  //The game logic is advanced only once per second
  if(m_frameInTick == 0){
    // call tower turn
    m_gameLogic.TowerTurn();
    // call enemyturn and check if game is over
    if (!m_gameLogic.EnemyTurn()) {
      m_gameOver = true;
      return;
    }
  }
  //Draw everything
  
  //Background and towers

  //m_gameLogic.GetAttacks()


  while (/* window is open */) {
    // draw the attacks
    uint32_t i;
    for (i = 0; i < ANIMATION_LENGTH; i++) {
      // Maybe currently just a line from tower to enemy or something like that
    }
    // Check if the round has ended and continue to buildPhase
    if (m_gameLogic.RoundIsFinished()) {
      m_buildPhase = true;
      return;
    }
    // draw the movements
    for (i = 0; i < ANIMATION_LENGTH; i++) {
      // Enemies have a method MovedLastTick which can be used to determine
      // which ones have moved and must be animated somewhere between the last
      // grid cell and the current one. The other ones can be just draw to their
      // current location
    }
  }
}

void GameState::Priv_RunBuildPhase() {
  // TODO the build stage loop

  // Returns either by setting m_buildPhase to false or m_gameOver to true
  //At the end of build phase, get the next enemy phase ready
  m_roundNum = m_gameLogic.StartNextRound();
  m_frameInTick = 0;
}
