#pragma once

//#include <cmath>

#include <list>
#include "tower.hpp"
#include "assignment.hpp"
#include "utils.hpp"

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
  AttackingTower(uint32_t power, uint32_t range, uint32_t health, std::pair<int32_t, int32_t> coords, const Map& map, const std::string& imageName);

  /**
   * @brief Performs an attack against one enemy
   * The tower goes through the possible targetable locations in m_inRange, starting from the one closest to end
   * and when it finds a living enemy in one of the locations, it attacks that.
   * After performing an attack, it clears the buffs
   * @param enemies A reference to the map of enemies in different coordinates
   */
  void Attack(std::map<std::pair<int32_t, int32_t>, std::list<Assignment*>>& enemies);

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

  //Static member functions to create some types of attacking towers
  static AttackingTower* Freshman(std::pair<int32_t, int32_t> coords, const Map& map);

private:
  uint32_t m_basePower, m_health, m_maxHealth;
  float m_buffs;
  std::vector<std::pair<int32_t, int32_t>> m_inRange;
};