#include "tower.hpp"

Tower::Tower(uint32_t range, const std::pair<int32_t, int32_t>& coords, const std::string& name, const std::vector<sf::Sprite>& sprites)
  : Renderable(name, sprites[0]), m_range(range), m_coords(coords), m_allSprites(sprites) {
    //Set the location of the sprite correctly
    m_sprite.setPosition(m_coords.first * TILE_SIZE, m_coords.second * TILE_SIZE);
  }

const std::pair<int32_t, int32_t>& Tower::GetCoords() const { return m_coords; }

uint32_t Tower::GetRange() const { return m_range; }