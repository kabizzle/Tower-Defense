#pragma once

//#include <cmath>

#include "tower.hpp"
#include "assignment.hpp"

/**
 * @brief A class for the offensive towers
 * 
 */
class AttackingTower : public Tower
{
public:
  /**
   * @brief Construct a new Attacking Tower object
   * 
   * @param power The amount of damage this tower can do to an enemy
   * @param range The basic range
   * @param health The health of this tower
   * @param coords The coordinates of the tower
   * @param map A reference to the map used for the game, this is needed to know the enemy path and find attackable locations
   * @param imageName The name of the image representing this particular tower, also the name of the tower type
   */
  AttackingTower(uint32_t power, uint32_t range, uint32_t health, uint32_t upgCost,
                 const std::pair<int32_t, int32_t>& coords, const Map& map,
                 const std::string& imageName, const std::vector<sf::Sprite>& sprites);

  /**
   * @brief Performs an attack against one enemy NOTE: migrate to using this overload
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
   * The cost of upgrading 1 -> 2 is the base cost m_upgCost and 2 -> 3 is twice that.
   * Also checks that this tower is not already max level.
   */
  bool IsUpgradeable(uint32_t money) const;

  /**
   * @brief Tells the upgrade cost
   * @return uint32_t 
   */
  uint32_t GetUpgradeCost() const;

  /**
   * @brief Can be used to upgrade the tower to the next level. Assumes that tower is upgradeable.
   * @return Cost of the upgrade
   */
  uint32_t Upgrade();

  friend std::ostream& operator<<(std::ostream& os, const AttackingTower& at);


  //Static member functions to create some types of attacking towers
  static AttackingTower* Freshman(const std::pair<int32_t, int32_t>& coords, const Map& map);

  static AttackingTower* Teekkari(const std::pair<int32_t, int32_t>& coords, const Map& map);

  static AttackingTower* Bachelor(const std::pair<int32_t, int32_t>& coords, const Map& map);

  static AttackingTower* Master(const std::pair<int32_t, int32_t>& coords, const Map& map);

  static AttackingTower* Doctor(const std::pair<int32_t, int32_t>& coords, const Map& map);

private:
  uint32_t m_basePower, m_maxHealth, m_health, m_upgCost, m_level;
  float m_buffs;
  //std::vector<std::pair<int32_t, int32_t>> m_inRange;
  std::vector<uint32_t> m_inRangeInd;
  const Map& m_map;

  //Private functions

  void Priv_UpdateRange(uint32_t newRange);
};