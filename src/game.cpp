#include "game.hpp"

Game::Game(uint32_t mapWidth,
           uint32_t mapLength,
           const std::string& filename,
           Difficulty difficulty,
           uint32_t playerHealth)
    : m_map(Map(mapWidth, mapLength)),
    m_enemyFactory(difficulty),
    m_playerHealth(playerHealth) {
        m_map.InitializeMap(filename);
        // Create empty list for enemies for each path tile
        for (uint32_t i = 0; i < m_map.GetPath().size(); i++) {
            m_enemies.push_back(std::list<Assignment*>());
        }
 }

 bool Game::EnemyTurn() {
    // Start advancing enemies from the last path tile to avoid advancing moving enemies twice
    for (uint32_t i = m_enemies.size() - 1; i >= 0; i--) {
        for (auto enemyIt = m_enemies[i].begin(); enemyIt != m_enemies[i].end();) {
            Assignment *e = *enemyIt;
            if (e->Advance()) {
                // Remove moving enemy from the current tile and advance iterator
                enemyIt = m_enemies[i].erase(enemyIt);
                // If enemy moves from the last tile decrease player's health and check if the game ends
                if (i == m_enemies.size() - 1) {
                    m_playerHealth -= 1;
                    if (m_playerHealth == 0) {
                        return false;
                    }
                    delete e;
                } else {
                    // Move enemy to the next tile
                    m_enemies[i + 1].push_back(e);
                }
            } else {
                // Advance iterator if enemy didn't move
                enemyIt++;
            }
        }
    }

    // Add new enemies to the first path tile
    for (auto e : m_enemyFactory.NextTick()) {
        m_enemies.front().push_back(e);
    }

    return true;
 }

 void Game::TowerTurn() {
  //Reset the m_tickattacks collection
  m_tickAttacks.clear();
  // Supporting towers act first because they affect attacking towers
  for (auto t : m_supportingTowers){
    t->Act(m_attakingTowers);
  }
  //auto enemies = Priv_GetEnemyMap();  //Probably need references instead of copies here
  for (auto t : m_attakingTowers) {
    if(t->IsFunctional()){
      t->Attack(m_enemies, m_tickAttacks);   //Refactored to used the vector m_enemies directly
    }
  }
  // Remove and free dead enemies
  for (uint32_t i = 0; i < m_enemies.size(); i++) {
      for (auto enemyIt = m_enemies[i].begin(); enemyIt != m_enemies[i].end();) {
          Assignment *e = *enemyIt;
          if (!e->IsAlive()) {
              enemyIt = m_enemies[i].erase(enemyIt);
              delete e;
          } else {
              enemyIt++;
          }
      }
  }
 }

const std::list<std::pair<std::pair<int32_t, int32_t>,std::pair<int32_t, int32_t>>>& Game::GetAttacks() {
  return m_tickAttacks;
}

//Probably need references instead of copies here
 std::list<std::pair<std::pair<int32_t, int32_t>, Renderable*>> Game::GetEnemies() {
    std::list<std::pair<std::pair<int32_t, int32_t>, Renderable*>> enemies;
    for (uint32_t i = 0; i < m_enemies.size(); i++) {
        std::pair<int32_t, int32_t> coordinates = m_map.GetPath()[i];
        for (auto enemy : m_enemies[i]) {
            enemies.push_back(std::make_pair(coordinates, enemy));
        }
    }
    return enemies;
 }

//Probably need references instead of copies here
 std::map<std::pair<int32_t, int32_t>, std::list<Assignment*>> Game::Priv_GetEnemyMap() {
    std::map<std::pair<int32_t, int32_t>, std::list<Assignment*>> enemyMap;
    for (uint32_t i = 0; i < m_enemies.size(); i++) {
        enemyMap[m_map.GetPath()[i]] = m_enemies[i];
    }
    return enemyMap;
 }
