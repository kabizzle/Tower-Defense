#include "gamestate.hpp"

#define ANIMATION_LENGTH 30   //30 frames is 1/2 second

GameState::GameState(Gui gui, sf::RenderWindow& window, Difficulty difficulty, const std::string& filename)
  : State(gui, window), m_gameOver(false), m_buildPhase(true), m_roundNum(0), m_gameLogic(Game(30, 20, filename, difficulty)) { }

void GameState::Run() {
  while (/* window is open && !gameOver */)
  {
    if(m_buildPhase){
      Priv_RunBuildPhase();
    } else {
      Priv_RunEnemyPhase();
    }
  }
  //We exit the loop either because of game over or the window is closed
  if(/* window is open */){
    //change state to endstate
  }
}

void GameState::Priv_RunEnemyPhase() {
  m_roundNum = m_gameLogic.StartNextRound();
  while (/* window is open */)GIT  {
    //call tower turn
    m_gameLogic.TowerTurn();
    //draw the attacks
    uint32_t i;
    for(i = 0; i < ANIMATION_LENGTH; i++) {
      //Maybe currently just a line from tower to enemy or something like that
    }
    //call enemyturn and check if game is over
    if(!m_gameLogic.EnemyTurn()) {
      m_gameOver = true;
      return;
    }
    //Check if the round has ended and continue to buildPhase
    if(m_gameLogic.RoundIsFinished()) {
      m_buildPhase = true;
      return;
    }
    //draw the movements
    for(i = 0; i < ANIMATION_LENGTH; i++){
      //Enemies have a method MovedLastTick which can be used to determine which ones have moved and must be animated
      //somewhere between the last grid cell and the current one. The other ones can be just draw to their current location
    }
  }
}

void GameState::Priv_RunBuildPhase() {
  //TODO the build stage loop



  //Returns either by setting m_buildPhase to false or m_gameOver to true
}