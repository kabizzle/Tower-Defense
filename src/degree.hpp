#pragma once

#include <list>
#include <utility>

#include "assignment.hpp"
class EnemyFactory; //Forward declaration

/**
 * @brief A more advanced type of enemy
 * Splits into multiple other enemies upon death
 * The descendants are stored in the m_descendants collection as pairs where the first one is the type and the second one is the amount
 */
class Degree : public Assignment {
 public:
  /**
  * @brief Construct a new Degree object
  * @param cr The "health" of the enemy, and also the amount of credits it rewards the player for killing it
  * @param timeToMove The inverse of speed for the enemy, basically the amount of game ticks it takes to advance
  * @param name The name of this enemy
  * @param ef The enemyfactory used for creating this enemy. Is used to spawn the descendants when this dies
  * @param decendants The types and amounts of descendants
  */
  Degree(uint32_t cr, uint32_t timeToMove, const std::string& name, const sf::Sprite& sprite, const EnemyFactory& ef,
         const std::list<std::pair<Enemy, uint32_t>>& decendants);

  /**
   * @brief Default destructor
   */
  ~Degree() = default;

  /**
   * @brief Makes the enemy take damage
   * @param dmg Amount of damage the enemy takes
   * @param location A ref to the location of this enemy, spawns the descendants there
   * @return uint32_t The amount of damage the enemy gives the tower upon splitting (== m_maxCr / 4)
   */
  uint32_t TakeDmg(uint32_t dmg, std::list<Assignment*>& location);

 private:
  const std::list<std::pair<Enemy, uint32_t>> m_decendants;
  const EnemyFactory& m_ef;
};