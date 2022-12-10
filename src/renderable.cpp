#include "renderable.hpp"

Renderable::Renderable(const std::string& entityName, const sf::Sprite& sprite)
  : m_entityName(entityName), m_sprite(sprite) { }

const std::string& Renderable::EntityName() const {
  return m_entityName;
}

sf::Sprite& Renderable::GetSprite() { 
  return m_sprite;
}

void Renderable::SetSprite(const sf::Sprite& newSprite) {
  m_sprite = newSprite;
}
