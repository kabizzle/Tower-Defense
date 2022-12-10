#include "game.hpp"

#include <algorithm>

#include "tower.hpp"

Game::Game(uint32_t mapWidth, uint32_t mapLength, const std::string& filename,
           Difficulty difficulty)
    : m_playerHealth(100 - difficulty * 20),
      m_score(0),
      m_money(50),
      m_map(Map(mapWidth, mapLength)),
      m_enemyFactory(difficulty) {
  m_map.InitializeMap(filename);
  // Create empty list for enemies for each path tile
  for (uint32_t i = 0; i < m_map.GetPath().size(); i++) {
    m_enemies.push_back(std::list<Assignment*>());
  }
}

Game::~Game() {
  for (auto* at : m_attakingTowers) {
    delete at;
  }
  for (auto* st : m_supportingTowers) {
    delete st;
  }
  for (const auto& list : m_enemies) {
    for (auto* e : list) {
      delete e;
    }
  }
}

uint32_t Game::StartNextRound() { return m_enemyFactory.NextRoundInit(); }

bool Game::EnemyTurn() {
  // Start advancing enemies from the last path tile to avoid advancing moving
  // enemies twice
  for (int32_t i = m_enemies.size() - 1; i >= 0; i--) {
    for (auto enemyIt = m_enemies[i].begin(); enemyIt != m_enemies[i].end();) {
      Assignment* e = *enemyIt;
      if (e->Advance()) {
        // Remove moving enemy from the current tile and advance iterator
        enemyIt = m_enemies[i].erase(enemyIt);
        // If enemy moves from the last tile decrease player's health and check
        // if the game ends
        if (i == static_cast<int32_t>(m_enemies.size() - 1)) {
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

bool Game::TowerTurn() {
  // Reset the m_tickattacks collection
  m_tickAttacks.clear();
  // Supporting towers act first because they affect attacking towers
  for (auto t : m_supportingTowers) {
    t->Act(m_attakingTowers);
  }
  // auto enemies = Priv_GetEnemyMap();
  for (auto t : m_attakingTowers) {
    if (t->IsFunctional()) {
      t->Attack(
          m_enemies,
          m_tickAttacks);  // Refactored to used the vector m_enemies directly
    }
  }
  // Remove and free dead enemies
  bool enemiesDied = false;
  for (uint32_t i = 0; i < m_enemies.size(); i++) {
    for (auto enemyIt = m_enemies[i].begin(); enemyIt != m_enemies[i].end();) {
      Assignment* e = *enemyIt;
      if (!e->IsAlive()) {
        enemyIt = m_enemies[i].erase(enemyIt);
        m_score +=
            e->GetCredits();  // Score is currently just total money earned
        m_money += e->GetCredits();
        enemiesDied = true;
        delete e;
      } else {
        enemyIt++;
      }
    }
  }
  return enemiesDied;
}

bool Game::RoundIsFinished() {
  if (m_enemyFactory.EnemiesLeft()) {
    return false;
  } else {
    // Must check if there are enemies still present on the field
    for (const auto& eList : m_enemies) {
      if (!eList.empty()) {
        return false;
      }
    }
    return true;
  }
}

std::vector<std::list<Assignment*>>& Game::GetEnemies() { return m_enemies; }

const std::list<
    std::pair<std::pair<int32_t, int32_t>, std::pair<int32_t, int32_t>>>&
Game::GetAttacks() const {
  return m_tickAttacks;
}

const Map& Game::GetMap() const { return m_map; }

bool Game::AddTower(Tower* t) {
  AttackingTower* at = dynamic_cast<AttackingTower*>(t);
  SupportTower* st = nullptr;
  if (at) {
    m_attakingTowers.push_back(at);
  } else {
    st = dynamic_cast<SupportTower*>(t);
    if (st) {
      m_supportingTowers.push_back(st);
    }
  }
  return (at || st);
}

bool Game::IsActionPossible(const std::pair<int32_t, int32_t>& coords,
                            Action a) const {
  // Check if coordinate is positive
  if (coords.first < 0 || coords.second < 0) {
    return false;
  }

  TileType tile = m_map.GetPos(coords);
  // Actions are only possible on towerTiles
  if (tile != TileType::towerTile) {
    return false;
  }
  // Check if there is a tower at the location
  Tower* tower = nullptr;
  for (auto* at : m_attakingTowers) {
    if (at->GetCoords() == coords) {
      tower = at;
      break;
    }
  }
  for (auto* st : m_supportingTowers) {
    if (tower) {
      break;
    } else if (st->GetCoords() == coords) {
      tower = st;
    }
  }
  // Check the action and determine the outcome
  switch (a) {
    case Action::UpgradeTower:
      // There must be a tower and it must be upgradeable with the amount of
      // money
      return (tower && tower->IsUpgradeable(m_money));
      break;
    case Action::DestroyTower:
      // There must be a tower
      return (tower != nullptr);
      break;
    default:
      // The action is about buying, so we must check if the cell is free and if
      // we have enough money
      try {
        return !(tower) &&
               Tower::towerPrices.at(static_cast<TowerType>(a)) <= m_money;
      } catch (...) {
        std::cerr << "In \"Game::IsActionPossible()\" was not able to "
                     "determine the cost of a tower"
                  << std::endl;
        return false;
      }
      break;
  }
}

void Game::CreateTower(const std::pair<int32_t, int32_t>& coords, TowerType t) {
  if (!IsActionPossible(coords, static_cast<Action>(t))) {
    std::cerr << "Tower creation is not possible" << std::endl;
    return;
  }
  switch (t) {
    case Freshman:
      m_attakingTowers.emplace_back(AttackingTower::Freshman(coords, m_map));
      break;
    case Teekkari:
      m_attakingTowers.emplace_back(AttackingTower::Teekkari(coords, m_map));
      break;
    case Bachelor:
      m_attakingTowers.emplace_back(AttackingTower::Bachelor(coords, m_map));
      break;
    case Master:
      m_attakingTowers.emplace_back(AttackingTower::Master(coords, m_map));
      break;
    case Doctor:
      m_attakingTowers.emplace_back(AttackingTower::Doctor(coords, m_map));
      break;
    case Calculator:
      m_supportingTowers.emplace_back(SupportTower::Calculator(coords));
      break;
    case CoffeeTable:
      m_supportingTowers.emplace_back(SupportTower::CoffeeTable(coords));
      break;
    default:
      std::cerr << "Invalid tower type" << std::endl;
      break;
  }
  // Substrack money
  try {
    m_money -= Tower::towerPrices.at(t);
  } catch (...) {
    std::cerr << "Wasn't able to determine the cost of a tower" << std::endl;
  }
}

void Game::UpgradeTower(const std::pair<int32_t, int32_t>& coords) {
  if (!IsActionPossible(coords, Action::UpgradeTower)) {
    std::cerr << "Tower upgrading is not possible" << std::endl;
    return;
  }
  // If upgrading is possible, it has to be AttackingTower
  AttackingTower* tower = *std::find_if(
      m_attakingTowers.begin(), m_attakingTowers.end(),
      [coords](const AttackingTower* t) { return (*t).GetCoords() == coords; });
  // Upgrade the tower and subtract cost fo upgrade from player's money
  m_money -= tower->Upgrade();
}

void Game::DestroyTower(const std::pair<int32_t, int32_t>& coords) {
  if (!IsActionPossible(coords, Action::DestroyTower)) {
    std::cerr << "Tower destroying is not possible" << std::endl;
    return;
  }
  // Search tower first from attacking towers
  auto attackingTowerIt = std::find_if(
      m_attakingTowers.begin(), m_attakingTowers.end(),
      [coords](const AttackingTower* t) { return (*t).GetCoords() == coords; });
  // Check if the tower was found
  if (attackingTowerIt != m_attakingTowers.end()) {
    // Remove and free the tower
    AttackingTower* t = *attackingTowerIt;
    m_attakingTowers.erase(attackingTowerIt);
    delete t;
    return;
  }
  // If not attacking tower, it has to be support tower
  auto supportTowerIt = std::find_if(
      m_supportingTowers.begin(), m_supportingTowers.end(),
      [coords](const SupportTower* t) { return (*t).GetCoords() == coords; });
  SupportTower* t = *supportTowerIt;
  m_supportingTowers.erase(supportTowerIt);
  delete t;
}

const std::list<AttackingTower*>& Game::GetAttackingTowers() const {
  return m_attakingTowers;
}

const std::list<SupportTower*>& Game::GetSupportTowers() const {
  return m_supportingTowers;
}

const Tower* Game::GetTower(const std::pair<int32_t, int32_t>& coords) const {
  auto it = m_attakingTowers.begin();
  it = std::find_if(it, m_attakingTowers.end(), [&coords](AttackingTower* at) {
    return at->GetCoords() == coords;
  });
  if (it != m_attakingTowers.end()) {
    return *it;
  }
  auto it2 = m_supportingTowers.begin();
  it2 = std::find_if(
      it2, m_supportingTowers.end(),
      [&coords](SupportTower* st) { return st->GetCoords() == coords; });
  if (it2 != m_supportingTowers.end()) {
    return *it2;
  } else {
    return nullptr;
  }
}

uint32_t Game::GetScore() const {
  return 100 * m_score / m_map.GetPath().size();
}

uint32_t Game::GetMoney() const { return m_money; }

uint32_t Game::GetHealth() const { return m_playerHealth; }

Difficulty Game::GetDifficulty() const {
  return m_enemyFactory.GetDifficulty();
}

std::ostream& operator<<(std::ostream& os, const Game& game) {
  os << "*** GAME INFO ***\n";
  os << "Player health: " << game.m_playerHealth
     << "\t\tScore: " << game.m_score << std::endl;
  // Go through the towers and print their info
  for (const auto* at : game.m_attakingTowers) {
    os << *at;
  }
  for (const auto* st : game.m_supportingTowers) {
    os << *st;
  }
  // Same for enemies
  for (size_t i = 0; i < game.m_enemies.size(); i++) {
    if (!game.m_enemies[i].empty()) {
      os << "At path index " << i << "\n";
    }
    for (const auto* e : game.m_enemies[i]) {
      os << *e;
    }
  }
  os << std::flush;
  return os;
}