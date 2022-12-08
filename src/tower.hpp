#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "renderable.hpp"
#include "map.hpp"

enum TowerType {
  Freshman,
  Teekkari,
  Bachelor,
  Master,
  Doctor,
  Calculator,
  CoffeeTable
};

/**
 * @brief An abstract base-class for the towers
 * 
 * Sub-classes will be Attacking towers and supporting towers
 */
class Tower : public Renderable
{
public:
  /**
   * @brief Get the coordinates of the tower 
   */
  const std::pair<int32_t, int32_t>& GetCoords() const;

  /**
   * @brief Tells if the tower can be upgraded with set amount of money
   * @param money The amount of money the player has 
   * @return bool
   */
  virtual bool IsUpgradeable(uint32_t money) const = 0;

  inline static const std::map<TowerType, uint32_t> towerPrices = {
    {TowerType::Freshman, 20}, {TowerType::Teekkari, 40},
    {TowerType::Bachelor, 60}, {TowerType::Master, 80},
    {TowerType::Doctor, 100}, {TowerType::Calculator, 50},
    {TowerType::CoffeeTable, 50}
  };

protected:
  uint32_t m_range;
  std::pair<int32_t, int32_t> m_coords;
  std::vector<sf::Sprite> m_allSprites;

  //Private functions
  /**
   * @brief Plain towers are not meant to be constructed, only the subclassess are
   * 
   * @param range The basic range, all towers have this
   * @param coords The coordinates of the tower
   * @param imageName The name of the image representing this particular tower, also the name of the tower type
   */
  Tower(uint32_t range, const std::pair<int32_t, int32_t>& coords,
        const std::string& imageName, const std::vector<sf::Sprite>& sprites);
  virtual ~Tower() { }

  /**
   * @brief TODO, for possible range updates
   * 
   */
  void UpdateTargetable();
};