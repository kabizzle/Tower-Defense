/**
 * @file text_based_test.cpp
 * @brief Used to test the game running with text output to terminal
 */

#include <iostream>
#include <string>

#include "../src/game.hpp"

int main(void) {
  Game* g;
  try {
    g = new Game(30, 20, "maps/map1.txt", Difficulty::Easy);
  } catch (const std::exception& e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
    return 1;
  }
  char grid[20][30];

  std::pair<int32_t, int32_t> p(17, 5);
  bool t1 = g->AddTower(AttackingTower::Freshman(p, g->GetMap()));
  if (!t1) {
    std::cerr << "Could not add a tower" << std::endl;
  }

  uint32_t round = g->StartNextRound();

  while (true) {
    for (const auto& [coords, tile] : g->GetMap().GetGrid()) {
      char c;
      // enum tileType { towerTile, startTile, pathTile, endTile }
      switch (tile) {
        case TileType::towerTile:
          c = '#';
          break;
        case TileType::startTile:
          c = 'S';
          break;
        case TileType::endTile:
          c = 'F';
          break;
        case TileType::pathTile:
          c = ' ';
          break;
        default:
          c = 'X';
          break;
      }
      grid[coords.second][coords.first] = c;
    }
    //Path
    auto& path = g->GetMap().GetPath();
    // Place the enemies and towers
    auto& enemies = g->GetEnemies();
    for (size_t i = 0; i < path.size(); i++) {
      const auto& coords = path[i];
      if (enemies[i].size() > 1) {
        grid[coords.second][coords.first] = 'E';  // Many enemies
      } else if (enemies[i].size() == 1) {
        grid[coords.second][coords.first] = 'e';
      }
    }
    for (const auto* at : g->GetAttackingTowers()) {
      grid[at->GetCoords().second][at->GetCoords().first] = 'a';
    }
    for (const auto* st : g->GetSupportTowers()) {
      grid[st->GetCoords().second][st->GetCoords().first] = 's';
    }

    // Print game info out
    std::cout << *g;
    std::cout << round << std::endl;

    // print the map out
    for (uint32_t r = 0; r < 20; r++) {
      for (uint32_t c = 0; c < 30; c++) {
        std::cout << grid[r][c];
      }
      std::cout << "\n";
    }
    std::cout << std::flush;

    // Input
    // std::cin >> line;
    if (std::cin.get() != '\n') {
      break;
    }
    g->EnemyTurn();
    g->TowerTurn();
    if (g->RoundIsFinished()) {
      round = g->StartNextRound();
    }
  }

  if (g) {
    delete g;
  }
  return 0;
}

// g++ -std=c++17 -o texttest ../tests/text_based_test.cpp game.cpp enemy_factory.cpp map.cpp assignment.cpp attacking_tower.cpp degree.cpp renderable.cpp tower.cpp support_towers.cpp utils.cpp