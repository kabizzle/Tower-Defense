#pragma once

#include <cstdint>
#include <string>

#include "renderable.hpp"

/**
 * @brief An abstarct base-class for the towers
 * 
 * Sub-classes will be Attackin towers and supporting towers
 */
class Tower : public Renderable
{
public:
  Tower(uint32_t power, uint32_t range, const std::string& imageName)
    : Renderable(imageName), m_power(power), m_range(range) { }
  ~Tower();

  /**
   * @brief Used for attacking/supporting, TODO needs some way to contact Map
   * 
   */
  virtual void Act() = 0;

  //TODO methods to apply buffs (from supports etc)

private:
  uint32_t m_power, m_range;
};