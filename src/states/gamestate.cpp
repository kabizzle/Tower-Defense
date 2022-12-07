#include "gamestate.hpp"

#define ANIMATION_LENGTH 30  // 30 frames is 1/2 second
#define TILE_SIZE 30

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
  while (m_window.pollEvent(m_event)) {
    if (m_event.type == sf::Event::Closed) m_window.close();
  }
  //The game logic is advanced only once per second
  if(m_frameInTick == 0){
    // call enemyturn and check if game is over
    if (!m_gameLogic.EnemyTurn()) {
      m_gameOver = true;
      return;
    }
    // call tower turn
    m_gameLogic.TowerTurn();
    if (m_gameLogic.RoundIsFinished()) {
      m_buildPhase = true;
      return;
    }
  }
  //Draw everything
  
  //Background and towers

  //Draw attacks? A sprite for these?
  //m_gameLogic.GetAttacks()

  //Enemies
  auto& enemyVec = m_gameLogic.GetEnemies();
  const auto& path = m_gameLogic.GetMap().GetPath();
  for(size_t i = 0; i < enemyVec.size(); i++){
    for(auto* e: enemyVec[i]) {
      //Check if the enemy has moved or if it is stationary now
      auto& coords = path[i];
      int32_t x = coords.first * TILE_SIZE, y = coords.second * TILE_SIZE;
      if(e->MovedLastTick()) {
        //Must be drawn between the last and current positions
        if(i == 0) {
          std::cerr << "Tried to animate enemies before start" << std::endl;
          continue;
        }
        //Previous coordinate
        auto& prev = path[i];
        int32_t xP = prev.first * TILE_SIZE, yP = prev.second * TILE_SIZE;
        //(1-t)*x_1 + t*x_2
        //x_1-t*x_1 + t*x_2    t = f/AL
        //x_1-f*x_1/Al + f*x_2/Al
        //x_1+f*(-x_1 + x_2)/Al
        x = xP + m_frameInTick * (x - xP) / ANIMATION_LENGTH;
        y = yP + m_frameInTick * (y - yP) / ANIMATION_LENGTH;
      }
      auto& sprite = e->GetSprite();
      sprite.setPosition(x, y);
      m_window.draw(sprite);
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
