#pragma once

#include <list>
#include <map>
#include <vector>

#include "assignment.hpp"
#include "attacking_tower.hpp"
#include "enemy_factory.hpp"
#include "map.hpp"
#include "support_towers.hpp"

class Game
{
public:
    Game(uint32_t mapWidth,
         uint32_t mapLength,
         const std::string& filename,
         Difficulty difficulty,
         uint32_t playerHealth);

    bool EnemyTurn();

    void TowerTurn();

    // Method for getting enemies and their coordinates for GUI to draw
    std::list<std::pair<std::pair<int32_t, int32_t>, Renderable*>> GetEnemies();

private:
    uint32_t m_playerHealth;
    uint32_t m_score;
    Map m_map;
    EnemyFactory m_enemyFactory;
    std::list<AttackingTower*> m_attakingTowers;
    std::list<SupportTower*> m_supportingTowers;

    /*  Enemies are strored in lists which are stored in vector
        where indices corresponds to indices of Map::GetPath
    */
    std::vector<std::list<Assignment*>> m_enemies;

    // Method for getting enemies and their coordinates for towers to attack
    std::map<std::pair<int32_t, int32_t>, std::list<Assignment*>> Priv_GetEnemyMap();
};