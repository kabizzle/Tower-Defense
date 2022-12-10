#pragma once

#include <list>
#include <map>
#include <vector>

#include "assignment.hpp"
#include "attacking_tower.hpp"
#include "enemy_factory.hpp"
#include "map.hpp"
#include "support_towers.hpp"

/**
 * @brief An enumeration for different actions on grid cells
 * Used to test the possibility of actions
 */
enum Action {
  BuyFreshman,
  BuyTeekkari,
  BuyBachelor,
  BuyMaster,
  BuyDoctor,
  BuyCalculator,
  BuyCoffeeTable,
  UpgradeTower,
  DestroyTower
};

/**
 * @brief A class which holds the logic of the game
 */
class Game {
public:
  /**
   * @brief Construct a new Game object
   * @param mapWidth The width of the map (should be 30)
   * @param mapHeigth The height of the map (should be 20)
   * @param filename The file where the map's text representation is
   * @param difficulty The difficulty for the game
   */
  Game(uint32_t mapWidth, uint32_t mapHeigth, const std::string& filename,
       Difficulty difficulty);

  /**
   * @brief Destroy the Game object
   * In case of a game over / quit the enemies and towers present must be freed
   */
  ~Game();

  /**
   * @brief Delete copy constructor
   */
  Game(const Game& other) = delete;
  
  /**
   * @brief Delete assignment operator
   */
  Game& operator=(const Game& other) = delete;

  /**
   * @brief Used to start the next round
   * Calls the enemyfactory to initialize its own state such that the round can
   * start
   * @return uint32_t The number of the round starting
   */
  uint32_t StartNextRound();

  /**
   * @brief Advances the enemies
   * @return true: No game over
   * @return false: Game over
   */
  bool EnemyTurn();

  /**
   * @brief Makes the towers attack the enemies
   * If enemies died during the attacking, returns true (for sound effects)
   * @return bool
   */
  bool TowerTurn();

  /**
   * @brief Used to check if the round is still ongoing.
   * SHOULD be called only AFTER StartNextRound()!
   * @return bool
   */
  bool RoundIsFinished();

  /**
   * @brief Get the Enemies in the game now
   * Method for getting enemies and their coordinates for GUI to draw
   * @return std::vector<std::list<Assignment*>>& 
   */
  std::vector<std::list<Assignment*>>& GetEnemies();

  /**
   * @brief Gives information about which attacks happened during the turn
   * @return const std::list<std::pair<std::pair<int32_t,
   * int32_t>,std::pair<int32_t, int32_t>>>&
   */
  const std::list<
      std::pair<std::pair<int32_t, int32_t>, std::pair<int32_t, int32_t>>>&
  GetAttacks() const;

  /**
   * @brief Gets a const ref version of the map used
   * @return const Map&
   */
  const Map& GetMap() const;

  /**
   * @brief For adding a tower to the Game.
   * Only for the text_based_test.cpp
   * @param t A pointer to the dynamically allocated tower
   * Will fail if the Tower is not an instance of Attacking or supporting Tower
   * @return bool Whether the adding was successfull
   */
  bool AddTower(Tower* t);

  /**
   * @brief Used by GUI states to check what can be done
   * @param coords The grid coordinates
   * @param a Enumeration telling the desired action
   * @return bool
   */
  bool IsActionPossible(const std::pair<int32_t, int32_t>& coords,
                        Action a) const;

  /**
   * @brief Create a Tower object in the game
   * Uses the coordinates and enumeration to place a tower on the playing field
   * Reduces the players money
   * @param coords The position where the tower needs to be created
   * @param t An enumeration of the desired tower to build
   */
  void CreateTower(const std::pair<int32_t, int32_t>& coords, TowerType t);

  /**
   * @brief Upgrades tower and reduces player's money.
   *
   * @param coords position of tower to upgrade
   */
  void UpgradeTower(const std::pair<int32_t, int32_t>& coords);

  /**
   * @brief Destroys tower.
   *
   * @param coords position of tower to destroy
   */
  void DestroyTower(const std::pair<int32_t, int32_t>& coords);

  /**
   * @brief Get a ref to the Attacking Towers for drawing them
   *
   * @return const std::list<AttackingTower*>&
   */
  const std::list<AttackingTower*>& GetAttackingTowers() const;

  /**
   * @brief Get a ref to the Support Towers for drawing them
   *
   * @return const std::list<SupportTower*>&
   */
  const std::list<SupportTower*>& GetSupportTowers() const;

  /**
   * @brief Get a pointer to Tower in a cell
   * The function will return nullptr if no tower is at the desired location
   * @param coords The xy-coordinates where we want to look
   * @return const Tower*
   */
  const Tower* GetTower(const std::pair<int32_t, int32_t>& coords) const;

  /**
   * @brief Calculates player's score.
   * Total money earned is multiplied by 100
   * and then divided by the length of the path. When the path is shorter
   * there is shorter time to defeat enemies so player get more points.
   * 
   * @return uint32_t player's score
   */
  uint32_t GetScore() const;

  /**
   * @brief Tells the player's current money
   * @return uint32_t 
   */
  uint32_t GetMoney() const;

  /**
   * @brief Tells the player's current health
   * @return uint32_t 
   */
  uint32_t GetHealth() const;

  /**
   * @brief Tells the difficulty of the current game
   * @return Difficulty 
   */
  Difficulty GetDifficulty() const;

  /**
   * @brief Overload for the stream output operator
   */
  friend std::ostream& operator<<(std::ostream& os, const Game& game);

 private:
  uint32_t m_playerHealth;
  uint32_t m_score; // Stores total money earned
  uint32_t m_money;
  Map m_map;
  EnemyFactory m_enemyFactory;
  std::list<AttackingTower*> m_attakingTowers;
  std::list<SupportTower*> m_supportingTowers;

  /*  Enemies are strored in lists which are stored in vector
      where indices corresponds to indices of Map::GetPath */
  std::vector<std::list<Assignment*>> m_enemies;

  /*
   Stores the attack performed during towerturn so that they can be
   rendered They are stored as pairs of coordinate pairs, in the order "from,
   to" */
  std::list<std::pair<std::pair<int32_t, int32_t>, std::pair<int32_t, int32_t>>>
      m_tickAttacks;
};