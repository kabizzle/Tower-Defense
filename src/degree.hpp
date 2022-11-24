#pragma once

#include <list>
#include <utility>

#include "assignment.hpp"
#include "enemy_factory.hpp"

/**
 * @brief A more advanced type of enemy, will split into multiple other enemies
 * upon death
 * The descendants are stored in the m_descendants collection as pairs where the first one is the type and the second one is the amount
 */
class Degree : public Assignment {
 public:
 /**
  * @brief Construct a new Degree object
  * 
  * @param cr 
  * @param timeToMove 
  * @param imageName 
  * @param ef The enemyfactory used for creating this enemy. Is used to spawn the descendants when this dies
  * @param decendants The types and amounts of descendants
  */
  Degree(uint32_t cr, uint32_t timeToMove, const std::string& imageName, const EnemyFactory& ef,
         const std::list<std::pair<Enemy, uint32_t>>& decendants);

  uint32_t TakeDmg(uint32_t dmg, std::list<Assignment*>& location) override;

 private:
  const std::list<std::pair<Enemy, uint32_t>> m_decendants;
  const EnemyFactory& m_ef;
};