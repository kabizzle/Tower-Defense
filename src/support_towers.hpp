#pragma once

#include "attacking_tower.hpp"

/**
 * @brief A virtual base class for the supporting towers
 * Cannot be directly instanciated
 */
class SupportTower : public Tower
{
protected:
  /**
   * @brief Construct a new Support Tower object
   * 
   * @param range The range of the tower
   * @param coords The coordinates of the tower
   * @param name The name of this tower
   * @param sprites Support towers cannot be upgraded, so the collection only has one sprite for them
   */
  SupportTower(uint32_t range, const std::pair<int32_t, int32_t>& coords,
               const std::string& name, const std::vector<sf::Sprite>& sprites);

public:
  /**
   * @brief Virtual destructor
   */
  virtual ~SupportTower() { }

  /**
   * @brief No SupportTower can be upgraded
   * @return false
   */
  bool IsUpgradeable(uint32_t money) const;
  /**
   * @brief Used by the supporting towers to buff/heal the attacking towers
   * The towers go through the attacking towers present on the game board and apply buffs/heal those that are
   * within range
   * @param towers The towers present on the game board
   */
  virtual void Act(std::list<AttackingTower*>& towers) = 0;

  /**
   * @brief Overload to stream output operator
   */
  friend std::ostream& operator<<(std::ostream& os, const SupportTower& st);

  //static functions to create support towers
  /**
   * @brief Creates a BuffTower called calculator
   * @param coords Where to create the tower
   * @return SupportTower*
   */
  static SupportTower* Calculator(const std::pair<int32_t, int32_t>& coords);

  /**
   * @brief Creates a HealTower called coffee_table
   * @param coords Where to create the tower
   * @return SupportTower* 
   */
  static SupportTower* CoffeeTable(const std::pair<int32_t, int32_t>& coords);

};

/**
 * @brief A tower which buffs attacking towers making the do more damage
 */
class BuffTower : public SupportTower
{
public:
  /**
   * @brief Construct a new Buff Tower object
   * @param range The basic range
   * @param coords The coordinates of the tower
   * @param buffStrength The amount of buff the tower gives, for example 20% buff is 0.2f
   * @param name The name of the tower
   * @param sprites Support towers cannot be upgraded, so the collection only has one sprite for them
   */
  BuffTower(uint32_t range, const std::pair<int32_t, int32_t>& coords, float buffStrength,
            const std::string& name, const std::vector<sf::Sprite>& sprites);
  
  /**
   * @brief Default destructor
   */
  ~BuffTower() = default;

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
   * @param name The name of the tower
   * @param sprites Support towers cannot be upgraded, so the collection only has one sprite for them
   */
  HealTower(uint32_t range, const std::pair<int32_t, int32_t>& coords, uint32_t healStrength,
            const std::string& name, const std::vector<sf::Sprite>& sprites);
  
  /**
   * @brief Default destructor
   */
  ~HealTower() = default;
  
  /**
   * @brief Goes through the attacking towers and heals them if in range and not in full health already
   * 
   * @param towers The towers on the game board
   */
  void Act(std::list<AttackingTower*>& towers);
private:
  uint32_t m_healStrength;
};

