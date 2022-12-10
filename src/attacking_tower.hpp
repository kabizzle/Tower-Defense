#pragma once

#include "tower.hpp"
#include "assignment.hpp"

/**
 * @brief A class for the offensive towers 
 */
class AttackingTower : public Tower
{
public:
  /**
   * @brief Construct a new Attacking Tower object
   * @param power The amount of damage this tower can do to an enemy
   * @param range The basic range
   * @param health The health of this tower
   * @param upgCost The cost of upgrading this tower
   * @param coords The coordinates of the tower
   * @param map A reference to the map used for the game, this is needed to know the enemy path and find attackable locations
   * @param name The name of the tower
   * @param sprites A collection of the sprites of different levels of this tower
   */
  AttackingTower(uint32_t power, uint32_t range, uint32_t health, uint32_t upgCost,
                 const std::pair<int32_t, int32_t>& coords, const Map& map,
                 const std::string& name, const std::vector<sf::Sprite>& sprites);

  /**
   * @brief Default destructor
   */
  ~AttackingTower() = default;

  /**
   * @brief Performs an attack against one enemy
   * The tower goes through the possible targetable locations in m_inRangeInd, starting from the one closest to end
   * and when it finds a living enemy in one of the locations, it attacks that.
   * After performing an attack, it clears the buffs
   * It also adds the attacks which it performs to a collection given as a reference
   * @param enemies A reference to the map of enemies in different coordinates
   * @param attackCollection A reference to the collection where the attacks happening during the round are stored
   */
  void Attack(std::vector<std::list<Assignment*>>& enemies,
              std::list<std::pair<std::pair<int32_t, int32_t>,std::pair<int32_t, int32_t>>>& attackCollection);

  /**
   * @brief Used by the buffing towers to apply a buff
   * In case multiple buffing towers buff a single tower, the buffs stack additively, not multiplicatively
   * @param b The buff amount as a decimal number (e.g. 20% buff is 0.2f)
   */
  void ApplyBuff(float b);

  /**
   * @brief Tells whether the tower is functional or destroyed
   * @return bool
   */
  bool IsFunctional() const;

  /**
   * @brief Used by the healing towers to heal other towers
   * Will not heal over the maximum health
   * @param h The heal amount
   */
  void Heal(uint32_t h);

  /**
   * @brief Tells whether or not this tower can be upgraded with the corrent amount of money
   * Also checks that this tower is not already max level.
   * @return bool
   */
  bool IsUpgradeable(uint32_t money) const;

  /**
   * @brief Tells the upgrade cost
   * @return uint32_t 
   */
  uint32_t GetUpgradeCost() const;

  /**
   * @brief Can be used to upgrade the tower to the next level. Assumes that tower is upgradeable.
   * @return uint32_t The cost of the upgrade
   */
  uint32_t Upgrade();

  /**
   * @brief Overload for the stream output operator
   */
  friend std::ostream& operator<<(std::ostream& os, const AttackingTower& at);


  /**
   * @brief Static function to create a specific tower
   * @param coords Where the tower is placed
   * @param map A const ref to the map the tower is placed on
   * @return AttackingTower* 
   */
  static AttackingTower* Freshman(const std::pair<int32_t, int32_t>& coords, const Map& map);

  /**
   * @brief Static function to create a specific tower
   * @param coords Where the tower is placed
   * @param map A const ref to the map the tower is placed on
   * @return AttackingTower* 
   */
  static AttackingTower* Teekkari(const std::pair<int32_t, int32_t>& coords, const Map& map);

  /**
   * @brief Static function to create a specific tower
   * @param coords Where the tower is placed
   * @param map A const ref to the map the tower is placed on
   * @return AttackingTower* 
   */
  static AttackingTower* Bachelor(const std::pair<int32_t, int32_t>& coords, const Map& map);

  /**
   * @brief Static function to create a specific tower
   * @param coords Where the tower is placed
   * @param map A const ref to the map the tower is placed on
   * @return AttackingTower* 
   */
  static AttackingTower* Master(const std::pair<int32_t, int32_t>& coords, const Map& map);

  /**
   * @brief Static function to create a specific tower
   * @param coords Where the tower is placed
   * @param map A const ref to the map the tower is placed on
   * @return AttackingTower* 
   */
  static AttackingTower* Doctor(const std::pair<int32_t, int32_t>& coords, const Map& map);

private:
  uint32_t m_basePower, m_maxHealth, m_health, m_upgCost, m_level;
  float m_buffs;
  std::vector<uint32_t> m_inRangeInd;   //The indices in the enemy path where the tower can shoot to
  const Map& m_map;

  //Private functions

  /**
   * @brief Private. Used to update the m_inRangeInd
   * @param newRange The new range of the tower
   */
  void Priv_UpdateRange(uint32_t newRange);
};