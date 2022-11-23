#include "tower.hpp"

Tower::Tower(uint32_t range, std::pair<uint32_t, uint32_t> coords, const std::string& imageName)
  : Renderable(imageName), m_range(range), m_coords(coords) { }