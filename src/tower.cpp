#include "tower.hpp"

Tower::Tower(uint32_t range, const std::pair<int32_t, int32_t>& coords, const std::string& imageName, const std::vector<sf::Sprite>& sprites)
  : Renderable(imageName, sprites[0]), m_range(range), m_coords(coords) {
    //Set the location of the sprite correctly
    m_sprite.setPosition(m_coords.first, m_coords.second);
  }

const std::pair<int32_t, int32_t>& Tower::GetCoords() const { return m_coords; }