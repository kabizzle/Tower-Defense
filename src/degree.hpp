#pragma once

#include <list>
#include <utility>

#include "assignment.hpp"

/**
 * @brief A more advanced type of enemy, will split into multiple other enemies
 * upon death
 *
 */
class Degree : public Assignment {
 public:
  Degree(uint32_t cr, uint32_t speed, const std::string& imageName,
         const std::list<std::pair<Enemy, uint32_t>>& decendants)
      : Assignment(cr, speed, imageName), m_decendants(decendants) {}
  ~Degree();

  uint32_t TakeDmg(uint32_t dmg) {
    if (this->m_curCr > dmg) {
      this->m_curCr -= dmg;
      return 0;
    } else {
      /**
       * @brief TODO must also return the descendants to Map somehow OR make Map
       * spawn them
       *
       */
      return this->m_maxCr;
    }
  }

 private:
  const std::list<std::pair<Enemy, uint32_t>> m_decendants;
};