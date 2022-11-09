#pragma once

#include <cstdint>
#include <string>

#include "renderable.hpp"

enum Enemy {
  Homework,
  Essay,
  Project,
  B_Thesis,
  M_Thesis,
  D_Thesis,
  BSc,
  MSc,
  DSc
};

/**
 * @brief Generic Enemy class, these just die when they are killed
 * 
 */
class Assignment : public Renderable
{
public:
  Assignment(uint32_t cr, uint32_t speed, const std::string& imageName)
    : Renderable(imageName), m_maxCr(cr), m_curCr(cr), m_speed(speed) { }
  ~Assignment();

  /**
   * @brief A function which can be called to advance the enemy forward
   * 
   * @param t The time which has elapsed since the last tick, in ms
   * @return The amound of pixels the enemy has advanced
   */
  uint32_t Advance(uint32_t t) const;

  /**
   * @brief Makes the enemy take damage
   * 
   * @param dmg The amount of damage taken
   * @return The amount of credits the player has gotten from attacking, non-zero amount means that the enemy died
   * */
  virtual uint32_t TakeDmg(uint32_t dmg){
    if(this->m_curCr > dmg){
      this->m_curCr -= dmg;
      return 0;
    } else {
      return this ->m_maxCr;
    }
  }

protected:
  uint32_t m_maxCr, m_curCr, m_speed;
};
