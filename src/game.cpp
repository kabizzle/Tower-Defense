#include <algorithm>

#include "game.hpp"

Game::Game(uint32_t mapWidth,
           uint32_t mapLength,
           const std::string& filename,
           Difficulty difficulty)
    : m_map(Map(mapWidth, mapLength)),
    m_enemyFactory(difficulty),
    m_playerHealth(10000000 - difficulty * 20),
    m_money(100) // TODO: change to some meaningful value
{
        m_map.InitializeMap(filename);
        // Create empty list for enemies for each path tile
        for (uint32_t i = 0; i < m_map.GetPath().size(); i++) {
            m_enemies.push_back(std::list<Assignment*>());
        }
 }

 Game::~Game() {
  for(auto* at: m_attakingTowers) {
    delete at;
  }
  for(auto* st: m_supportingTowers) {
    delete st;
  }
  for(const auto& list: m_enemies) {
    for(auto* e: list) {
      delete e;
    }
  }
 }

 uint32_t Game::StartNextRound() {
  return m_enemyFactory.NextRoundInit();
 }

 bool Game::EnemyTurn() {
    // Start advancing enemies from the last path tile to avoid advancing moving enemies twice
    for (int32_t i = m_enemies.size() - 1; i >= 0; i--) {
        for (auto enemyIt = m_enemies[i].begin(); enemyIt != m_enemies[i].end();) {
            Assignment *e = *enemyIt;
            if (e->Advance()) {
                // Remove moving enemy from the current tile and advance iterator
                enemyIt = m_enemies[i].erase(enemyIt);
                // If enemy moves from the last tile decrease player's health and check if the game ends
                if (i == m_enemies.size() - 1) {
                    m_playerHealth -= 1;
                    delete e;
                    if (m_playerHealth == 0) {
                        return false;
                    }
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
  //auto enemies = Priv_GetEnemyMap();
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
              m_score += e->GetCredits(); // Score is currently just total money earned
              m_money += e->GetCredits();
              delete e;
          } else {
              enemyIt++;
          }
      }
  }
 }

bool Game::RoundIsFinished() {
  if(m_enemyFactory.EnemiesLeft()) {
    return false;
  } else {
    //Must check if there are enemies still present on the field
    for(const auto& eList: m_enemies){
      if(!eList.empty()){
        return false;
      }
    }
    return true;
  }
}

 std::list<std::pair<std::pair<int32_t, int32_t>, Assignment*>> Game::GetEnemies() {
    std::list<std::pair<std::pair<int32_t, int32_t>, Assignment*>> enemies;
    for (uint32_t i = 0; i < m_enemies.size(); i++) {
        std::pair<int32_t, int32_t> coordinates = m_map.GetPath()[i];
        for (auto enemy : m_enemies[i]) {
            enemies.push_back(std::make_pair(coordinates, enemy));
        }
    }
    return enemies;
 }

const std::list<std::pair<std::pair<int32_t, int32_t>,std::pair<int32_t, int32_t>>>& Game::GetAttacks() {
  return m_tickAttacks;
}

const Map& Game::GetMap() const { return m_map; }

bool Game::AddTower(Tower* t) {
  AttackingTower* at = dynamic_cast<AttackingTower*>(t);
  SupportTower* st = nullptr;
  if(at) {
    m_attakingTowers.push_back(at);
  } else {
    st = dynamic_cast<SupportTower*>(t);
    if(st) {
      m_supportingTowers.push_back(st);
    }
  }
  return (at || st);
}

bool Game::BuildAttackingTower(AttackingTower* t, uint32_t cost) {
  if (m_money < cost) return false;
  m_money -= cost;
  m_attakingTowers.push_back(t);
  return true;
}

bool Game::BuildSupportTower(SupportTower* t, uint32_t cost) {
  if (m_money < cost) return false;
  m_money -= cost;
  m_supportingTowers.push_back(t);
  return true;
}

bool Game::UpgradeTower(const std::pair<int32_t, int32_t>& coords) {
  auto tower = std::find_if(m_attakingTowers.begin(), m_attakingTowers.end(),
    [coords] (const AttackingTower* t) {return (*t).GetCoords() == coords;});
  // Check that the tower at given coordinates exists
  if (tower == m_attakingTowers.end()) return false;
  // Check that the tower can be upgraded
  if (!(*tower)->IsUpgradeable(m_money)) return false;
  // Upgrade the tower and subtract cost fo upgrade from player's money
  m_money -= (*tower)->Upgrade();
  return true;
}

const std::list<AttackingTower*>& Game::GetAttackingTowers() const { return m_attakingTowers; }

const std::list<SupportTower*>& Game::GetSupportTowers() const { return m_supportingTowers; }

std::ostream& operator<<(std::ostream& os, const Game& game) {
  os << "*** GAME INFO ***\n";
  os << "Player health: " << game.m_playerHealth << "\t\tScore: " << game.m_score << std::endl;
  //Go through the towers and print their info
  for(const auto* at: game.m_attakingTowers) {
    os << *at;
  }
  for(const auto* st: game.m_supportingTowers) {
    os << *st;
  }
  //Same for enemies
  for(size_t i = 0; i < game.m_enemies.size(); i++) {
    if(!game.m_enemies[i].empty()) {
      os << "At path index " << i << "\n";
    }
    for(const auto* e: game.m_enemies[i]) {
      os << *e;
    }
  }
  os << std::flush;
  return os;
}