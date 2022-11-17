#include "tower.hpp"

Tower::Tower(uint32_t power, uint32_t range, uint32_t health, const std::string& imageName)
  : Renderable(imageName), m_power(power), m_range(range), m_health(health) { }