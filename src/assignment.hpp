#pragma once

#include <cstdint>
#include <string>
#include <ostream>

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
  Assignment(uint32_t cr, uint32_t speed, const std::string& imageName);

  virtual ~Assignment() { }

  /**
   * @brief A function which can be called to advance the enemy forward
   * The object also keeps track of the remainder of time, since otherwise
   * it would never move if timeframes t are too small.
   * @param t The time which has elapsed since the last tick, in ms
   * @return The amound of pixels the enemy has advanced
   */
  uint32_t Advance(uint32_t t);

  /**
   * @brief Makes the enemy take damage
   * 
   * @param dmg The amount of damage taken
   * @return The amount of credits the player has gotten from attacking, non-zero amount means that the enemy died
   * */
  virtual uint32_t TakeDmg(uint32_t dmg);

  /**
   * @brief Overload for stream operator << for debugging 
   */
  friend std::ostream& operator<<(std::ostream& os, const Assignment& as);

protected:
  uint32_t m_maxCr, m_curCr, m_speed, m_timeRemainder;
};
