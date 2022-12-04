#pragma once

#include "attacking_tower.hpp"

/**
 * @brief A virtual base class for the supporting towers
 * 
 */
class SupportTower : public Tower
{
protected:
  SupportTower(uint32_t range, const std::pair<int32_t, int32_t>& coords, const std::string& imageName);

public:
  virtual ~SupportTower() { }
  /**
   * @brief Used by the supporting towers to buff/heal the attacking towers
   * The towers go through the attacking towers present on the game board and apply buffs/heal those that are
   * within range
   * @param towers The towers present on the game board
   */
  virtual void Act(std::list<AttackingTower*>& towers) = 0;

  /**
   * @brief Overload to stream output operator
   * @return std::ostream& 
   */
  friend std::ostream& operator<<(std::ostream& os, const SupportTower& st);

  //static functions to create support towers
  static SupportTower* Calculator(const std::pair<int32_t, int32_t>& coords);
  static SupportTower* CoffeeTable(const std::pair<int32_t, int32_t>& coords);

};

/**
 * @brief A tower which buffs attacking towers making the do more damage
 * 
 */
class BuffTower : public SupportTower
{
public:
  /**
   * @brief Construct a new Buff Tower object
   * 
   * @param range The basic range
   * @param coords The coordinates of the tower
   * @param buffStrength The amount of buff the tower gives, for example 20% buff is 0.2f
   * @param imageName The name of the image representing this particular tower, also the name of the tower type
   */
  BuffTower(uint32_t range, const std::pair<int32_t, int32_t>& coords, float buffStrength, const std::string& imageName);
  //~BuffTower();
  /**
   * @brief Goes trough the attacking towers in the game and applies buff to them
   * 
   * @param towers The towers on the game board
   */
  void Act(std::list<AttackingTower*>& towers);
private:
  float m_buffStrength;
};

/**
 * @brief A tower which heals attacking towers
 */
class HealTower : public SupportTower
{
public:
  /**
   * @brief Construct a new healing tower
   * 
   * @param range The basic range
   * @param coords The coordinates of the tower
   * @param healStrength The amount this tower can heal each tower during each tick
   * @param imageName The name of the image representing this particular tower, also the name of the tower type
   */
  HealTower(uint32_t range, const std::pair<int32_t, int32_t>& coords, uint32_t healStrength, const std::string& imageName);
  //~HealTower();
  /**
   * @brief Goes through the attacking towers and heals them if in range and not in full health already
   * 
   * @param towers The towers on the game board
   */
  void Act(std::list<AttackingTower*>& towers);
private:
  uint32_t m_healStrength;
};

