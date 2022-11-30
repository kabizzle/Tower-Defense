#pragma once

#include <cstdint>
#include <string>
#include <ostream>

#include "renderable.hpp"
#include "enemy_factory.hpp"

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
 * @param cr The "health" of the enemy, and also the amount of credits it rewards the player for killing it
 * @param timeToMove The inverse of speed for the enemy, basically the amount of game ticks it takes to advance
 * @param imageName The name of the image that should be used for this enemy, also the name of this enemy
 */
class Assignment : public Renderable
{
public:
  Assignment(uint32_t cr, uint32_t timeToMove, const std::string& imageName);

  virtual ~Assignment() { }

  /**
   * @brief A function which can be called to see if the enemy must be moved forward
   * @return True if the enemy moves to the next place
   */
  bool Advance();

  /**
   * @brief Tells whether this enemy is still alive or not
   */
  bool IsAlive() const;

  /**
   * @brief Tells the amount of health the enemy has left
   */
  uint32_t CrLeft() const;

  /**
   * @brief Get the amount of credits the enemy is worth
   */
  uint32_t GetCredits() const;

  /**
   * @brief Makes the enemy take damage
   * Splitting enemies hurt the attacking tower when they die
   * @param dmg The amount of damage taken
   * @param location A reference to the list of enemies at the location of this enemy. Used by Degree to spawn its descendants there
   * @return The amount of dmg the enemy causes the attacker to take
   * */
  virtual uint32_t TakeDmg(uint32_t dmg, std::list<Assignment*>& location);

  /**
   * @brief Overload for stream operator << for debugging 
   */
  friend std::ostream& operator<<(std::ostream& os, const Assignment& as);

protected:
  uint32_t m_maxCr, m_curCr, m_timeToMove, m_timeRemainder;
};
