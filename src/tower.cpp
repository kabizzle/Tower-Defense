#include "tower.hpp"

Tower::Tower(uint32_t range, const std::pair<int32_t, int32_t>& coords, const std::string& imageName)
  : Renderable(imageName), m_range(range), m_coords(coords) { }

const std::pair<int32_t, int32_t>& Tower::GetCoords() const { return m_coords; }