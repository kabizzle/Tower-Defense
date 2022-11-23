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

 void Game::EnemyTurn() {
    // Add new enemies to the first path tile
    m_enemyFactory.NextRoundInit();               //!!!Not for every turn -Juho
    for (auto e : m_enemyFactory.NextTick()) {
        m_enemies.front().push_back(e);
    }

    // Start advancing enemies from the last path tile to avoid advancing moving enemies twice
    for (auto it = m_enemies.rbegin(); it != m_enemies.rend(); it++) {
        for (auto e : *it) {
            /*  TODO:
                Check with Assignment::Advance if the enemy moves
                If it moves, move it to the next list in m_enemies
                If it is in the last list, free it and decrease m_playerHealth
            */
        }
    }
 }

 void Game::TowerTurn() {
    // Supporting towers act first because they affect attacking towers
    /*
    for (auto t : m_supportingTowers){
        t->Act();
    }
    */
    for (auto t : m_attakingTowers) {
        //t->Attack();
    }
    /*  TODO:
        Remove and free enemies that have died
    */
 }

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