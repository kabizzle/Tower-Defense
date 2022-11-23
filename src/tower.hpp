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
  Tower(uint32_t range, std::pair<uint32_t, uint32_t> coords, const std::string& imageName);

  virtual ~Tower() { }

  //TODO methods to apply buffs (from supports etc)

private:
  uint32_t m_range;
  std::pair<uint32_t, uint32_t> m_coords;

  //Private functions
  void UpdateTargetable();
};