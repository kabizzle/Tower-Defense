#pragma once

#include <list>
#include <vector>

#include "assignment.hpp"
#include "enemy_factory.hpp"
#include "map.hpp"
#include "attacking_tower.hpp"

class Game
{
public:
    Game(uint32_t mapWidth,
         uint32_t mapLength,
         const std::string& filename,
         Difficulty difficulty,
         uint32_t playerHealth);

    void EnemyTurn();

    void TowerTurn();

    // Method for getting enemies and their coordinates for GUI to draw
    std::list<std::pair<std::pair<int32_t, int32_t>, Renderable*>> GetEnemies();

private:
    uint32_t m_playerHealth;
    Map m_map;
    EnemyFactory m_enemyFactory;
    std::list<AttackingTower*> m_attakingTowers;
    //std::list<Tower*> m_supportingTowers;

    /*  Enemies are strored in lists which are stored in vector
        where indices corresponds to indices of Map::GetPath
    */
    std::vector<std::list<Assignment*>> m_enemies;
};