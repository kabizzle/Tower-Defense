#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "map.hpp"
#include "renderable.hpp"

#define TILE_SIZE 30

/**
 * @brief An enumeration for the different towertypes
 */
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
 * Sub-classes will be Attacking towers and supporting towers.
 * Cannot be directly instanciated.
 */
class Tower : public Renderable {
 public:
  /**
   * @brief Virtual destructor
   */
  virtual ~Tower() { }
  /**
   * @brief Get the coordinates of the tower
   * @return const std::pair<int32_t, int32_t>&
   */
  const std::pair<int32_t, int32_t>& GetCoords() const;

  /**
   * @brief Tells if the tower can be upgraded with set amount of money
   * Supporting towers can never be upgraded
   * @param money The amount of money the player has
   * @return bool
   */
  virtual bool IsUpgradeable(uint32_t money) const = 0;

  /**
   * @brief The prices of the different kinds of towers
   */
  inline static const std::map<TowerType, uint32_t> towerPrices = {
      {TowerType::Freshman, 50},     {TowerType::Teekkari, 300},
      {TowerType::Bachelor, 1000},   {TowerType::Master, 3000},
      {TowerType::Doctor, 5000},     {TowerType::Calculator, 1000},
      {TowerType::CoffeeTable, 1000}};

  /**
   * @brief The base ranges of the towers
   */
  inline static const std::map<TowerType, uint32_t> towerRanges = {
      {TowerType::Freshman, 2},   {TowerType::Teekkari, 3},
      {TowerType::Bachelor, 5},   {TowerType::Master, 7},
      {TowerType::Doctor, 9},     {TowerType::Calculator, 5},
      {TowerType::CoffeeTable, 5}};

  /**
   * @brief The base powers of the attacking towers
   */
  inline static const std::map<TowerType, uint32_t> towerPowers = {
      {TowerType::Freshman, 1},  {TowerType::Teekkari, 5},
      {TowerType::Bachelor, 20}, {TowerType::Master, 50},
      {TowerType::Doctor, 100},
  };

  /**
   * @brief The healths of the attacking towers
   */
  inline static const std::map<TowerType, uint32_t> towerHealths = {
      {TowerType::Freshman, 10}, {TowerType::Teekkari, 20},
      {TowerType::Bachelor, 30}, {TowerType::Master, 40},
      {TowerType::Doctor, 50},
  };

  /**
   * @brief Get the range of the tower
   * @return uint32_t
   */
  uint32_t GetRange() const;

 protected:
  uint32_t m_range;
  std::pair<int32_t, int32_t> m_coords;
  std::vector<sf::Sprite>
      m_allSprites;  //< Stores all the sprites of the tower, one for each level

  /**
   * @brief Plain towers are not meant to be constructed, only the subclassess
   * are
   * @param range The basic range, all towers have this
   * @param coords The coordinates of the tower
   * @param name The name of the tower
   * @param sprites Sprites for the different levels of the tower
   */
  Tower(uint32_t range, const std::pair<int32_t, int32_t>& coords,
        const std::string& name, const std::vector<sf::Sprite>& sprites);

};