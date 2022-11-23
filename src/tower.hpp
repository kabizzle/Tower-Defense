#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "renderable.hpp"
#include "map.hpp"

/**
 * @brief An abstarct base-class for the towers
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

protected:
  uint32_t m_range;
  std::pair<int32_t, int32_t> m_coords;

  //Private functions
  /**
   * @brief Plain towers are not meant to be constructed, only the subclassess are
   * 
   * @param range The basic range, all towers have this
   * @param coords The coordinates of the tower
   * @param imageName The name of the image representing this particular tower, also the name of the tower type
   */
  Tower(uint32_t range, std::pair<int32_t, int32_t> coords, const std::string& imageName);
  virtual ~Tower() { }

  /**
   * @brief TODO, for possible range updates
   * 
   */
  void UpdateTargetable();
};