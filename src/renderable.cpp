#include "renderable.hpp"

Renderable::Renderable(const std::string& imageName, const sf::Sprite& sprite)
  : m_imageName(imageName), m_sprite(sprite) { }

const std::string Renderable::ImgPath() const {
  return m_imageName + ".png";
}

sf::Sprite& Renderable::GetSprite() { 
  return m_sprite;
}

void Renderable::AddSuffix(const std::string& suffix) {
  m_imageName += suffix;
}

void Renderable::SetSprite(const sf::Sprite& newSprite) {
  m_sprite = newSprite;
}
