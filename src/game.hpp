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

class Game {
 public:
  Game(uint32_t mapWidth, uint32_t mapLength, const std::string& filename,
       Difficulty difficulty);

  /**
   * @brief Destroy the Game object
   * In case of a game over / quit the enemies and towers present must be freed
   */
  ~Game();

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
   * If enemies died during the attacking, returns true
   * @return bool
   */
  bool TowerTurn();

  /**
   * @brief Used to check if the round is still ongoing. SHOULD be called only
   * AFTER StartNextRound()!
   */
  bool RoundIsFinished();

  // Method for getting enemies and their coordinates for GUI to draw
  std::vector<std::list<Assignment*>>& GetEnemies();

  /**
   * @brief Gives information about which attacks happened during the turn
   * @return const std::list<std::pair<std::pair<int32_t,
   * int32_t>,std::pair<int32_t, int32_t>>>&
   */
  const std::list<
      std::pair<std::pair<int32_t, int32_t>, std::pair<int32_t, int32_t>>>&
  GetAttacks();

  /**
   * @brief Gets a const ref version of the map used, to get for example the
   * path
   *
   * @return const Map&
   */
  const Map& GetMap() const;

  /**
   * @brief For adding a tower to the Game. NOTE: not ideal implementation, just
   * for the text-based test
   *
   * @param t A pointer to the dynamically allocated tower
   * Will fail if the Tower is not an instance of Attacking or supporting Tower
   * @return bool Whether the adding was successfull
   */
  bool AddTower(Tower* t);

  /**
   * @brief For building attacking tower. Assumes that tower is at suitable
   * location. MAYBE NOT NEEDED
   * @param t tower to build
   * @param cost cost of building tower NOTE: should probably be included in
   * Tower class
   * @return if building tower was successful
   */
  bool BuildAttackingTower(AttackingTower* t, uint32_t cost);

  /**
   * @brief For building support tower. Assumes that tower is at suitable
   * location. MAYBE NOT NEEDED
   * @param t tower to build
   * @param cost cost of building tower NOTE: should probably be included in
   * Tower class
   * @return if building tower was successful
   */
  bool BuildSupportTower(SupportTower* t, uint32_t cost);

  /**
   * @brief Upgrade tower. Checks if the tower exist and can be upgraded.
   * MAYBE NOT NEEDED
   * @param coords coordinates where tower is
   * @return if upgrade was successful
   */
  //bool UpgradeTower(const std::pair<int32_t, int32_t>& coords);

  /**
   * @brief Used by GUI states to check what can be done
   * NOTE: TODO make this check the price
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

  uint32_t GetScore() const;

  uint32_t GetMoney() const;

  uint32_t GetHealth() const;

  /**
   * @brief Overload for the stream output operator
   */
  friend std::ostream& operator<<(std::ostream& os, const Game& game);

 private:
  uint32_t m_playerHealth;
  uint32_t m_score;
  uint32_t m_money;
  Map m_map;
  EnemyFactory m_enemyFactory;
  std::list<AttackingTower*> m_attakingTowers;
  std::list<SupportTower*> m_supportingTowers;

  /*  Enemies are strored in lists which are stored in vector
      where indices corresponds to indices of Map::GetPath
  */
  std::vector<std::list<Assignment*>> m_enemies;

  /**
   * @brief Stores the attack performed during towerturn so that they can be
   * rendered They are stored as pairs of coordinate pairs, in the order "from,
   * to"
   */
  std::list<std::pair<std::pair<int32_t, int32_t>, std::pair<int32_t, int32_t>>>
      m_tickAttacks;
};