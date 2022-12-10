#pragma once

#include <cstdint>
#include <string>
#include <ostream>
#include <list>

#include "renderable.hpp"

/**
 * @brief An enumeration for the different enemy types
 */
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
 */
class Assignment : public Renderable
{
public:
  /**
   * @brief Construct a new Assignment object
   * @param cr The "health" of the enemy, and also the amount of credits it rewards the player for killing it
   * @param timeToMove The inverse of speed for the enemy, basically the amount of game ticks it takes to advance
   * @param name The name of this enemy
   * @param sprite The sprite used for this enemy
   */
  Assignment(uint32_t cr, uint32_t timeToMove, const std::string& name, const sf::Sprite& sprite);

  /**
   * @brief A virtual destructor
   */
  virtual ~Assignment() = default;

  /**
   * @brief Tells if the enemy must be moved forward
   * Returns true if the enemy moves to the next place
   * @return bool
   */
  bool Advance();

  /**
   * @brief Tells if the enemy moved during the last tick
   * For animation purposes
   * @return bool
   */
  bool MovedLastTick() const;

  /**
   * @brief Tells whether this enemy is still alive or not
   * @return bool
   */
  bool IsAlive() const;

  /**
   * @brief Tells the amount of health the enemy has left
   * @return uint32_t
   */
  uint32_t CrLeft() const;

  /**
   * @brief Totalt amount of credits the enemy is worth
   * @return uint32_t
   */
  uint32_t GetCredits() const;

  /**
   * @brief Makes the enemy take damage
   * Splitting enemies hurt the attacking tower when they die. The return value tells the amount of this damage.
   * The method is overridden in subclass Degree.
   * @param dmg The amount of damage taken
   * @param location A reference to the list of enemies at the location of this enemy. Used by Degree to spawn its descendants there
   * @return uint32_t
   * */
  virtual uint32_t TakeDmg(uint32_t dmg, std::list<Assignment*>& location);

  /**
   * @brief Overload for stream operator << for debugging 
   */
  friend std::ostream& operator<<(std::ostream& os, const Assignment& as);

protected:
  uint32_t m_maxCr, m_curCr, m_timeToMove, m_timeRemainder;
  bool m_movedLastTick;
};
